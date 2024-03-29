#ifndef SpuriousGate_h
#define SpuriousGate_h

#include "interrupts/Gate.h"

/*
 * 	PageFaultGate: behandelt PageFaults
 *
 *      Das PageFaultGate wird bei Speicherzugriffsverletzungen aktiviert,
 *      macht eine entsprechende Ausgabe und haelt die CPU an.
 */
class SpuriousGate: public Gate {
public:
	SpuriousGate();

	// seit uebung 5 entfernt void handle();
	bool prologue();
};

#endif
