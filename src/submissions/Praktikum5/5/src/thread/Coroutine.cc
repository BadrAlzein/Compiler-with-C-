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
void Coroutine::startup(Coroutine *object)
{
	/*
	sorgt dafür, dass in Coroutine :: startup () explizit für jede Coroutine die Interrupts angestellt werden
	Dies muss geschehen, bevor ihr body() aufruft.
	Wir müssen das so machen, weil wir in
	einem Interrupt-Handler einen Prozesswechsel durchführen. Die Interrupts sind deshalb solan-
	ge gesperrt, bis wir wieder aus dem Handler zurückkehren. Da neue Prozesse am Anfang noch
	niemals losgelaufen sind, sind sie auch noch nie unterbrochen worden. Wir müssen explizit ein-
	mal dafür sorgen, dass sie unterbrechbar sind. Die Interrupts können mit Hilfe der Klasse CPU.h
	angestellt und gesperrt werden.
	*/
	//Interrupts werden angestellt für jede neue Coroutine
	/*
	TODO
	Da jetzt nicht mehr über Interruptsperren synchronisiert wird, müsst ihr auch die Coroutinenim-
plementierung entsprechend anpassen. => keine enable Interrupts und kein CPU sondern Monitor
	 */
	// wenn der monitor verlassen, dann koennen wieder interrupts auftreten also interrupts enable
	monitor.leave();
	// seit uebung 5 entfernt cpu.enableInterrupts();
	//Coroutinebody will get called
	object->body();
	//Coroutinebody will be deleted
	object->exit();
}

/* 
Init new Coroutine
tos could be null pointer 
 */
void Coroutine::setup(void *tos)
{
	// tos is some storage address of the top of stack e.g. 756785
	if (tos == 0)
	{
		// if the top of stack pointer is a null pointer
		// then esp == 0, so constructor has its default no explicit address passed
		// so this is if no top of stack is initialized
		// Coroutine could use the Main stack
	}
	else if (tos != 0)
	{
		Stack *tos_ptr = (Stack *)tos;
		// stack spacing for getting 1023 not 1024
		tos_ptr--;
		// vorhandene daten koennen nicht veraendert werden wenn 0 darin steht
		tos_ptr->edi = 0;
		tos_ptr->esi = 0;
		tos_ptr->ebx = 0;
		tos_ptr->ebp = 0;
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
