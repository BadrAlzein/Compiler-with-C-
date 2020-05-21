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


class CgaChar {

public:

	// setzen des Zeichens
	void setChar(char c){
		this->zeichen =c;
	}
	
	// auslesen des Zeichens
	char getChar(){
		return zeichen;
	}
	
	// setzen der Darstellungsattribure
	void setAttr(const CgaAttr& attr){
		attribute.setAttr(attr);
	}
	
	// auslesen der Darstellungsattribute
	CgaAttr getAttr(){
		CgaAttr attribute;
	}

private:
char zeichen;
CgaAttr attribute;

};

#endif

