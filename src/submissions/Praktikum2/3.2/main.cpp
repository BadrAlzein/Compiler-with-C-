#include <iostream>
#include "hello.h"

Hello* front;

void createHello() {
	
	// Push Anton to the stack
	Hello anton("Anton");
	// Point to Anton (top of stack)
	front = &anton;
	// Take Anton from the stack (call destructor)

}

int main() {
	createHello();
	front->body();
	// Put Berta where Anton used to be
	Hello berta("Berta");
	// führe das aus, wo Anton hinzeigte
	front->body();


	/*
	
	In den Kommentaren steht meine Theorie.	
	Aber wenn diese stimmt, warum kann nach createHello(); front-body(); aufgerufen werden?
	==> Wahrscheinlich ist das nicht der Grund.

	*/
};
