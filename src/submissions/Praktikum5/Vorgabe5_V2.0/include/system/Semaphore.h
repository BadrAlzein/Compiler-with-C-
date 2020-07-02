#ifndef Semaphore_h
#define Semaphore_h

#include "sync/KernelSemaphore.h"
#include "sync/KernelLock.h"

/**
 *  Semaphore: Die Semaphorenimplementation f�r Benutzerprozesse
 * implentation of the KernelSempahore class where the 2 Operations of any Semaphore
 * wait() and signal implemented
 * 
 */
class Semaphore: private KernelSemaphore {
public:
	Semaphore(int count = 1) : KernelSemaphore(count)
	{}

	//the actual wait methode from the semaphore will be implemented in KernelSemaphore
	void wait()
	{
		KernelLock lock;
		KernelSemaphore::wait();
	}
	//the actual signal methode from the semaphore will be implemented in KernelSemaphore
	void signal()
	{
		KernelLock lock;
		KernelSemaphore::signal();
	}
};

#endif
