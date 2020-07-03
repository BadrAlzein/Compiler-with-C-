// Testprogramm fuer sleep() und wakeup() in kooperativen Threads
// Basiert auf mainAct.cc!

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
        join();
    }

    void body()
    {
        if (count < 2) {
            count = 2;
        }

        for(int i=0; i<=count; i++) {
            cout.print(name);
            cout.print(" ");
            cout.print(i);
            cout.println();

            for (int i = 0; i < 4000; i++) {
                cout.print("\r|\r\\\r-\r/");
            };

            // nach 1/2 der Zeit schlafen legen und den nächsten weitermachen lassen
            if (i == (count / 2)) {
                wakeup();
                sleep();

                //exit();
            }

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

int main()
{
    Hello anton("Anton", out, 12); // anton benutzt den Stack von main
    Hello berta("Berta", out, &stack0[1024], 24);

    anton.body();
}

