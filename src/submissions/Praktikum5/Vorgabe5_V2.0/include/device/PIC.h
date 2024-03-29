#ifndef PIC_h
#define PIC_h

/*
 * PIC: Diese Klasse ist der Treiber fuer den
 *	Programmable Interrupt Controler (PIC)
 *
 *	Genaugenommen werden hier zwei kaskadierte PICs behandelt
 */


#include "io/IOPort.h"

class PIC {
public:
	// die Interrupt-Quellen von Co-Stubs

	enum Interrupts {
		PIT	 = 0,	// Programmable Interval Timer (PIT)
		KEYBOARD = 1	// Tastatur
	};

	PIC(): 	imr1(IMR1), imr2(IMR2),
		ctrl1(CTRL1), ctrl2(CTRL2) {}

	// Anstellen von Interrupt "num"
	void enable (int num);

	// Abstellen von Interrupt "num"
	void disable (int num);

	// Die Behandlung von Interrupt "num" best"atigen
	void ack (int num);

	// Unspezifische Best"atigung des aktuellen Interrupts
	void ack ();

private:
	enum Ports {
		IMR1 	= 0x21,	// Interrupt Mask Register von PIC 1
		IMR2 	= 0xa1,	// " PIC2
		CTRL1 	= 0x20,	// Interrupt Control Register von PIC 1
		CTRL2 	= 0xa0	// " PIC 2
	};

	enum Commands {
		ACK	= 0x20	// Bestaetigung fuer alle Interr.
		/** Comand 0x20 in PIC
		 * Note PIC 1 called Master and PIC 2 calles slave
		 * The Comand ACK is the end of interrupt (EOI) return if the interrupt ended 
		*/


	};

	IOPort8 imr1; //G14: The IMR specifies which interrupts are to be ignored 
	IOPort8 imr2;
	IOPort8 ctrl1; //G14: When a page fault occurs, the address the program attempted to access is stored in the CR2 register
	IOPort8 ctrl2;
};

extern PIC pic;

#endif
