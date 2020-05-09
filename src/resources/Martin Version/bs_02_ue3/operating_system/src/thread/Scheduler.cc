#include "thread/Scheduler.h"
#include "io/PrintStream.h"
#include "interrupts/IntLock.h"

/*
wir koennen auf der readylist queue methoden aufrufen!
*/
//insert one element to the readylist
void Scheduler::schedule(Schedulable *sched)
{
	//schützen der Ready-Liste
	IntLock safe;
	// chain kommt von schedulable und dann von chain selbst
	// cast ist hier noetig um mit den methoden von queue zu arbeiten
	readylist.enqueue((Chain *)sched);
}

//Remove one element from the readylist
void Scheduler::remove(Schedulable *sched)
{
	//schützen der Ready-Liste
	IntLock safe;
	readylist.remove((Chain *)sched);
}

// activate the front of list with activate
void Scheduler::reschedule()
{
	//schützen der Ready-Liste
	IntLock safe;
	/* Diese pur-virtuelle Methode stellt die Schnittstelle zum
	 * ActivityScheduler dar, der diese Klasse erweitert. Siehe
	 * die Beschreibung dort.
	 */
	// virtual void activate(Schedulable* to) = 0;
	// returns the head of list
	Schedulable *head = (Schedulable *)readylist.dequeue();
	this->activate(head);
}
