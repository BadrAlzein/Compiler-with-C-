#include "device/PIT.h"


/** Default-Konstruktor. Das Interval wird spaeter
	  * mit der interval-Methode initialisiert */
PIT::PIT():controlPort(CONTROL_PORT), dataPort(DATA_PORT) {}

/** Initialisiert den Timers, sodass alle "us" Mikrosekunden ein Interrupt
 * ausgeloest wird */
PIT::PIT(int us) :controlPort(CONTROL_PORT), dataPort(DATA_PORT) 
{
	//this->controlPort = CONTROL_PORT;
	//this->dataPort = DATA_PORT;
	interval(us); //set the interval of (us) 
}

/** Setzt das Timer-Intervall, sodass alle "us" Mikrosekunden ein Interrupt
* ausgeloest wird.
* 
* BEACHTE: Hier muss die Hardware korrekt programmiert werden.
* Naeheres steht in der Web-Dokumentation.
*/
void PIT::interval(int us)
{
	/*
	every Step is from startValue until 0 d.h. 838ns 
	TODO: delay the interrupt in (us) amout of steps -> that means us * 838ns
	*/
	interValue = us * TIME_BASE;
	
	/** Controling the Hardware*/

	/*
	 * PIT is 16 byte Counter but the ports are all 8 bytes -> use steuerwort 
	 *  to every Steuerwort use : 
	 * 1. Bit0 is 0 binary 
	 * 2. Bit1-3: Modus 2. Dabei wird bei Erreichen des Wertes 0 ein kurzer Impuls auf OUTx 
	 * 	  ausgegeben und der Zähler wird automatisch wieder mit dem Startwert initialisiert,
	 * 	  worauf der Vorgang wieder von vorn losgeht. 
	 * 3. Bit4-5: use 10/01 to register the first and secound 6 bytes into the PIT
	 * 4. Bit6-7: use one of the Counter -> use counter0
	 **/

//(Pending) -> dataPort

	//write the low bytes of interValue
	controlPort.write(0b00010100); //low ->Bit4-5 is 01 -> 00 (01) 010 0
	dataPort.write(((char)(interValue &0xff))); //let (8-1 bits) in & 0xff

	//write the high bytes of interValue
	controlPort.write(0b00100100); //high ->Bit4-5 is 10 -> 00 (01) 010 0
	dataPort.write(((char)((8>>interValue) &0xff)));//let (16-8 bits) in & 0xff


}
