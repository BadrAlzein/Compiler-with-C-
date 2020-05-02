#ifndef CgaChar_h
#define CgaChar_h

#include "device/CgaAttr.h"

/*
 * CgaChar:
 *	Diese Klasse stellt den Prototyp eines
 *	Zeichens des Bildschirms dar.
 *	Dieses besteht aus darstellbarem Zeichen
 *	und Darstellungsattributen.
 */



class CgaChar {

public:

	char c;
	// setzen des Zeichens
	void setChar(char c);
	
	// auslesen des Zeichens
	char getChar();
	
	// setzen der Darstellungsattribure
	void setAttr(const CgaAttr& attr);
	
	// auslesen der Darstellungsattribute
	CgaAttr getAttr();

private:
	/*
	jeder Zeichen in CGA Screens besteht aus Zeichen aus dem ascii Tabelle + 
	ein Attribut, der die For-und bg Color und blinker besteht (seheCgaAttr.h)
	insgesammt 2 Bit je Zeichen
	*/
	char charachter; //das Zeichen 
	CgaAttr attr;	//das Attribut 
};

#endif

