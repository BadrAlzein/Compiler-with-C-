#include "thread/Coroutine.h"

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
    // Top of the stack can be 0 (defined in the constructor)
    if(tos == 0) {

    } else if (tos != 0) {
        Stack* tos_ptr = (Stack *)tos;
		// stack spacing for getting 1023 not 1024
		tos_ptr--;
		// vorhandene daten koennen nicht veraendert werden wenn 0 darin steht
		// abstrakte methode definieren
		// initialisiere methode coroutine mit startup methode die parameter Instanz benoetigt
		tos_ptr->coroutine = &startup;
		tos_ptr->ret = 0;
		// instanz von der klasse coroutine
		tos_ptr->param = this;
		// stack pointer zuweisen
		this->sp = tos_ptr;
    }
}
