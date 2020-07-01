#include "../include/thread/Scheduler.h"
#include "sync/KernelLock.h"

// Einfuegen eines neuen Elements in die Ready-Liste.
void Scheduler::schedule(Schedulable *sched) {
    //IntLock lock;
    readylist.enqueue(sched);
}

// Entfernen eines Elements von der Ready-Liste.
void Scheduler::remove(Schedulable *sched) {
    //IntLock lock;
    readylist.remove((Chain *) sched);
}

// Aktiviert das vorderste der Liste mittels activate.
void Scheduler::reschedule() {
    //IntLock lock;
    activate((Schedulable *) readylist.dequeue());
}

/**
 * Jeder Prozess erfält einen Slice vom Quentum.
 */
