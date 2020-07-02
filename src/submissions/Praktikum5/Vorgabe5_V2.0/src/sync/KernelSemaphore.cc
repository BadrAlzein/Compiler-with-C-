#include "sync/KernelSemaphore.h"

/**
 * The implementaion of the Kernel Semaphore
 * and the implementation of the 2 methodes that every Semaphore has
 * wait() and signal()
 * 
*/

// with the wait methode the calling methode will be blocked if the
// counter is 0, otherwise the counter will be decremented
void KernelSemaphore :: wait() {
    if(this -> space <= 0) {
        Activity* current = (Activity*) (scheduler.getCurrentActivity());
        this -> queue.enqueue(current);
        current -> sleep();
    } else {
        this -> space--;
    }
}

// with the siganl methode the next sleeping process will be waken up
// if non of the processes are sleeping then the counter will be incremented
void KernelSemaphore :: signal() {
    Activity* waiting = (Activity*) (this ->queue.dequeue());
    if(waiting == 0) {
        this -> space++;
    } else {
        waiting -> wakeup();
    }
}