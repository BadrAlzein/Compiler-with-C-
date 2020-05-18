// Testprogramm fuer Coroutinen

#include "device/CgaChannel.h"
#include "io/PrintStream.h"
#include "thread/Coroutine.h"

// Eine Coroutinen-Klasse
//
// Anmerkung: Diese Klasse dient
// zu Testzwecken und der Einfacheit halber sind
// alle Methoden dieser Klasse ausnahmsweise inline deklariert
// Das sollte normalerweise *nicht* der Fall sein!
// Klasse Hello erbt von Coroutine
class Hello: public Coroutine {
public:
	// Konstruktor Uebergabe von string namen und Printstream Objekt
	// initialisierung von PrintStream Objekt
	Hello(const char* name, PrintStream& out)
		: cout(out)
	{
		// Initialisierung von name
		this->name = name;
	}

	// Konstruktor Uebergabe von string namen und PrintStream Objekt und leerer Pointer 
	// initialisiere den leeren Pointer mit Coroutine Objekt Instanz Konstruktoraufruf 
	Hello(const char* name, PrintStream& out, void* sp)
		: Coroutine(sp), cout(out)
	{
		// initialisiere den namen
		this->name = name;
	}

	// verbinde die Klasse mit der naechsten Coroutine
	void link(Coroutine& next)
	{
		// this->next ist ein pointer auf eine Coroutine 
		// folglich muss die speicheradresse uebergeben werden
		this->next = &next;
	}

	// Der Name und die Zahl vom Hello Objekt wird so lange ausgegeben 
	// bis die 99 iteration abgeschlossen ist
	// Nach dem die Iteration vollfuehrt ist, gibt die Aktivitaet den Kontrollfluss ab
	void body()
	{
		for(int i=0; i<200; i++) {
			cout.print(name);
			cout.print(" ");
			cout.print(i);
			cout.println();
			// Kontrolltransfer von dieser Coroutine zu "next"
	 		// Die eigentliche Arbeit erledigt "switchContext"
			resume(next);
		}
	}

	// printe Panic!!! und eine neue Zeile 
	void exit()
	{
		cout.print("Panic!!!!");
		cout.println();
	}

	// public attribute fuer name von Hello naechste Coroutine Zeiger und PrintStream Objekt
	const char* name;
	Coroutine* next;

	PrintStream& cout;
};

//////////////////////////////////////////////////////////////////////////
// Die Systemobjekte von Co-Stubs

// globale Ein-/Ausgabeobjekte

CgaChannel cga;         // unser CGA-Ausgabekanal
PrintStream out(cga);   // unseren PrintStream mit Ausgabekanal verknuepfen

// die Stacks fuer unsere Prozesse/Coroutinen

unsigned stack0[1024];
unsigned stack1[1024];

int main()
{
	Hello anton("Anton", out); // anton benutzt den Stack von main
	Hello berta("Berta", out, &stack0[1024]);
	Hello caesar("Caesar", out, &stack1[1024]);

	// alle Coroutinen zyklisch verketten
	anton.link(berta);
	berta.link(caesar);
	caesar.link(anton);

	// los geht's
	anton.body();
}
