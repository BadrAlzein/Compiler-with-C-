#ifndef ActivityScheduler_h
#define ActivityScheduler_h

/*
 * ActivityScheduler: 	Diese Klasse implementiert die Zustandsverwaltung
 * 			f�r Activities
 * 
Zum Schluss kommt der ActivityScheduler . h . Er verwaltet die Ausf�hrungszust�nde der Prozesse.
Er sorgt daf�r, dass ein Prozess wieder in die Ready-Liste kommt, wenn es der Ausf�hrungszu-
stand erlaubt. Er sorgt auch daf�r, dass wenn Prozesse beendet werden, eventuelle Wartebedin-
gungen eingehalten werden. Au�erdem kann der ActivityScheduler . h Prozesse komplett aus dem
Scheduling entfernen.
Testet zum Schluss Euer System zun�chst mit dem in mainAct.cc vorgegebenen Programm und
testet zus�tzlich mit einem eigenen Programm die Funktionalit�t von sleep , wakeup und das Ver-
halten beim Beenden von Prozessen. Dies ist nat�rlich bei der Abgabe zu demonstrieren.
 */

#include "lib/Queue.h"
#include "thread/Activity.h"
#include "thread/Dispatcher.h"
#include "thread/Scheduler.h"

class ActivityScheduler : public Dispatcher, public Scheduler
{
public:
	/*
	Scheduler.h 

	// Einfuegen eines neuen Elements in die Ready-Liste.
	void schedule(Schedulable* sched);

	// Entfernen eines Elements von der Ready-Liste.
	void remove(Schedulable* sched);

	// Aktiviert das vorderste der Liste mittels activate.
	void reschedule();
	// Diese Klasse implementiert die Zustandsverwaltung
 	// f�r Activities
 	*/
	ActivityScheduler()
	{
		/* Definieren des ersten Prozesses.
		 * Wird nur einmal zur Initialisierung aufgerufen!!
		 */
		// void init(Coroutine* act)
		waiting = false;
	}

	/* Initialisieren der ersten Aktivit�t, des Schedulers
	 * und des Dispatchers.
	 * Wird nur einmal aufgerufen.
	 */
	void start(Activity *act)
	{
		// init from dispatch first initial coroutine
		act->changeTo(Activity::RUNNING);
		init((Coroutine *)act);
		// initialize the first element in Scheduler
		//this->schedule((Schedulable *)act);
		// Aendern des Ausfuehrungszustandes. Diese Methode sollte nur vom
		// Scheduler verwendet werden.
		// void Activity::changeTo(State state)
		 
		// kann changeto mit der uerbergabe benutzen
		
		waiting = false;
		// after starting activity the state is running normally
		/*act->changeTo(Activity::RUNNING);
		this->init((Coroutine *) act);
		this->remove((Schedulable *) act);
		waiting = false;*/


	}

	/* Suspendieren des aktiven Prozesses
	 * Der korrekte Ausfuehrungszustand ist zu setzen
	 * und danach der naechste lauffaehige Prozess zu aktivieren.
	 */
	void suspend();

	/* Explizites Terminieren des angegebenen Prozesses
	 * Der Prozesszustand ist korrekt zu setzen
	 * und der Prozess aus der Ready-Liste des Schedulers
	 * zu entfernen. Falls der aktive Prozess zerstoert wird,
	 * ist dem naechsten lauffaehigen Prozess die CPU
	 * zuzuteilen.
	 */
	void kill(Activity *);

	/* Terminieren des aktiven Prozesses,
	 * und Wechsel zum naechsten lauffaehigen Prozess
	 */
	void exit();

	Activity *getActiveProcessActivity();
	

protected:
	/* Der aktive Prozess ist, sofern er sich nicht im Zustand
	 * Blocked oder Zombie befindet, wieder auf die Ready-Liste
	 * zu setzen. Danach ist "to" mittels dispatch die Kontrolle
	 * zu �bergeben.
	 */
	virtual void activate(Schedulable *to);

private:
	bool waiting;
};

extern ActivityScheduler scheduler;

#endif
