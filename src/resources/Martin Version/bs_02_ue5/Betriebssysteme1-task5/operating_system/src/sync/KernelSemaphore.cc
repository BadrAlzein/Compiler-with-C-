#include "sync/KernelSemaphore.h"

/**
 * KernelSemaphore: Semaphorenimplementation f�r kooperative
 * Prozesse oder zur Anwendung innerhalb des Kernels.
 * Implementiert zunächst die KernelSemaphore für den kooperativen Fall. Wie der Name andeutet,
wird diese innerhalb des Kerns benutzt. Überlegt euch, was dies für den Schutz von kritischen
Datenstrukturen bedeutet.
 */

void KernelSemaphore::wait() {
    if (this->space <= 0) {
        // wenn wir keinen platz mehr im restaurant haben 
        // dann wird auch keiner reinkommen und stellt sich an die schlange an
        Activity* current = (Activity*) (scheduler.getActiveProcessActivity());
        this->snake.enqueue(current);
        current->sleep();
    } else {
        // andernfalls kommt einer herein 
        // und der platz im restaurant wird kleiner
        this->space--;
    }
}

void KernelSemaphore::signal() {
    // entfernen des listenkopfs
    Activity* waiting = (Activity*) (this->snake.dequeue());
    if (waiting == 0) {
        // mache platz frei, wenn keiner mehr wartet
        // also wenn die schlange leer ist, 
        // dann muss auch wieder platz im restaurant sein
        this->space++;
    } else {
        // andernfalls wecke den wartenden kunden wieder auf 
        // und er schafft es vielleicht ins restaurant zu kommen
        waiting -> wakeup();
    }
}