#include "thread/ActivityScheduler.h"
#include "device/CPU.h"
#include "interrupts/IntLock.h"
#include "sync/KernelLock.h"
#include "sync/Monitor.h"


/* Initialisieren der ersten Aktivit�t, des Schedulers
	 * und des Dispatchers.
	 * Wird nur einmal aufgerufen.
	 */
void ActivityScheduler::start(Activity *act) {

    // Werte initialisieren
    // Dispatch, activeElement ...
    // siehe 'init' und vorige Konstruktoren
    init(act);
    this->activeElement = act;
    act->changeTo(Activity::RUNNING);
}

/* Suspendieren des aktiven Prozesses
 * Der korrekte Ausfuehrungszustand ist zu setzen
 * und danach der naechste lauffaehige Prozess zu aktivieren.
 */
void ActivityScheduler::suspend() {
    //IntLock lock;
    activeElement->changeTo(Activity::BLOCKED);
    reschedule();

}

/* Explizites Terminieren des angegebenen Prozesses
 * Der Prozesszustand ist korrekt zu setzen
 * und der Prozess aus der Ready-Liste des Schedulers
 * zu entfernen. Falls der aktive Prozess zerstoert wird,
 * ist dem naechsten lauffaehigen Prozess die CPU
 * zuzuteilen.
 */
void ActivityScheduler::kill(Activity *act) {

    // Prozess wird zum Zombie
    act->changeTo(Activity::ZOMBIE);

    // remove or shoot down
    if (act != activeElement) {
        remove((Schedulable *) act);
    } else {
        reschedule();
    }


}

/* Terminieren des aktiven Prozesses,
 * und Wechsel zum naechsten lauffaehigen Prozess
 */
void ActivityScheduler::exit() {

    /*
     * Der Prozess wird hier nicht explizit beendet. Er wird durch zuweisen eines
     * neuen Prozesses beendet.
     */

    // wegen dem 'join' --> R�cksprung zum aktiven Element, als join aufgerufen wurde
    if (activeElement->waitingElement != 0x0) {

        Activity *processToWakeUp = activeElement->waitingElement;
        activeElement->waitingElement = 0x0;

        processToWakeUp->wakeup();
    }

    reschedule();
}


/* Der aktive Prozess ist, sofern er sich nicht im Zustand
 * Blocked oder Zombie befindet, wieder auf die Ready-Liste
 * zu setzen. Danach ist "to" mittels dispatch die Kontrolle
 * zu �bergeben.
 */
void ActivityScheduler::activate(Schedulable *to) {


    if (((!to) && ((activeElement->isRunning()) || (activeElement->isReady()))) || (idle)) {
        return;
    } else { // kein aktives, lauffähiges Element

        Activity* newTo = (Activity*)to;
        // falls auch hier kein neues to vorhanden
        idle = true;
        
        while (!newTo) {
            // Möglichkeit zum Einsetzen der Interrupts
            monitor.leave();
            CPU::halt();
            monitor.enter();
            newTo = (Activity *) readylist.dequeue();
        }
        idle = false;

        if (!activeElement->isZombie() && !activeElement->isBlocked()) {
            activeElement->changeTo(Activity::READY);
            schedule(activeElement);
        }

        newTo->changeTo(Activity::RUNNING);
        activeElement = newTo;

        dispatch(newTo);

    }

}

void ActivityScheduler::checkSlice() {

        int quantum = activeElement->quantum();
        int currSlice = activeElement->getCurrentSlice();

        if (currSlice >= quantum) {
            activeElement->resetCurrentSlice();
            reschedule();
        } else {
            activeElement->incrementCurrentSlice();
        }

}
