#ifndef KernelSemaphore_h
#define KernelSemaphore_h


/**
 * KernelSemaphore: Semaphorenimplementation f�r kooperative
 * Prozesse oder zur Anwendung innerhalb des Kernels.
 * Implementiert zunächst die KernelSemaphore für den kooperativen Fall. Wie der Name andeutet,
wird diese innerhalb des Kerns benutzt. Überlegt euch, was dies für den Schutz von kritischen
Datenstrukturen bedeutet.
 */
#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"

class KernelSemaphore {
public:
	// Initialisierung des Zaehlers
	KernelSemaphore(int count = 1): space(count){}

	void wait();
	void signal();

private:
	Queue snake;
	// fluechtig fuer jeder Zeit veraenderbar
	/*
	Wert der Variable jederzeit ohne expliziten Zugriff im Quelltext ändern kann. 
	Dies geschieht beispielsweise durch andere Prozesse, Threads oder externe Hardware
	 */
	volatile unsigned int space;
};

#endif

