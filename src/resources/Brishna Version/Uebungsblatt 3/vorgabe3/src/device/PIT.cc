#include "../include/device/PIT.h"

/** Default-Konstruktor. Das Interval wird spaeter
	  * mit der interval-Methode initialisiert */

/* Edit Robert:
 *
 *      us (Intervallänge) ist nicht gegeben.
 *      Es muss nach Aufruf des Konstruktors nochmal
 *          interval(us);
 *      aufgerufen werden.
 *
 *      In diesem Konstruktor ist es nur wichtig, dass die IOPorts korrekt initialisiert werden.
 *
 */
PIT::PIT()
    : controlPort(CONTROL_PORT),
      dataPort(DATA_PORT)
{

}


/** Initialisieren des Timers, sodass alle "us" Mikrosekunden ein Interrupt
  * ausgeloest wird
  */

/* Edit Robert:
 *
 *      us (Intervallänge) ist gegeben.
 *      Es ist kein seperater Aufruf von 'interval(us);' nötig.
 *      Dies wird von diesem Konstruktor erledigt, da die Intervallänge bekannt ist.
 *
 *      Darüber hinaus müssen die IOPorts initialisiert werden.
 *
 */
PIT::PIT (int us)
    : controlPort(CONTROL_PORT),
      dataPort(DATA_PORT)
{
    // Achtung: explicit!

    // us bereits gegeben
    // Interval muss nicht mehr seperat aufgerufen werden.
    interval(us);
}

/** Setzt das Timer-Intervall, sodass alle "us" Mikrosekunden ein Interrupt
  * ausgeloest wird.
  *
  * BEACHTE: Hier muss die Hardware korrekt programmiert werden.
  * Naeheres steht in der Web-Dokumentation.
  */

/** Edit Robert
 *
 *      Diese Funktion soll die Hardware beschreiben, so dass diese alle x Zeiteinheiten einen Interrupt auslöst.
 *      Zum konkreten beschreiben findet man Informationen in der Web-Dokumentation
 *      (hab ich auch noch nicht alles verstanden).
 *
 *      Diese Funktion wird ganz am Anfang aufgerufen, um eine Intervallänge zu setzen.
 *      Danach immer, wenn das Interval verändert werden soll.
 *
 *      @param us
 *                  Intervallänge in Mikrosekunden.
 */
void PIT::interval (int us) {
    /*
    GEDANKENSTUETZE für den vergesslichen Tim

    // 1 Tick = 838 ns (Nanosekunden) = 0.838 us (Mikrosekunden)
    if ([Anz. Ticks] == this.interv) {
        [Interrupt ausloesen!]
    }

    Edit Robert:
        Findet Robert gut so. So ists leicht zu verstehen.
        Hätte aber lieber ne Gleichung. Aber nicht wichtig jetzt.

    Edit Tim:
        Fände Tim auch besser, aber mir ist noch nichts besseres
        eingefallen als die while-Schleife...
    */

    this->interv = us;

    int ns = us * 1000;
    int reqTicks = 1; // required amount of ticks
    int timeBase = (TIME_BASE);

    while ((reqTicks * timeBase) <= ns) {
        reqTicks++;
    }


    // 0xFF = 0b 1111 1111


    controlPort.write(CONTROL_WORD);
    dataPort.write(reqTicks & (0xff));
    reqTicks = reqTicks >> 8;
    dataPort.write(reqTicks & (0xff));

}
