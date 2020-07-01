#ifndef BoundedBuffer_h
#define BoundedBuffer_h
#include "thread/ActivityScheduler.h"
#include "interrupts/IntLock.h"

/** Diese Klasse stellt einen begrenzten synchronisierten
 *  Puffer dar, welcher von Interruptbehandlungsroutinen
 *  gef�llt werden kann.
 *
 *  Die Klasse ist eine Templateklasse. Das bedeutet f�r euch
 *  erstmal nur, das ihr alle Methoden hier im Header implementieren
 *  m�sst.
 */
template<typename T,unsigned size>
class BoundedBuffer {
public:
	BoundedBuffer(){}

	/** Diese Methode wird vom Interrupthandler aufgerufen, um
	 *  ein etwas in den Puffer zu schreiben. 
	 * //SECTION: buffer Voll 
	 *  Ist der Puffer voll,werden die zu schreibenden Daten verworfen.
	 * //SECTION: fair sync 
	 * Prozesse die auf eine Eingabe warten m�ssen hier geweckt werden.
	 */
	void add(T& elem)
	{	
		//if buffer not full
		if(population < size){
			population ++; //inc buffer counter
			buffer[pushPos] = elem; //add the elemet to the head 
			pushPos= (pushPos+1) % size; // inc the push Position (if pushPos=size -> 0) 

			//SECTION: fair sync 
			/** if there is any waiting Activity */
			if (suspendedAct !=0){
				Activity *wackedAct = suspendedAct;
				wackedAct->wakeup();//wakeup this
				suspendedAct=0;	//reset the  suspended Activity Trigger
			}
		}else {
		//SECTION: buffer Voll 
		//if the buffer full dont add anything
		//TODO: (not wanted)  delete the oldest elem and add the new elem 
 		}
	
	}

	/** Diese Methode wird von Prozessen aufgerufen, um Daten aus dem
	 *  Puffer zu lesen. 
	 * //SECTION:empty buffer
	 * Ist dieser leer wird der lesende Prozess schlafen gelegt.
	 * //SECTION: sync
	 * Achtet hier besonders auf die Synchronisierung.
	 */
	T get()
	{
		//SECTION: sync
		IntLock lock; //save this func from Synchronisierung mistakes
		popPos = (popPos+1) % size; //get the index of the wanted elem (if popPos=size -> 0)
		//SECTION:empty buffer
		if(population==0){
			suspendedAct = (Activity *) scheduler.active();
			scheduler.suspend(); //suspend the current activity 
		}
		population--; 

		/* get the last elem from buffer */
		if (popPos == 0) { //if the buffer voll 
			return buffer[size-1]; // -1 because of % size will set the pop on 0
		}else {
			return buffer[popPos-1];
		}
	}


private:
	T buffer[size];
	unsigned population = 0 ; //the population of the buffer
	unsigned pushPos = 0, popPos = 0 ;  //shows where to push/pop elements out of the buffer 
	Activity *suspendedAct = 0; //the suspended Activity 
};

#endif

