#ifndef Init_h
#define Init_h

/** Die erste richtige Anwendung
 */
#include "system/Thread.h"
#include "system/Console.h"
#include "system/Environment.h"

class Init: public Thread {
 public:
 Init(int slice=1) :
	Thread(slice), shell(keyboard, screen)
	{
	}
	
	~Init()
		{
			join();
		}
	
	virtual void run();
 private:
	Console shell;
};

#endif
