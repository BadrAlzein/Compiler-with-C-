#include "device/PIC.h"

/**
 * this class implements the head PIC.h and work as a control class for 
 * Programmable Interrupt Controler (PIC) 
*/

	// Anstellen von Interrupt "num"
	void enable (int num);

	// Abstellen von Interrupt "num"
	void disable (int num);

	// Die Behandlung von Interrupt "num" best"atigen
	void ack (int num);

	// Unspezifische Best"atigung des aktuellen Interrupts
	void ack ();