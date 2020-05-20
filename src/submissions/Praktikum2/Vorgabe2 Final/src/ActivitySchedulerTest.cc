#include "device/CgaChannel.h"
#include "io/PrintStream.h"
#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"

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
            //testing begint
            
            //sleep Test
			if (count == 5 && i==count-3) {
                 cout.println("Anton Sleep for one time");
                    for(int j=0; j<pause ; j++){};
                    sleep();
            } 
			else if((count == 7 && i == count)){
					cout.println("finish Berta and start Caesar");
					join();
            }else if((count == 15 && i == count)){
				cout.println("end Caesar");
				exit();
			}
		
		//break every output
        for(int j=0; j<pause; j++){};
		}
		
	}

private:
	const char* name;
	PrintStream& cout;
    const long long  pause= 4000000;
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
	Hello berta("Berta", out, &stack0[1024], 7);
	Hello caesar("Caesar", out, &stack1[1024], 15);

	anton.body();
}



