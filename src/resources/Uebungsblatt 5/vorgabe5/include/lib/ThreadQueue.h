//
// Created by Robert on 09.07.19.
//

#ifndef ThreadQueue_h
#define ThreadQueue_h

#include "system/Thread.h"

/** Diese Klasse stellt einen begrenzten synchronisierten
 *  Puffer dar, welcher von Interruptbehandlungsroutinen
 *  gef�llt werden kann.
 *
 *  Die Klasse ist eine Templateklasse. Das bedeutet f�r euch
 *  erstmal nur, das ihr alle Methoden hier im Header implementieren
 *  m�sst.
 */

class ThreadQueue {
public:

    ThreadQueue()
    {
        // 'first' zeigt auf das Element VOR das erste Element.
        // Dadurch kann in get first inkrementiert werden, ohne einen Wert zwischenzuspeichern.
        first = size-1;
        last = 0;


    }

    /** Diese Methode wird vom Interrupthandler aufgerufen, um
     *  ein etwas in den Puffer zu schreiben. Ist der Puffer voll,
     *  werden die zu schreibenden Daten verworfen.
     *  Prozesse die auf eine Eingabe warten m�ssen hier geweckt werden.
     */
    void add(Thread* elem)
    {

        if ((first-1) == last) {
            // Daten werden verworfen
        } else {
            buffer[last] = elem;
            last = (last + 1) % size;
        }

    }

    /** Diese Methode wird von Prozessen aufgerufen, um Daten aus dem
     *  Puffer zu lesen. Ist dieser leer wird der lesende Prozess schlafen
     *  gelegt. Achtet hier besonders auf die Synchronisierung.
     */
    Thread* get()
    {

        first = (first+1) % size;
        return buffer[first];

    }


private:

    Thread* buffer[10];
    unsigned int first;
    unsigned int last;
    unsigned int size = 10;


};

#endif
