#ifndef Scheduler_h
#define Scheduler_h

/*
 * Scheduler: 	Diese Klasse implementiert die Zuteilungsstrategie
 *		fuer die CPU.
 *
 *	Anmerkung: Hier wird ein einfacher First-Come-First-Served
 *	Algorithmus implementiert, der sich auf eine
 *	ready-liste stuetzt, in dem alle lauffaehigen Prozesse
 *	miteinander verkettet sind.
 Als nächstes kommt der Scheduler . h . Er verwaltet alle lauffähigen Objekte auf einer Liste. In der
ersten Aufgabe ist ein simpler FIFO-Scheduler zu implementieren. Er wird über die Methoden
schedule , remove und reschedule benutzt. Seinerseits benutzt er die abstrakte Methode activate , um
dem abgeleiteten Scheduler mitzuteilen, welches Objekt er zur Aktivierung ausgesucht hat. Er
entfernt dabei das ausgesuchte Objekt aus seiner Ready-Liste.
 */

#include "lib/Queue.h"
#include "thread/Schedulable.h"

class Scheduler {
public:

	// Einfuegen eines neuen Elements in die Ready-Liste.
	void schedule(Schedulable* sched);

	// Entfernen eines Elements von der Ready-Liste.
	void remove(Schedulable* sched);

	// Aktiviert das vorderste der Liste mittels activate.
	void reschedule();


protected:
	/* Diese pur-virtuelle Methode stellt die Schnittstelle zum
	 * ActivityScheduler dar, der diese Klasse erweitert. Siehe
	 * die Beschreibung dort.
	 */
	virtual void activate(Schedulable* to) = 0;

	// Die Ready-Liste
	Queue readylist;
};

#endif
