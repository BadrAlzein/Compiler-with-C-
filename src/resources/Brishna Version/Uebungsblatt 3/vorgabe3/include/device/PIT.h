#ifndef PIT_h
#define PIT_h

/*
 * PIT: Der Treiber fuer den Programmable Interval Timer
 *
 *	Wenn der PIT richtig programmiert wurde,
 *	liefert er alle "us" Mikrosekunden einen Interrupt
 */

#include "io/IOPort.h"

class PIT {

protected:
    IOPort8 controlPort;
    IOPort8 dataPort;

public:

	/** Default-Konstruktor. Das Interval wird spaeter
	  * mit der interval-Methode initialisiert */
	PIT ();

	/** Initialisiert den Timers, sodass alle "us" Mikrosekunden ein Interrupt
	  * ausgeloest wird */
	explicit PIT (int us);

	/** Setzt das Timer-Intervall, sodass alle "us" Mikrosekunden ein Interrupt
	  * ausgeloest wird.
	  *
	  * BEACHTE: Hier muss die Hardware korrekt programmiert werden.
	  * Naeheres steht in der Web-Dokumentation.
	  */
	void interval (int us);

private:
	enum Values {
		TIME_BASE = 838  /* Dauer eines Zaehlticks in ns */
	};

	// Die I/O Ports des PIT
	enum Ports {
		CONTROL_PORT      = 0x43,
		DATA_PORT         = 0x40
	};

    // Das hier drunter beschreibt, wie das Kontrollwort zusammengesetzt ist.
	// Zaehler 0 | niederwertiges, anschließend hoeherwertiges Zaehlerbyte | Modus 2 | binaere Zaehlung von 16 Bit
	// Modus 2 zaehlt von 838 bis 0, gibt einen Impuls und wiederholt das ganze
    // siehe Web-Dokumentation
	const int CONTROL_WORD = 0b00110100;

	int interv = 0;

};

extern PIT pit;
#endif
