#ifndef Queue_h
#define Queue_h

#include "lib/Chain.h"

class Queue {
public:
	Queue () { head = 0; tail = &head; }

	// Einfuegen eines Elementes an das Ende der Liste
	void enqueue(Chain* item);

	// Entfernen des Listenkopfes
	Chain* dequeue();

	// Entfernen des angegebenen Elementes
	void remove(Chain* item);

	Chain* getHead() {
	    return head;
	}

	Chain** getTail() {
	    return tail;
	}

	Chain* getItem(int posi)
    {
        Chain* curr = head;
        if(posi > 0) {
            int i = 1; // jaja ok man faengt bei der null an aber trotzdem ist es das item nummer 1 und nicht null, weil head ist null
            while(curr && (i <= posi)) {
                curr = curr -> next;
                i++;
            }
        }
        return (curr);
    }

private:
	Chain* head;	// der Listenkopf
	Chain** tail;	// Zeiger auf den Zeiger auf das Listenende
};

#endif
