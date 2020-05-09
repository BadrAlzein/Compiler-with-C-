// Testprogramm fuer kooperative Threads

#include "device/CgaChannel.h"
#include "io/PrintStream.h"
#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"

// Hello: Eine kooperative Aktivitaet
//
// Anmerkung: Diese Klasse dient
// zu Testzwecken und der Einfacheit halber sind
// alle Methoden dieser Klasse ausnahmsweise inline deklariert
// Das sollte normalerweise *nicht* der Fall sein!
class Hello: public Activity {
public:
	Hello(const char* name, PrintStream& out, int count=10)
		: cout(out)
	{
		this->name = name;
		this->count = count;
	}

	Hello(const char* name, PrintStream& out, void* sp, int count=10)
		: Activity(sp), cout(out)
	{
		this->name = name;
		this->count = count;
		wakeup();
	}
	
	~Hello()
	{
	}
	
	void body()
	{
		
		for(int i=0; i<=count;i++){
			cout.print(name);
			cout.print(" ");
			cout.print(i);
			cout.println();

			if (count == 5) {
				if (i==1){
					cout.println("Letting Anton Sleep");
					cout.println("Berta is next");
					sleep();				
				} else if(i>1){
					cout.println("Exiting Anton");
					for(int j=0; j<3000000; j++){};
					cout.print(". ");
					for(int j=0; j<3000000; j++){};
					cout.print(". ");
					for(int j=0; j<3000000; j++){};
					cout.print(". ");
					for(int j=0; j<10000000; j++){};
					exit();
				} else {
					cout.println("Joining Anton to Berta");
					join();
				}
			}else if((count == 10) && (i == 8)){
				if (i>8){
	
				} else {
					cout.println("Joining Berta to Caesar");
					join();
				}
			} else if((count == 15) && (i == 12)){
				cout.println("Exiting Caesar and waking Anton");
				exit();
			}
			for(int j=0; j<1000000; j++){};
		}
		
	}

private:
	const char* name;
	PrintStream& cout;
	int count;
};

//////////////////////////////////////////////////////////////////////////
// Die Systemobjekte von Co-Stubs

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
	Hello anton("Anton", out, 5); // anton benutzt den Stack von main
	Hello berta("Berta", out, &stack0[1024], 10);
	Hello caesar("Caesar", out, &stack1[1024], 15);

	anton.join();


}

