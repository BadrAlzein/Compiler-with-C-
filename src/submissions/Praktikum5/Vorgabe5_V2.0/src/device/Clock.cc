#include "device/Clock.h"
/* -------------------Aufgaben-Kommentare------------------------
 * Clock.h verwaltet unsere Systemzeit (in Ticks) und aktiviert
 * regelmäßig den Scheduler. Programmiert die Uhr so, dass alle 20ms ein Interrupt auftritt.
 * Testet die Uhr zunächst, ohne den Scheduler zu aktivieren. Gebt dazu einfach innerhalb der Uhr
 * ein einziges Zeichen (ohne Zeilenvorschub) aus. Wenn ihr dieses Zeichen regelmäßig seht, habt
 * ihr den Baustein prinzipiell korrekt programmiert und den Interrupt soweit richtig behandelt.
 * Überprüft nun die korrekte Zeiteinstellung, indem ihr an einer fixen Bildschirmposition einen
 * kleinen Propeller jede Sekunde ein Stück weiterdreht. Schaut zur Kontrolle auf eine Uhr. Der
 * Propeller ist während der Abgabe zu zeigen!
 */
/**	Spaetere Initialisierung...
*	Hier ist nur im Konstruktor dafuer zu sorgen,
*	dass sich Gate korrekt initialisieren kann
*/
// gate braucht im konstruktor vektornummer
/*
enum InterruptVector {
	Panic 			= -1,
	PageFault 		= 14,
	Timer 			= 32,
	KeyboardInterrupt 	= 33,
	SpuriousInterrupt	= 39,
	NrOfInterrupts 		= 64
};
// Definition eines Gates fuer Vektornummer "num"
explicit Gate (int num);
Vektornummer fuer das Gate ist 32 also fuer timer und wir wollen einen timer fuer die clock initialisieren
Zur Behandlung der Interrupts: Jeder Interrupt-Quelle ist eine Vektornummer zugeordnet. Diese
Nummern sind in der vorgegebenen Enumeration InterruptVector . h deklariert.
Die Clock-Klasse
muss sich von der vorgegebenen Klasse Gate.h ableiten, dem Gate-Konstruktor die Vektornum-
mer mitteilen und eine handle () Methode definieren, um Interrupts behandeln zu können.
Gate sorgt dann automatisch dafür, dass ein Eintrag an der richtigen Stelle der Vektortabelle erfolgt.
Wenn alles korrekt ist, wird dann bei jedem Timer-Interrupt automatisch Clock :: handle () aufgeru-
fen.
*/
Clock::Clock()
	: Gate(Timer), PIT()
{
	// dass sich Gate korrekt initialisieren kann => gate muss in initialisierungsliste initialisiert werden mit timer vektornummer 32
	// gate kann sich jetzt korrekt initialisieren
	this->touretteTicks = 0;
}

/*	Initialisierung des "Ticks" der Uhr
 *	Standardmaessig setzen wir das
 *	Uhrenintervall auf 20 Millisekunden
 *	und wir bekommen damit 50 Interrupts pro Sekunde
 *
 *	Zum Testen koennt Ihr bei Bedarf einen hoeheren Wert einstellen
 *	Weitere Hinweise zur Implementierung siehe "windup"
 *
 * - gate braucht im konstruktor vektornummer
 *
 * enum InterruptVector {
 *	Panic 			= -1,
 *	PageFault 		= 14,
 *	Timer 			= 32,
 *	KeyboardInterrupt 	= 33,
 *	SpuriousInterrupt	= 39,
 *	NrOfInterrupts 		= 64
 * };
 * - Definition eines Gates fuer Vektornummer "num"
 *   explicit Gate (int num);
 * - Vektornummer fuer das Gate ist 32 also fuer timer und wir wollen einen timer fuer die clock initialisieren
 */
Clock::Clock(int us)
	: Gate(Timer), PIT(us)
{
	/*  dass sich Gate korrekt initialisieren kann => gate muss in initialisierungsliste initialisiert werden mit timer vektornummer 32
	 *	- Initialisierung des "Ticks" der Uhr
	 * 	- Einheit sind Mikrosekunden.
	 * 	- Hier ist der PIT geeignet zu initialisieren
	 * 	  und der PIT beim PIC anzustellen.
	 * void Clock::windup(int us)
	 */
	this->windup(us);
}

/**	Initialisierung des "Ticks" der Uhr
 * 	Die Einheit sind Mikrosekunden.
 * 	Hier ist der PIT geeignet zu initialisieren
 * 	und der PIT beim PIC anzustellen.
 */
void Clock::windup(int us)
{
	// initialisieren des ticks der uhr also 0
	this->touretteTicks = 0;
	// pit initialisieren
	pit.interval(us);
	/*  PIT wird beim PIC angestellt
	 *  die Interrupt-Quellen von Co-Stubs
	 * 
	 *  enum Interrupts {
	 *	PIT	 = 0,	// Programmable Interval Timer (PIT)
	 * 	KEYBOARD = 1	// Tastatur
	 * };
	 * 
	 * - Anstellen von Interrupt "num" => also nummer 0 fuer den pit interrupt
	 * void enable (int num);
	 * Hier ist noch zu beachten, dass alle Interrupt-Quellen von einem externen Baustein verwaltet
	werden, dem Programmable Interrupt Controller ( PIC.h ). Jede Interrupt-Quelle muss explizit über
	diesen Baustein angestellt werden, sonst wird er nicht zur CPU durchgeleitet.
		In der vorgegebenen Klasse PIC.h sind alle
	Steuerfunktionen für den PIC.h definiert. Ferner sind dort auch die Interrupt-Quellen vermerkt.
	PIC::PIT ist die betreffende Nummer unseres Timers.
	 */
	pic.enable(PIC::PIT);
}

/** 	Der Interrupt-Handler fuer die Uhr.
	 *	Hier ist der Interrupt am PIC zu bestaetigen
	 *	und die Systemzeit zu aktualisieren.
	 *	Die Systemzeit wird in Uhrenticks gemessen,
	 *	Ihr muesst hier also nur mitzaehlen,
	 *	wie oft die Uhr getickt hat.
	 *
	 *	Ueberpruefe zunaechst die Funktion des Timers
	 *	indem Du jede Sekunde eine Ausgabe an der Bildschirmstelle (0,0)
	 *	in Form eines rotierenden Propellers machst, der sich pro Sekunde
	 *	ein kleines Stueck weiterdreht, wie der Sekundenzeiger einer Uhr.
	 *	Der Propeller besteht aus der Zeichenfolge '/', '-', '\\', '|',
	 *	d.h. nach 4 Sekunden ist eine komplette Umdrehung geschafft.
	 *
	 *	Achtung: Kommentiert alle anderen Ausgaben Eures Testprogrammes
	 *	aus, sonst seht Ihr nichts!
	 *
	 *	Wenn der Uhrentest erfolgreich verlaufen ist, kommentiert
	 *	den Propeller wieder aus und ruft stattdessen
	 *	die "checkSlice" Methode des Schedulers auf,
	 *	um diesen ggf. zum praeemptiven Rescheduling zu veranlassen.
     *
	 *-------------------------------Aufgaben-Kommentare---------------------------
     * Die Clock-Klasse
     * muss sich von der vorgegebenen Klasse Gate.h ableiten, dem Gate-Konstruktor die Vektornummer
     * mitteilen und eine handle () Methode definieren, um Interrupts behandeln zu können. Gate
     * sorgt dann automatisch dafür, dass ein Eintrag an der richtigen Stelle der Vektortabelle erfolgt.
     * Wenn alles korrekt ist, wird dann bei jedem Timer-Interrupt automatisch Clock:: handle () aufgerufen
     * void Clock::handle();
     */
void Clock::epilogue()
{
	/*
	
	durch den monitor ist nur ein processwechsel im BS kern erlaubt, deswegen processwechsel muss in epilog erfolgen. 
	 */

	scheduler.checkSlice();
	
}

bool Clock::prologue()
{
	//pic.ack wartet auf eine bestatigung der ubergegebene interrupt, solange the Interuppt nicht komplett 
	//ausgelost ist,wird kein neue Interuppt erluabt
	
	this->touretteTicks = this->ticks() + 1;
	pic.ack(PIC::PIT);
	return true;
}

/* 
void Clock::handle()
{
	*/
/*
	 * Hier ist noch zu beachten, dass alle Interrupt-Quellen von einem externen Baustein verwaltet
	 * werden, dem Programmable Interrupt Controller ( PIC.h ). Jede Interrupt-Quelle muss explizit über
	 * diesen Baustein angestellt werden, sonst wird er nicht zur CPU durchgeleitet.
	 * 
	 * 
	 *  Hier ist der Interrupt am PIC zu bestaetigen
	 *
	 * - Die Behandlung von Interrupt "num" bestaetigen
	 * void ack (int num);
	 * - Unspezifische Bestaetigung des aktuellen Interrupts
	 * void ack ();
	 */
// pic.ack();
/*
	 *  Systemzeit zu aktualisieren.
	 *	Die Systemzeit wird in Uhrenticks gemessen,
	 *	Ihr muesst hier also nur mitzaehlen,
	 *	wie oft die Uhr getickt hat.
	 */
// this->touretteTicks = this->ticks() + 1;
/*
	 *	Ueberpruefe zunaechst die Funktion des Timers
	 *	indem Du jede Sekunde eine Ausgabe an der Bildschirmstelle (0,0)
	 *	in Form eines rotierenden Propellers machst, der sich pro Sekunde
	 *	ein kleines Stueck weiterdreht, wie der Sekundenzeiger einer Uhr.
	 *	Der Propeller besteht aus der Zeichenfolge '/', '–', '\', '|',
	 *	d.h. nach 4 Sekunden ist eine komplette Umdrehung geschafft.
	 *
	 *	Achtung: Kommentiert alle anderen Ausgaben Eures Testprogrammes
	 *	aus, sonst seht Ihr nichts!
	 *
	 *	Wenn der Uhrentest erfolgreich verlaufen ist, kommentiert
	 *	den Propeller wieder aus und ruft stattdessen
	 *	die "checkSlice" Methode des Schedulers auf,
	 *	um diesen ggf. zum praeemptiven Rescheduling zu veranlassen.
	 * 
	 *  - 1000000 mikrosekunden sind 1 sekunde !!!!
	 *  - interval ist in mikrosekunden angegeben also interval durch 100000 mikrosekunden sind angabe in sekunden
	 *
	 * 
	 * - aktuelle zeit ist anzahl der ticks mal eine interval zeit => komplette zeit
	 * int intervalInSeconds = (this->getInterValue() / 1000000);
	 * int seconds = this->ticks() / intervalInSeconds;
	 * - ohne Zeilenvorschub ist \r 
	 * switch (seconds % 4)
	 * {
	 *  case 0:
	 *  out.print("\r/");
	 * 	break;
	 * case 1:
	 * 	out.print("\r-");
	 * 	break;
	 * case 2:
	 * 	out.print("\r\\");
	 * 	break;
	 * case 3:
	 * 	out.print("\r|");
	 * 	break;
	 * default:
	 * 	out.print("This should never happen.");
	 * }
	 */

/* veranlasst den Scheduler praeemptives Scheduling zu betreiben
	 * checkSlice aus ActivityScheduler aufrufen
	 * every 20 ms it calls checkSlice()
	 */
// if ((this->ticks() / this->getInterValue()) % 20 == 0)
// {
/*
		 * Wenn ja, soll checkSlice () ein Re-
		 * scheduling veranlassen. Ruft von nun an in Clock :: handle () checkSlice () anstelle von reschedule ()
		 * auf.
		 */
// scheduler.checkSlice();
// }
// }
