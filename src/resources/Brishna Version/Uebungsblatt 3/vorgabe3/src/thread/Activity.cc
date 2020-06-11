#include "../include/thread/Activity.h"
#include "../include/thread/ActivityScheduler.h"

/**
 * Hier wird scheduler verwendet (die globale Variable).
 *
 * Leider ist das dann nicht mehr gleichgültig. Aber is halt so anscheinend.
 *
 */

/* Aufsetzen eines Threads, der initiale Zustand ist "Blocked",
 * da der Thread erst laufen darf, wenn der spezielle Konstruktor
 * der abgeleiteten Klasse abgearbeitet ist. Die Aktivierung
 * erfolgt von der abgeleiteten Klasse mittels "wakeup".
 */
Activity::Activity(void *tos) : Coroutine(tos) {
    IntLock lock;
    this->state = BLOCKED;
    waitingElement = 0x0;
}

/* Verpacken des aktuellen Kontrollflusses als Thread.
 * Wird nur für den Hauptkontrollfluss "main" benötigt.
 * Es wird hier kein Stack initialisiert.
 * Beachte das Activity wegen der Vererbungsbeziehung von
 * Coroutine abstrakt ist. Bei Bedarf muss "body" direkt
 * aufgerufen werden.
 */
Activity::Activity() {
    //IntLock lock;
    this->state = BLOCKED;
    waitingElement = 0x0;
    scheduler.start(this);
}


/* Im Destruktor muss ein explizites Terminieren dieser Aktivitaet erfolgen.
 * Das muss geschehen, da aufgrund der Aufrufreihenfolge von
 * Destruktoren bereits der abgeleitete Teil des Activity-Objekts zerstoert
 * wurde und diese Aktivitaet daher keine Laufzeit mehr erhalten darf.
 * Das Warten auf die Beendigung (mittels join()) muss im Destruktor der
 * von Activity am weitesten abgeleiteten Klasse erfolgen.
 */
Activity::~Activity() {
    //IntLock lock;
    // Diese Funktion wird aufgerufen, sobald ein Prozess seine LETZTE
    // Instruktion ausgeführt hat
    scheduler.kill(this);
}

/* Veranlasst den Scheduler, diese Aktivitaet zu suspendieren.
 */
void Activity::sleep() {
    //IntLock lock;
    // Prozess aus readylist entfernen
    // Da sleep() nur von einem aktiven Prozess aufgerufen werden (da Aufruf in Laufzeit), muss
    // einem neuen Prozess dem Prozessor zugewiesen werden.
    scheduler.suspend();
}

/* Veranlasst den Scheduler, diese Aktivitaet aufzuwecken.
 */
void Activity::wakeup() {
    IntLock lock;
    // Prozess einreihen
    this->state = READY;
    scheduler.schedule(this);
}

/*
 * Diese Aktivitaet gibt die CPU vorruebergehend ab.
 */
void Activity::yield() {
    //IntLock lock;
    // Prozess gibt den Prozessor weiter an das erste Element der readylist ab.
    // Reiht sich dann wieder ans Ende der readylist ein.


    //this->state = READY; // unnoetig?
    scheduler.reschedule(); //activate=> dispatch

}

/* Diese Aktivitaet wird terminiert. Hier muss eine eventuell
 * auf die Beendigung wartende Aktivität geweckt werden.
 */
void Activity::exit() {
    IntLock lock;
    // Auf Zombie setzen und Prozess terminieren.
    this->state = ZOMBIE;
    scheduler.exit();
}

/* Der aktuelle Prozess wird solange schlafen gelegt, bis der
 * Prozess auf dem join aufgerufen wird beendet ist. Das
 * Wecken des wartenden Prozesses übernimmt exit.
 */
void Activity::join() {

    IntLock lock;

    waitingElement = scheduler.activeElement;

    if ((!isZombie())) { // Für einen Zombie soll das hier nicht mehr ausgeführt werden!
        if (this != waitingElement) {

            waitingElement->sleep();

        }
    }

}
