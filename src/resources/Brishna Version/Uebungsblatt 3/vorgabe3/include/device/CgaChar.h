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
    void setChar(unsigned char c) {
        this->letter = c;
    }

    // auslesen des Zeichens
    unsigned char getChar() {
        return letter;
    }

    // setzen der Darstellungsattribure
    void setAttr(const CgaAttr &attr) {
        attribut.setAttr(attr);
    }

    // auslesen der Darstellungsattribute
    CgaAttr getAttr() {
        return attribut;
    }

private:

    unsigned char letter;
    CgaAttr attribut;

};

#endif

