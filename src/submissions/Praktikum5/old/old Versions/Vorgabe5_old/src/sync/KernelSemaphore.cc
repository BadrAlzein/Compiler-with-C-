#include "sync/KernelSemaphore.h"


void KernelSemaphore :: wait() {
    if(this -> space <= 0) {
        Activity* current = (Activity*) (scheduler.getCurrentActivity());
        this -> queue.enqueue(current);
        current -> sleep();
    } else {
        this -> space--;
    }
}

void KernelSemaphore :: signal() {
    Activity* waiting = (Activity*) (this ->queue.dequeue());
    if(waiting == 0) {
        this -> space++;
    } else {
        waiting -> wakeup();
    }
}