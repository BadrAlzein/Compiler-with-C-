#ifndef CgaChar_h
#define CgaChar_h

#include "device/CgaAttr.h"

/*
 * CgaChar:
 * 
 *	Diese Klasse stellt den Prototyp eines
 *	Zeichens des Bildschirms dar.
 *	Dieses besteht aus darstellbarem Zeichen
 *	und Darstellungsattributen.
 */

// Aim: Class for set a char on an address in vram
class CgaChar {

public:

	// setzen des Zeichens
	void setChar(char c);
	
	// auslesen des Zeichens
	char getChar();
	
	// setzen der Darstellungsattribure
	void setAttr(const CgaAttr& attr);
	
	// auslesen der Darstellungsattribute
	CgaAttr getAttr();

private:
	char c;
	CgaAttr attr;
};

#endif
