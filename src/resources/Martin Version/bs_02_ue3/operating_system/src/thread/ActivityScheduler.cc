#include "thread/ActivityScheduler.h"
#include "io/PrintStream.h"
#include "interrupts/IntLock.h"
#include "device/Clock.h"
extern Clock clock;

/*
 * Scheduler.h 
 * - Einfuegen eines neuen Elements in die Ready-Liste.
 * void schedule(Schedulable* sched);
 * - Entfernen eines Elements von der Ready-Liste.
 * void remove(Schedulable* sched);
 * - Aktiviert das vorderste der Liste mittels activate.
 * void reschedule();
 * - Diese Klasse implementiert die Zustandsverwaltung
 * - für Activities
 * Dem aktiven Prozess soll erst dann die CPU entzogen werden, wenn sein Quantum
 * abgelaufen ist. Führe dazu eine Methode checkSlice () beim Scheduler ein, die überprüft, ob die
 * Zeitscheibe des aktuell laufenden Prozesses abgelaufen ist.
 */
void ActivityScheduler::checkSlice()
{
	//redundanter IntLock weil schon in scheduler geschützt
	//IntLock safe;
	/*
	 *	von Clock.cc
	 *	Wenn der Uhrentest erfolgreich verlaufen ist, kommentiert
	 *	den Propeller wieder aus und ruft stattdessen
	 *	die "checkSlice" Methode des Schedulers auf,
	 *	um diesen ggf. zum praeemptiven Rescheduling zu veranlassen.
	 *  Dem aktiven Prozess soll erst dann die CPU entzogen werden, wenn sein Quantum
     *	abgelaufen ist. Führe dazu eine Methode checkSlice () beim Scheduler ein, die überprüft, ob die
	 *	Zeitscheibe des aktuell laufenden Prozesses abgelaufen ist.
	 */
	Schedulable *active = (Schedulable *)getActiveProcessActivity();
	if (active->getQuantum() == clock.ticks())
	{
		clock.resetTicks();
		this->reschedule(); //reschedule aufrufen, wenn Zeitscheibe(Quantum) abgelaufen ist
	}
}

/* Suspendieren des aktiven Prozesses
 * Der korrekte Ausfuehrungszustand ist zu setzen
 * und danach der naechste lauffaehige Prozess zu aktivieren.
 */
void ActivityScheduler::suspend()
{
	IntLock safe;
	/* 
	 * dispatcher holds always the running process
	 * - "active" liefert den Zeiger auf den aktiven Prozess.
	 * Coroutine* active()
	 * - get the current active process from dispatcher
	 */
	Activity *activeProcess = (Activity *)this->active();
	activeProcess->changeTo(Activity::BLOCKED);

	/* 
	 * remove current process from ready list
	 * this->remove((Schedulable *)activeProcess);
	 * Activity* nextElement = activeProcess->next;
	 * nextElement->setBlob(activeProcess);
	 * 
	 * this->schedule((Schedulable *)activeProcess);
	 * activate the next element in ready list
	 */
	this->reschedule();
}

/* void dispatch(Coroutine* next)
 * "dispatch" wird vom ActivityScheduler aufgerufen,
 * um vom aktiven zum neu ausgewaehlten Prozess zu wechseln.
 * Man beachte die Reihenfolge der Anweisungen, die daraus
 * resultiert, dass hier der Kontrollfluss gewechselt wird
 * 
 * Explizites Terminieren des angegebenen Prozesses
 * Der Prozesszustand ist korrekt zu setzen
 * und der Prozess aus der Ready-Liste des Schedulers
 * zu entfernen. Falls der aktive Prozess zerstoert wird,
 * ist dem naechsten lauffaehigen Prozess die CPU
 * zuzuteilen.
 */
void ActivityScheduler::kill(Activity *act)
{
	// redundanter IntLock weil schon in Scheduler geschützt
	//IntLock safe;

	act->changeTo(Activity::ZOMBIE);
	this->remove((Schedulable *)act);

	/*Activity *activeProcess = this->getActiveProcessActivity();
	if (activeProcess == act)
	{
		this->remove((Schedulable *)activeProcess);
		// aktiver prozess wuerde hier zerstoert werden
	}
	else
	{
		// remove the process passed in method
		this->remove((Schedulable *)act);
	}*/

	// nutze den naechsten prozess in liste
	this->reschedule();
}

/* 
 * Terminieren des aktiven Prozesses,
 * und Wechsel zum naechsten lauffaehigen Prozess
 */
void ActivityScheduler::exit()
{
	////redundanter IntLock weil schon in scheduler geschützt
	//IntLock safe;
	/* Dispatcher.h
	"active" liefert den Zeiger auf den aktiven Prozess.
	*/
	Activity *activeProcess = this->getActiveProcessActivity();
	this->kill(activeProcess);
	this->reschedule();
}

/* Der aktive Prozess ist, sofern er sich nicht im Zustand
 * Blocked oder Zombie befindet, wieder auf die Ready-Liste
 * zu setzen. Danach ist "to" mittels dispatch die Kontrolle
 * zu �bergeben.
 */
void ActivityScheduler::activate(Schedulable *to)
{
	//redundanter IntLock, wird schon im Scheduler geschützt
	//IntLock safe;

	Activity *destinationProcess = (Activity *)to;
	Activity *activeProcess = this->getActiveProcessActivity();

	if (((!(activeProcess->isBlocked())) && (!(activeProcess->isZombie()))) && activeProcess->isRunning())
	{
		// Einfuegen eines neuen Elements in die Ready-Liste.
		activeProcess->changeTo(Activity::READY);
		scheduler.schedule((Schedulable *)activeProcess);
	}

	// solange later ein nullpointer auf eine activity ist
	while (destinationProcess == 0)
	{
		if (!(activeProcess->isRunning()))
		{
			// Entfernen des Listenkopfes
			destinationProcess = (Activity *)readylist.dequeue();
		}
	}
	/* "dispatch" wird vom ActivityScheduler aufgerufen,
	 * um vom aktiven zum neu ausgewaehlten Prozess zu wechseln.
	 * Man beachte die Reihenfolge der Anweisungen, die daraus
	 * resultiert, dass hier der Kontrollfluss gewechselt wird
	 */
	if (destinationProcess != 0)
	{
		destinationProcess->changeTo(Activity::RUNNING);
		dispatch(destinationProcess);
	}
}

Activity *ActivityScheduler::getActiveProcessActivity()
{
	return ((Activity *)this->active());
}
