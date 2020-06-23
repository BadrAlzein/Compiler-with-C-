#ifndef Init_h
#define Init_h

/** Die erste richtige Anwendung
 */
#include "system/Thread.h"
#include "system/Console.h"
#include "system/Environment.h"

class Init: public Thread {
 public:
 	// consol construcotr Console(InputChannel &input, OutputChannel &output) 
	 // Console initialization with keyboard and screen from enviromental variables.
	 /*
	 input 
	 extern Keyboard keyboard;
	 output
	extern CgaChannel screen;
	  */
 	Init(int slice=1): 
	Thread(slice), shell(keyboard, screen)
	{
	}
	
	~Init()
	{
		this->join();
	}
	
	virtual void run();
 private:
	Console shell;
};

#endif
