#ifndef BoundedBuffer_h
#define BoundedBuffer_h

#include "lib/Queue.h"
#include "thread/ActivityScheduler.h"
#include "interrupts/IntLock.h"
#include "io/PrintStream.h"

extern PrintStream out;

/** Diese Klasse stellt einen begrenzten synchronisierten
 *  Puffer dar, welcher von Interruptbehandlungsroutinen
 *  gef�llt werden kann.
 *
 *  Die Klasse ist eine Templateklasse. Das bedeutet f�r euch
 *  erstmal nur, das ihr alle Methoden hier im Header implementieren
 *  m�sst.
 */
template <typename T, unsigned size>
class BoundedBuffer
{
public:
	BoundedBuffer()
	{
		// amount of elements in buffer
		sheeps = 0;
		// pointer for buffer in get method
		getPointer = 0;
		// pointer for buffer in add method
		addPointer = 0;
		// one pointer on sleeper
		sleeper = 0;
	}

	/** Diese Methode wird vom Interrupthandler aufgerufen, um
	 *  ein etwas in den Puffer zu schreiben. Ist der Puffer voll,
	 *  werden die zu schreibenden Daten verworfen.
	 *  Prozesse die auf eine Eingabe warten m�ssen hier geweckt werden.
	 */
	void add(T &elem)
	{
		// test if the buffer is full => get method could decrease the sheeps so amount of elements in buffer
		if (this->sheeps < (int) size)
		{
			// index 0 could be written because addPointer is 0 at beginning
			this->buffer[addPointer] = elem;
			this->addPointer = (this->addPointer + 1) % size;
			// counter for the written codes
			this->sheeps++;
			// after we increased an added element then we could safely wake up another sleeper to read the element out of the buffer 
			// if we got a sleeper then wake him up
			if (this->sleeper != 0)
			{
				// this is the read process which was get in to sleep in get method: 
				// this->sleeper = (Activity *) scheduler.active();
				Activity *sleeper = this->sleeper;
				// reset the sleeper 
				this->sleeper = 0;
				// Prozesse die auf eine Eingabe warten muessen hier geweckt werden.
				sleeper->wakeup();
			}
		}
		/*
		if(((int)((rear+1) % size) == front) && (rear != -1)){
			//error OVERFLOW
		} else {
			//out.println("ich schreibe");
			rear = (rear+1)%size;	
			buffer[rear] = elem;
			Activity* waking = (Activity*) sleepers.dequeue();
			if (waking != 0) {
				waking->wakeup();
			}
			//out.println();
			//out.println("ich habe was geschrieben");
		}
		 */
	}

	/** Diese Methode wird von Prozessen aufgerufen, um Daten aus dem
	 *  Puffer zu lesen. Ist dieser leer wird der lesende Prozess schlafen
	 *  gelegt. Achtet hier besonders auf die Synchronisierung.
	 */
	T get()
	{
		/* 
		T temp;					//temporaere variable zur ausgabe
		if (rear == -1) { 			//buffer ist leer
			//out.println("erster fall");
			Activity* active = (Activity*) scheduler.getActiveProcessActivity();
			sleepers.enqueue(active);
			active->sleep();
				
		} else if (front == rear) {		//letztes element		
			temp = buffer[front];
			front = 0;
			rear = -1;
		} else {				//normaler fall
			temp = buffer[front];
			front = (front+1)%size;
			// rear = -1;
		}
		return temp;
		*/
		// get could be interrupted by another process 
		IntLock lock;
		// buffer is cleared if no element in buffer (sheep)
		if (this->sheeps == 0)
		{
			// Ist dieser leer wird der lesende Prozess schlafen gelegt.
			this->sleeper = (Activity *) scheduler.active();
			// naechstes element in ready liste wird aktiv
			scheduler.suspend();
		}
		// danach ist wieder ein element im buffer zu befuellen
		this->sheeps--;
		// take the elements out of the buffer so get the next index of buffer
		this->getPointer = (this->getPointer + 1) % size;
		if (this->getPointer != 0) {
			// other elements before last element
			return this->buffer[this->getPointer - 1];
		} else {
			// if the index is 0 the getPointer shows on first element in buffer but we want the last element
			// because 
			// return last element 
			// this is neccessary because % modulo size resets the last element to 0 
			int lastElement = size - 1; 
			return this->buffer[lastElement];
		}
	}

private:
	T buffer[size];
	unsigned addPointer;
	Activity *sleeper;
	int sheeps;
	unsigned getPointer;
};

#endif
