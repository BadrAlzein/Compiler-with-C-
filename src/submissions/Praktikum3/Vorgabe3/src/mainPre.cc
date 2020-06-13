// Testprogramm fuer kooperative Threads

#include "device/CgaChannel.h"
#include "device/CPU.h"
#include "io/PrintStream.h"
#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"
#include "device/PIC.h"
#include "device/Clock.h"
#include "interrupts/InterruptGuardian.h"
#include "interrupts/IntLock.h"

// Hello: Eine kooperative Aktivitaet
//
// Anmerkung: Diese Klasse dient
// zu Testzwecken und der Einfacheit halber sind
// alle Methoden dieser Klasse ausnahmsweise inline deklariert
// Das sollte normalerweise *nicht* der Fall sein!
class Hello: public Activity {
public:
	Hello(const char* name, PrintStream& out, int quantum)
		: Activity(quantum), cout(out)
	{
		this->name = name;
	}

	Hello(const char* name, PrintStream& out, void* sp, int quantum)
		: Activity(sp,quantum), cout(out)
	{
		this->name = name;
		wakeup();
	}

	~Hello()
	{
		cout.print("Dest  Anfang" );
		cout.println(name);
		join();
		cout.print("Dest  Ende" );
		cout.println(name);
	}

	void body() {
		for(int i=0; i<10; i++) {
				IntLock lock;
                //cout.print(clock.ticks());
				cout.print(name);
				cout.print(" ");
				cout.print(i);
				cout.println();
				for (int i =0; i<10000000; i++){}
		}
		
	}

private:
	const char* name;
	int count;
	PrintStream& cout;
};

//////////////////////////////////////////////////////////////////////////
// Die Systemobjekte von Co-Stubs

CPU cpu;

InterruptGuardian interruptGuardian;
PIC pic;
PIT pit;
Clock clock(2500);

// globale Ein-/Ausgabeobjekte
CgaChannel cga;         // unser CGA-Ausgabekanal
PrintStream out(cga);   // unseren PrintStream mit Ausgabekanal verknuepfen

// Objekte der Prozessverwaltung
ActivityScheduler scheduler;   // der Scheduler

// die Stacks fuer unsere Prozesse/Coroutinen
unsigned stack0[1024];
unsigned stack1[1024];

int main()
{
	Hello anton("Anton", out, 1000000); // anton benutzt den Stack von main
	Hello berta("Berta", out, &stack0[1024], 1);
	Hello caesar("Caesar", out, &stack1[1024], 1);

	cpu.enableInterrupts();
	anton.body();
}
