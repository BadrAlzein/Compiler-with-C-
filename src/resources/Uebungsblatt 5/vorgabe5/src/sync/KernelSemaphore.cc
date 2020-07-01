//
// Created by Robert on 30.06.2019.
//

#include "sync/KernelSemaphore.h"
#include "device/CPU.h"

void KernelSemaphore::wait() {

    if (counter > 0) {
        counter--;
        return;
    }

    queue.enqueue((Activity*) scheduler.active());
    scheduler.activeElement->sleep();

}

void KernelSemaphore::signal() {

    if (!queue.getHead()) {
        counter++;
    } else {
        Thread* thread = (Thread*) queue.dequeue();
        thread->start();
    }

}


/* Implementierung mit Hilfe einer Thread-Queue (nicht unbedingt noetig)
void KernelSemaphore::wait() {

    if (counter > 0) {
        counter = counter - 1;
        return;
    }

    Thread* curr = Thread::self();

    queue.add(curr);
    processNum = processNum + 1;

    curr->sleep();
}

void KernelSemaphore::signal() {

    counter = counter + 1;

    if (processNum > 0) {

        Thread* act = queue.get();

        if (act) {
            processNum = processNum - 1;
            act->start();
        }

        return;

    }

}
*/