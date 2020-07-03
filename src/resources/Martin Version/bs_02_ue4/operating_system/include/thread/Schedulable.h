#ifndef Schedulable_h
#define Schedulable_h

/*
 * Schedulable: Diese Klasse implementiert ein Element
 *		der Ready-Liste des Schedulers
 *
 *	Anmerkung: Die Klasse ist von Chain abgeleitet,
 *	damit Instanzen dieser Klasse verkettet werden koennen.
 *	Hier wuerden typischerweise Informationen
 *	wie prozesspezifische Laufzeitstatistiken,
 *	Prioritaeten etc. verwaltet werden.
 *
 */
/*
Wenn unser erstes Scheduling erwartungsgemäß läuft, wollen wir nun jedem Prozess ein indi-
viduelles Zeitquantum (gemessen in den Ticks unserer Uhr) zuteilen. Dieses Quantum wird in
der vorgegebenen Klasse Schedulable . h verwaltet. Wir müssen nun den Scheduler ein wenig überarbeiten. 
Dem aktiven Prozess soll erst dann die CPU entzogen werden, wenn sein Quantum
abgelaufen ist. Führe dazu eine Methode checkSlice () beim Scheduler ein, die überprüft, ob die
Zeitscheibe des aktuell laufenden Prozesses abgelaufen ist.
*/
#include "lib/Chain.h"

class Schedulable : public Chain
{
public:
    /*
    jedem Prozess ein individuelles Zeitquantum (gemessen in den Ticks unserer Uhr) zuteilen. Dieses Quantum wird in
    der vorgegebenen Klasse Schedulable . h verwaltet.
    */
    explicit Schedulable(int slice = 1)
    {
        setQuantum(slice);
//	setDefault(slice);
    }

    void setQuantum(int slice)
    {
        this->slice = slice;
    }
	/*
    void setDefault(int slice) {
	
	this->defaultSlice = slice;
    }	*/

    int getQuantum()
    {
        return slice;
    }
/*
    void resetQuantum() {

	this->slice = this->defaultSlice;
    }
*/
private:
    int slice = 0;
};

#endif
