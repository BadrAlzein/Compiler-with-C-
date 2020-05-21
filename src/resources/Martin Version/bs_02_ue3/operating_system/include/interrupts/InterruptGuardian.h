#ifndef InterruptGuardian_h
#define InterruptGuardian_h

#include "interrupts/InterruptVector.h"
#include "interrupts/Gate.h"

class InterruptGuardian
{
public:
	InterruptGuardian();

	//geändert von "static void handle(unsigned num);" zu [...]int num);
	static void handle(int num);

	//geändert von "static void registerGate(Gate *gate, unsigned num);" zu [...]int num);
	static void registerGate(Gate *gate, int num);

private:
	static Gate *vectorTable[NrOfInterrupts];
};

#endif
