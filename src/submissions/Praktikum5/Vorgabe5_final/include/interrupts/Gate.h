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
class Gate :public Chain{
public:
	// Definition eines Gates fuer Vektornummer "num"
	explicit Gate (int num);

	//  Automatisches Abmelden des Gates
	virtual ~Gate ();
/* P5- 4.1. handle is skipt after using monitor Pro & epilogue
	virtual void handle() = 0;
*/
	int getNumber()
	{
		return num;
	}

	/* Monitor */
	/**
	 * Während des Prologes sind die Interrupts gesperrt.
	 * Der Rückgabewert des Prologes bestimmt, ob der Epilog aufgerufen werden soll
	*/
	virtual bool prologue() = 0;
	//die Interrupts sind aktiv
	virtual void epilogue() {}
	
	/* Monitor is marked */
	bool isDeferred()
	{
		return deferred;
	}
	/* Monitor set marked */
	void setDeferred(bool newDeferred)
	{
		deferred = newDeferred;
	}

    // alle Klassen mit virtuellen Destruktoren brauchen die
    // folgende Operator-Ueberladung:
    static void operator delete(void* p) {}

private:
	int num;
	bool deferred; //is marked in the monitor
};

#endif
