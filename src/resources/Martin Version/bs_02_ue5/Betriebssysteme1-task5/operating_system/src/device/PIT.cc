#include "device/PIT.h"

/*  -------------------------------Aufgaben-Kommentare-------------------------------------------
 *	Hier muss zunächst der Timer-Baustein programmiert werden. Dies geschieht in der Klasse PIT.h.
 *	Aufbauend auf dieser Klasse ist dann eine Klasse Clock.h zu implementieren, welche den vom
 * 	PIT.h generierten Interrupt behandelt.
 * 
 *  bei Ablauf einer Zeitscheibe ein Reschedulingzu veranlassen und einen Prozesswechsel durchzuführen
 * Timers, der uns nach festgelegten Zeitintervallen regelmäßig unterbricht
 * regelmäßig einen Interrupt auslöst.
 *  nebenläufigen Zugriff auf gemeinsame Daten machen müssen. 
 * Hier gilt es,alle kritischen Abschnitte in CoStubs zu identifizieren und zu schützen.
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

/** Default-Konstruktor. Das Interval wird spaeter
	  * mit der interval-Methode initialisiert */
PIT::PIT()
: controlPort(CONTROL_PORT), dataPort(DATA_PORT) 
{
}

/** Initialisiert den Timers, sodass alle "us" Mikrosekunden ein Interrupt
 * ausgeloest wird */
PIT::PIT(int us)
: controlPort(CONTROL_PORT), dataPort(DATA_PORT) 
{
	this->interval(us);
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
	Zaehlerwert
	Dabei wird bei Erreichen des Wertes 0 ein kurzer Impuls auf OUTx ausgegeben und der Zähler wird automatisch wieder mit dem Startwert initialisiert, 
	worauf der Vorgang wieder von vorn losgeht. 

	wir nutzen nur den ersten PIT und der Zaehler davon ist 16 bit breit
	benutze nur periodische unterbrechnung also zaehler 0 und port 0x40 fuer das erste pit (lesen und schreiben)
	dazu nutzen wir noch das steuerregister Port 0x43 nur schreiben, da

	enum Ports
	{
		CONTROL_PORT = 0x43,
		DATA_PORT = 0x40
	};

	enum Values
	{
		TIME_BASE = 838 // dauer zaehltick in ns
	};

	Alle Ports sind nur 8 Bits breit.
	Aber der Zaehler ist 16 bit breit.
	Um 16 Bit Zählerwerte in den PIT zu bekommen wird eine besondere Technik benutzt. 

	Steuerwort teilt PIT mit, was gemacht werden soll.

	explicit IOPort8 (unsigned port): port(port) {}

	Schritte:
	1. Uebergebe 8 bit Steuerwort mit out befehl
		00100100 (waehlt zaehler 0 aus, die high bytes vom zaehler, modus 2 fuer periodische zaehlung, binaere zaehlung von 16 bit)
	2. Uebergebe hoeherwertiges byte des zaehlerwertes mit out befehl
	3. uebergabe des niederwertigen bytes des zaehlerwertes mit out befehl
	*/
	// herz pro takt -> alle us mikrosekunden wird ein interrupt ausgeloest
	// alles in microsekunden
	this->interValue = TIME_BASE * us;
	char intervalLowByte = (char) (0b11111111 & this->interValue);
	char intervalHighByte = (char) ((8 >> this->interValue) & 0b11111111);
	// 00100100 (waehlt zaehler 0 aus, die high bytes vom zaehler, modus 2 fuer periodische zaehlung, binaere zaehlung von 16 bit)
	char highByteControlWord = (char) 0b00100100;
	// 00010100 (waehlt zaehler 0 aus, die low bytes vom zaehler, modus 2 fuer periodische zaehlung, binaere zaehlung von 16 bit)
	char lowByteControlWord = (char) 0b00010100;
	// schreibe low interval byte 8 bit
	controlPort.write(lowByteControlWord);
	dataPort.write(intervalLowByte);
	// schreibe high interval byte 8 bit
	controlPort.write(highByteControlWord);
	dataPort.write(intervalHighByte);
}
