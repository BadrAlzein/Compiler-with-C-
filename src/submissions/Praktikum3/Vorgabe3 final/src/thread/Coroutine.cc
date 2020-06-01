#include "thread/Coroutine.h"
#include "device/CPU.h"

/* Diese Funktion hat nur die Aufgabe
	 * den Rumpf der uebergebenen Coroutine aufzurufen
	 * und nach der Rueckkehr exit() aufzurufen,
	 * um die Termination des Rumpfes bekanntzugeben.
	 * Diese Prozedur dient so als eine Bruecke zwischen der
	 * nicht objektorientierten und der objektorientierten Welt
	 * Beachte, das "startup" als "static deklariert ist
	 * und deshalb keinen impliziten "this"-Zeiger uebergeben bekommt.
	 */
void Coroutine :: startup(Coroutine* obj) {
	//for every existing coroutine call enableInterrupts cause for every Interrupt Handler 
	// context switch should be called
	cpu.enableInterrupts();
    //create the body of the coroutine
    obj ->body();
    // terminate the coroutine
    obj -> exit();
}

/* Aufsetzen einer neuen Coroutine.
	 * Der Parameter "tos" (top of stack) ist der
	 * initiale Stackpointerwert fuer die neue Coroutine
	 * ACHTUNG: tos kann NULL sein (siehe Constructor)!
	 */

void Coroutine :: setup(void* tos) {
  if (tos != 0) {
        Stack* st = (Stack *)tos;
        /** set the couroutine to the methode startup 
         *  Startu act like the tinit in stackframe (die Methode die, die Coroutine startet)
         */
		st->coroutine = &startup;
		st->stackCoroutine = this;    
		this->sp = st;
    }
}
