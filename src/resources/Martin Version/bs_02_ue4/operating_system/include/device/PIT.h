#ifndef PIT_h
#define PIT_h

/*
 * PIT: Der Treiber fuer den Programmable Interval Timer
 *
 *	Wenn der PIT richtig programmiert wurde,
 *	liefert er alle "us" Mikrosekunden einen Interrupt.
 *
 *  -------------------------------Aufgaben-Kommentare-------------------------------------------
 *	Hier muss zunächst der Timer-Baustein programmiert werden. Dies geschieht in der Klasse PIT.h.
 *	Aufbauend auf dieser Klasse ist dann eine Klasse Clock.h zu implementieren, welche den vom
 * 	PIT.h generierten Interrupt behandelt.
 * 
 * PCs besitzen einen oder zwei Timer-Bausteine vom Typ 8253 oder 8254. 
 * Jeder dieser Bausteine besitzt drei 16 Bit breite Zähler, die mit einem Takt von 1,19318 MHz betrieben werden. 
 * Die Zählgeschwindigkeit ist also unabhängig vom Prozessortakt!
 * Und so werden die Zähler genutzt: 
 		1	0	Periodische Unterbrechungen
		1	1	Speicher-Refresh
		1	2	Tonerzeugung
		2	0	Fail-Safe-Timer (NMI)
		2	1	Ungenutzt
		2	2	Ungenutzt

		Jeder Zähler besitzt einen eigenen Ausgang (OUTx). 
		Je nach Anschluss dieses Ausgangs an verschiedene Stellen auf dem PC Motherboard ergeben sich die verschiedenen Spezialbedeutungen der Zähler (alles hart verdrahtet!). 
		So führt OUT0 an INT0 des PIC, 
		OUT1 an den Kanal 0-Eingang des DMA Controllers 8237, 
		OUT2 über ein programmierbares Gate an den Verstärker 
		und OUT0 des zweiten PIT an den NMI Eingang des Prozessor (über das NMI-Mask-Bit). 


		 Jeder PIT kann mit Hilfe von vier Ports angesprochen werden:
		Port (1.PIT)	Port (2.PIT)	Register	Zugriffsarten
		0x40	0x48	Zähler 0	schreiben/lesen
		0x41	0x49	Zähler 1	schreiben/lesen
		0x42	0x4a	Zähler 2	schreiben/lesen
		0x43	0x4b	Steuerregister	nur schreiben
		Alle Ports sind nur 8 Bits breit.

		Um 16 Bit Zählerwerte in den PIT zu bekommen wird eine besondere Technik benutzt. 
		Zunächst muss dem PIT über ein Steuerwort mitgeteilt werden, was man überhaupt von ihm will. Das Steuerwort hat den folgenden Aufbau:
		Bit(s)	Wert	Bedeutung
		6-7	Zählerauswahl
		00 	Zähler 0
		01 	Zähler 1
		10 	Zähler 2
		11 	ungültig beim 8253, Read-Back-Befehl beim 8254
		4-5	Lesen/Schreiben
		00 	Zähler-Latch-Befehl
		01 	nur niederwertiges Zählerbyte
		10 	nur höherwertiges Zählerbyte
		11 	niederwertiges, anschließend höherwertiges Zählerbyte
		1-3	Modus 0 bis Modus 5
		0 	Zählformat
		0 	binäre Zählung von 16 Bit
		1 	Zählung mit vierstelligen BCD Zahlen

Der Zähler-Latch-Befehl und der Read-Back-Befehl sind nur für das Auslesen von Zählerwerten von Interesse. Daher wird hier nicht weiter darauf eingegangen.
Der Modus bestimmt, wie der Zähler arbeitet und ob er mit Hilfe der OUTx Leitung externe Ereignisse auslöst. 
So zählt der Zähler im Modus 0 vom angegebenen Startwert bis 0 herunter (838 ns) pro Schritt und setzt am Ende die OUTx Leitung auf 1. 
Um periodische Impulse zu erzeugen, eignet sich am besten Modus 2. 
Dabei wird bei Erreichen des Wertes 0 ein kurzer Impuls auf OUTx ausgegeben und der Zähler wird automatisch wieder mit dem Startwert initialisiert, 
worauf der Vorgang wieder von vorn losgeht.

Zur Einstellung eines 16 Bit Zählerwertes sind damit drei out-Befehle notwendig. 
Der erste zum Übergeben des Steuerwortes und zwei weitere mit dem nieder- und dem höherwertigen Byte des Zählerwertes. 
 */

#include "io/IOPort.h"

class PIT
{
public:
	/** Default-Konstruktor. Das Interval wird spaeter
	  * mit der interval-Methode initialisiert */
	PIT();

	/** Initialisiert den Timers, sodass alle "us" Mikrosekunden ein Interrupt
	  * ausgeloest wird */
	explicit PIT(int us);

	/** Setzt das Timer-Intervall, sodass alle "us" Mikrosekunden ein Interrupt
	  * ausgeloest wird.
	  * 
	  * BEACHTE: Hier muss die Hardware korrekt programmiert werden.
	  * Naeheres steht in der Web-Dokumentation.
	  */
	void interval(int us);

	unsigned getInterValue() {
		return this->interValue;
	}

private:
	IOPort8 controlPort;
	IOPort8 dataPort;
	unsigned interValue;

	enum Values
	{
		TIME_BASE = 838 /* Dauer eines Zaehlticks in us */
	};

	// Die I/O Ports des PIC
	enum Ports
	{
		CONTROL_PORT = 0x43,
		DATA_PORT = 0x40
	};
};

extern PIT pit;
#endif
