#include "interrupts/IntLock.h"
#include "thread/ActivityScheduler.h"
#include "thread/Activity.h"

#ifndef BoundedBuffer_h
#define BoundedBuffer_h


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

    BoundedBuffer()
    {
        // 'first' zeigt auf das Element VOR das erste Element.
        // Dadurch kann in get first inkrementiert werden, ohne einen Wert zwischenzuspeichern.
        first = size-1;
        last = 0;

        // Beschreibt, wie viele Tasten gerade im Puffer auf
        // Abholung warten
        elementsInQueue = 0;

        //for (int i = 0; i < 10; i++) buffer[i] = (T) 42;

    }

    /** Diese Methode wird vom Interrupthandler aufgerufen, um
     *  ein etwas in den Puffer zu schreiben. Ist der Puffer voll,
     *  werden die zu schreibenden Daten verworfen.
     *  Prozesse die auf eine Eingabe warten m�ssen hier geweckt werden.
     */
    void add(T& elem)
    {

        if ((first-1) == last) {
             // Daten werden verworfen
        } else {
            elementsInQueue++;
            buffer[last] = elem;
            last = (last + 1) % size;

            Activity* temp = caller;
            caller = 0;
            if (temp) temp->wakeup();
            //if (queue.getHead()) {
                // ((Activity*) queue.dequeue())->wakeup();
            //}
        }

    }

    /** Diese Methode wird von Prozessen aufgerufen, um Daten aus dem
     *  Puffer zu lesen. Ist dieser leer wird der lesende Prozess schlafen
     *  gelegt. Achtet hier besonders auf die Synchronisierung.
     */
    T get()
    {

        if (elementsInQueue == 0) {
            caller = scheduler.activeElement;
            caller->sleep();
            /*
            Activity* temp = scheduler.activeElement;
            queue.enqueue(temp);
            temp->sleep();*/
        }

        if (elementsInQueue > 0) {

            first = (first + 1) % size;
            elementsInQueue--;
            return buffer[first];

        }
    }


private:

    T buffer[size];
    int indexEnd; // Länge des Puffers

    int first;
    int last;

    unsigned int elementsInQueue;
    //bool callerExists;

    bool callerSet;
    Activity* caller;

    Queue queue;

};

#endif
