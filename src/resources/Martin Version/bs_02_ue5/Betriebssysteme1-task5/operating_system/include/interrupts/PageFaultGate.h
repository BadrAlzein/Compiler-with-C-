#ifndef PageFaultGate_h
#define PageFaultGate_h

#include "interrupts/Gate.h"

/*
 * 	PageFaultGate: behandelt PageFaults
 *
 *      Das PageFaultGate wird bei Speicherzugriffsverletzungen aktiviert,
 *      macht eine entsprechende Ausgabe und haelt die CPU an.
 */
class PageFaultGate: public Gate {
public:
	PageFaultGate();

	// seit uebung 5 entfernt void handle();
	bool prologue();
};

#endif
