#ifndef Gate_h
#define Gate_h

#include "lib/Chain.h"

/*
 * Gate: Ein Trap/Interrupt Tor
 *
 *     	Alle Treiber, die Geraete mit Interrupts steuern
 *     	muessen fuer jeden Interrupt ein Gate-Objekt anlegen.
 *	Die Gate-Objekte tragen sich selber in die logische
 *	Interrupt-Tabelle ein.
 *	Sobald dies geschehen ist, werden alle an diesem Gate
 *	auftretenden Interrupts ueber die handle()-Methode
 *	dem Treiber mitgeteilt.
 *
 *	Achtung: Gates muessen definiert sein,
 *	*bevor* der zugehoerige Interrupt zugelassen wird!!!!
 */
class Gate : public Chain
{
public:
	// default constructor
	Gate(){};

	// Definition eines Gates fuer Vektornummer "num"
	Gate(int num);

	//  Automatisches Abmelden des Gates
	virtual ~Gate();

	/** 	Nur was sofort in der Interruptbehandlung gemacht werden
	 *	muss, darf im Prolog gemacht werden.
	 Waehrend des Prologes sind die Interrupts gesperrt. Der Rückgabewert des Prologes bestimmt,
ob der Epilog aufgerufen werden soll. Beim Epilog sind die Interrupts aktiv.
	 */
	virtual bool prologue() = 0;

	/** Nicht jeder Interrupthandler muss einen Epilog haben.
	 */
	/*
	Diese entsprechenden Methoden pro-
	logue und epilogue muss jedes Gate implementieren.
	Waehrend des Prologes sind die Interrupts gesperrt. Der Rückgabewert des Prologes bestimmt,
    ob der Epilog aufgerufen werden soll. Beim Epilog sind die Interrupts aktiv.
	*/
	virtual void epilogue() {}

	// seit uebung 5 entfernt virtual void handle() = 0;

	int getNumber()
	{
		return num;
	}

	bool isDeferred()
	{
		return deferred;
	}

	void setDeferred(bool value)
	{
		deferred = value;
	}

	// alle Klassen mit virtuellen Destruktoren brauchen die
	// folgende Operator-Ueberladung:
	static void operator delete(void *p) {}

private:
	int num;
	bool deferred;
};

#endif
