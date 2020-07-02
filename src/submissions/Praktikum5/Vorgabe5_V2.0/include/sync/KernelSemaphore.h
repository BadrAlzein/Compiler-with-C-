#ifndef KernelSemaphore_h
#define KernelSemaphore_h


/**
 * KernelSemaphore: Semaphorenimplementation f�r kooperative
 * Prozesse oder zur Anwendung innerhalb des Kernels.
 */

// implementing the KernelSepmaphore for the case of cooperative processes
// as the name suggests it should be protected in the Core

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
	int space;
};

#endif

