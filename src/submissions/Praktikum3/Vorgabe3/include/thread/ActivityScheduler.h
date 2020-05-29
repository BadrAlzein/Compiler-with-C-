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
	ActivityScheduler(){}

	/* Initialisieren der ersten Aktivit�t, des Schedulers
	 * und des Dispatchers.
	 * Wird nur einmal aufgerufen.
	 */
	void start(Activity *act)
	{
		/* 1. init the activity for Scheduler
         * 2. init the first activity for Dispatcher
		 * PS. act is not an obj but a pointer
         */

		//Scheduler
		act->changeTo(Activity::RUNNING);

		//Dispatcher
		init(act);
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

    /** this will get the active Act*/
	Activity *getCurrentActivity(){
        return ((Activity *) active());
    };
	
	/** resheduler if the quatum has reached the ticks of the clk then reset the clk */
	void quatumResheduler();

//protected:
	/* Der aktive Prozess ist, sofern er sich nicht im Zustand
	 * Blocked oder Zombie befindet, wieder auf die Ready-Liste
	 * zu setzen. Danach ist "to" mittels dispatch die Kontrolle
	 * zu �bergeben.
	 */
	virtual void activate(Schedulable *to);

   // Activity* activeElement;
 

private:
};

extern ActivityScheduler scheduler;

#endif
