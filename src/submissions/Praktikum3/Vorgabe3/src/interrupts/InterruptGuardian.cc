#include "interrupts/InterruptGuardian.h"

#include "interrupts/PanicGate.h"
extern PanicGate panicGate;

static bool initialized = false; //check if the vector table intialisiert oder nicht  
Gate* InterruptGuardian::vectorTable[NrOfInterrupts]; //by default all elem in the table is panicGate
extern "C" void guardian(int num);

void guardian(int num)
{
	InterruptGuardian::handle(num);
}

InterruptGuardian::InterruptGuardian()
{
	/**if the vector table is never been used 
	 * then fill it with the panic Gate as default
	 * */
	if(!initialized){
		for(int i=0; i<NrOfInterrupts; i++){
			vectorTable[i] = &panicGate;
		}
		initialized = true;
	}
}

//excute the handel routine to the given interrupt number 
//-> take it out of the interrupt table and handel it

void InterruptGuardian::handle(int num)
{
	vectorTable[num]->handle();
}

void InterruptGuardian::registerGate(Gate* gate,int num)
{
	/**if the vector table is never been used 
	 * then fill it with the panic Gate as default
	 * */
	if(!initialized){
		for(int i=0; i<NrOfInterrupts; i++){
			vectorTable[i] = &panicGate;
		}
		initialized = true;
	}
	//if the entered interrrupt number in Range then register it in the vector Table
	if((num >= -1) && (num < NrOfInterrupts)){
		vectorTable[num] = gate;
	}
}

