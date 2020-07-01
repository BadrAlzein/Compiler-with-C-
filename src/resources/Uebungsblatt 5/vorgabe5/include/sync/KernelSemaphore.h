#ifndef KernelSemaphore_h
#define KernelSemaphore_h

#include "lib/ThreadQueue.h"
#include "system/Thread.h"
#include "thread/ActivityScheduler.h"

/**
 * KernelSemaphore: Semaphorenimplementierung f�r kooperative
 * Prozesse oder zur Anwendung innerhalb des Kernels.
 */

class KernelSemaphore {
public:
	// Initialisierung des Zaehlers
	KernelSemaphore(int count = 1) : counter(count), processNum(0) {}

	void wait();
	void signal();

private:
    int         counter;
    int         processNum;
    Queue       queue;
    // Nur für die Implementierung mit Hilfe einer speziellen Thread-Queue
    // ThreadQueue     queue;


};

#endif

