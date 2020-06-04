// Testprogramm fuer kooperative Threads

#include "device/CgaChannel.h"
#include "io/PrintStream.h"
#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"
#include "interrupts/InterruptGuardian.h"
#include "device/PIC.h"
#include "device/Clock.h"
#include "interrupts/Gate.h"
#include "interrupts/SpuriousGate.h"


CgaChannel cga;         // unser CGA-Ausgabekanal
PrintStream out(cga);   // unseren PrintStream mit Ausgabekanal verknuepfen
CPU cpu;
PIC pic;
InterruptGuardian interruptGuardian;
Clock clock(2000);

// Objekte der Prozessverwaltung
ActivityScheduler scheduler; 

int main() {

	cpu.enableInterrupts();
	while(1){

	}
    //cpu.enableInterrupts();
    //Clock clock = Clock();
    //clock.windup(2000);
    //out.print("Ich bin fertig.");

}
