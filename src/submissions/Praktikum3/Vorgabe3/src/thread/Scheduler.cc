#include "thread/Scheduler.h"
#include "io/PrintStream.h"


//add a new element to the ready list , FIFO principal (Queue)
void Scheduler :: schedule(Schedulable* sched) {
    readylist.enqueue((Chain*)sched);
}

//entferne eine beliebiges Element aus dem Ready list
void Scheduler :: remove (Schedulable* sched) {
    readylist.remove((Chain*) sched);
}
//activiate the second ELement from the ready list (the second Process)
//dequeue the first item from the list and activiate the next element (process)
void Scheduler :: reschedule() {
    Schedulable* head = (Schedulable *) readylist.dequeue();
	this->activate(head);
}