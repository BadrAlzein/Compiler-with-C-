#include "device/Clock.h"
#include "interrupts/IntLock.h"
#include "device/PIT.h"
#include "interrupts/InterruptVector.h"
#include "thread/ActivityScheduler.h"

/**	Spaetere Initialisierung...
	 *	Hier ist nur im Konstruktor dafuer zu sorgen,
	 *	dass sich Gate korrekt initialisieren kann
	 */

/**
	 * Zur Behandlung der Interrupts: Jeder Interrupt-Quelle ist eine Vektornummer zugeordnet. 
	 * Diese Nummern sind in der vorgegebenen Enumeration InterruptVector . h deklariert. 
	 * Die Clock-Klasse muss sich von der vorgegebenen Klasse Gate.h ableiten,
	 *  dem Gate-Konstruktor die Vektornummer mitteilen und eine handle () Methode definieren, 
	 * um Interrupts behandeln zu können. 
	 * Gate sorgt dann automatisch dafür, dass ein Eintrag an 
	 * der richtigen Stelle der Vektortabelle erfolgt.
	 * Wenn alles korrekt ist, wird dann bei jedem Timer-Interrupt 
	 * automatisch Clock:: handle () aufgerufen.
	 * */
// initialise the clock
//programable interval time is deifned in PIT.cc
// initilalise the clock with the gate cause the class clock inherits the gate
//use PIT cause thats what the clock does, handels the interrupts created in PIT
Clock::Clock() : Gate(Timer), PIT()
{

	ticken = 0;
}

/**	Initialisierung des "Ticks" der Uhr
	 *	Standardmaessig setzen wir das
	 *	Uhrenintervall auf 20 Millisekunden
	 *	und wir bekommen damit 50 Interrupts pro Sekunde
	 *
	 *	Zum Testen koennt Ihr bei Bedarf einen hoeheren Wert einstellen
	 *	Weitere Hinweise zur Implementierung siehe "windup"
	 */
Clock::Clock(int us) : Gate(Timer), PIT(us)
{
	windup(us);
}

/**	Initialisierung des "Ticks" der Uhr
	 * 	Die Einheit sind Mikrosekunden.
	 * 	Hier ist der PIT geeignet zu initialisieren
	 * 	und der PIT beim PIC anzustellen.
	 */
void Clock::windup(int us)
{
	//interval length
	ticken = 0;
	pit.interval(us);

	// set the interrupts
	//Programmable Interrupt Controller ( PIC.h )
	//interuppt quellen sind auch in PIT und PIC.h difiniert
	// betreffende nummer des timers
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
	 */
     /**
	  * the gate object that is created for every interuppt will be added
	  * to logice-interupt table automatically and after this happend the interuppts 
	  * occured on every gate will be transfered to the driver via  handle method
	  * Sobald dies geschehen ist, werden alle an diesem Gate
      *	auftretenden Interrupts werden ueber die handle()-Methode an
      *	dem Treiber mitgeteilt.
	*/
    // if the ticks of the clock is equal to the qauntom reset the clock and reschedule it
void Clock::handle()
{
	IntLock lock; //save kritische Abschnitt
	//Ein geworfener Interrupt muss bestätigt werden, bevor er erneut geworfen werden kann.
	//ack confirms the thrown interrupt before it can be thrown again(damit ein Interrupt erneut auftreten kann)
	pic.ack();
	//1 second is 1000000 us(microseconds)
	//actual time is number of ticks multi by interval time 
	//brauche ich checkslice methode aus scheduler
/*
    if (((ticken % 50 == 0) &&  (ticken % 100 != 0)) && ((ticken % 150 != 0) && (ticken % 200 != 0)) ) {         out.print("\r|");
    }
    if(ticken % 100 == 0 && ticken % 150 != 0 && ticken % 200 != 0 && ticken % 50 == 0){
           out.print("\r/");
   
    }
    if (ticken % 150 == 0 && ((ticken % 200) != 0)){
      out.print("\r-");
    }
    if(ticken % 200 == 0 ){
           out.print("\r\\");
     //  out.println();
       this->ticken = 0;
    }
    this->ticken= ticks()+1;
    
*/
	/**** For mainPre****/
    this->ticken= ticks()+1;
	scheduler.checkSlice();
	//	}
}

/* 	Liefert die Systemzeit in Ticks zurueck
	 *	Kann hier "inline" implementiert werden

	 int ticks()
{
}
	 */
