#ifndef Semaphore_h
#define Semaphore_h

#include "sync/KernelSemaphore.h"
#include "sync/KernelLock.h"

// Von Robert
// ---------- Von hier ----------

#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"

extern ActivityScheduler scheduler;

// ---------- bis hier ----------

/**
 *  Semaphore: Die Semaphorenimplementation f�r Benutzerprozesse
 */
class Semaphore: private KernelSemaphore {
public:
	Semaphore(int count = 1) : KernelSemaphore(count)
	{}

	void wait()
	{
	    KernelLock lock;
	    KernelSemaphore::wait();
	}


	void signal()
	{
        KernelLock lock;
        KernelSemaphore::signal();
	}
};

#endif
