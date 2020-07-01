// Code eher als Pseudocode gemeint

#include "device/Clock.h" // "#include" sucht automatisch im include-Ordner
#include "device/PIT.h"
#include "interrupts/InterruptVector.h"
#include "thread/ActivityScheduler.h"
#include "sync/Monitor.h"

/**	Spaetere Initialisierung...
 *	Hier ist nur im Konstruktor dafuer zu sorgen,
 *	dass sich Gate korrekt initialisieren kann
*/
Clock::Clock() : Gate(Timer), PIT() {
    tick = 0;
}

/**	Initialisierung des "Ticks" der Uhr
 *	Standardmaessig setzen wir das
 *	Uhrenintervall auf 20 Millisekunden
 *	und wir bekommen damit 50 Interrupts pro Sekunde
 *
 *	Zum Testen koennt Ihr bei Bedarf einen hoeheren Wert einstellen
 *	Weitere Hinweise zur Implementierung siehe "windup"
 */
Clock::Clock(int us) : Gate(Timer), PIT(us) {
    tick = 0;
    windup(us);

}

/**	Initialisierung des "Ticks" der Uhr
 * 	Die Einheit sind Mikrosekunden.
 * 	Hier ist der PIT geeignet zu initialisieren
 * 	und der PIT beim PIC anzustellen.
 */
void Clock::windup(int us) {
    // Intervallänge setzen
	interval(us);
	// Interrupts setzen
	pic.enable(PIC::PIT);
}

/**
 * Edit R:
 * @return
 *          true:   epilogue exists
 *          false:  epilogue does not exist
 */
bool Clock::prologue() {

    pic.ack();
    // return-Wert wird durch InterruptGuardian.cc verarbeitet
    return true; // bei uns immer, da immer ein epilogue() vorhanden (wenn nicht: false)

}

void Clock::epilogue() {

    scheduler.checkSlice();

}
