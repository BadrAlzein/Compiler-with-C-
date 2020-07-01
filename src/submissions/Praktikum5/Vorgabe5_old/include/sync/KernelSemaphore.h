#ifndef KernelSemaphore_h
#define KernelSemaphore_h


/**
 * KernelSemaphore: Semaphorenimplementation f�r kooperative
 * Prozesse oder zur Anwendung innerhalb des Kernels.
 */

#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"
class KernelSemaphore {
public:
	// Initialisierung des Zaehlers
	KernelSemaphore(int count = 1) : space(count)
	{
		
	}

	void wait();
	void signal();

private:
	Queue queue;

	volatile unsigned int space;


};

#endif

