#ifndef Semaphore_h
#define Semaphore_h

#include "sync/KernelSemaphore.h"
#include "sync/KernelLock.h"

/**
 *  Semaphore: Die Semaphorenimplementation f�r Benutzerprozesse
 * 
 * Deshalb soll für sie die Semaphore implementiert werden. 
 * In dieser wird nicht die gesamte Funktionalität der KernelSemaphore erneut
implementiert (beachtet die Vererbungshierarchie).
 */
class Semaphore: private KernelSemaphore {
public:
	Semaphore(int count = 1) 
	: KernelSemaphore(count)
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
