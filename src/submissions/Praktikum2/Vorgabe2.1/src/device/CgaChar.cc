#include "device/CgaChar.h"
#include "device/CgaAttr.h"


/**
 * Diese Klasse wird die Methoden in CgaChar.h defniieren bzw. implementieren::
 * setChar(char c)
 * getChar()
 * setAttr(const CgaAttr& attr)
 * getAttr()
 */


// setzen des Zeichens
void CgaChar::setChar(char c)
{
    this->c = c;

}

// auslesen des Zeichens
char CgaChar::getChar()
{
	return c;
}

// setzen der Darstellungsattribure
void CgaChar::setAttr(const CgaAttr& attr)
{
	this->attr = attr;
}

// auslesen der Darstellungsattribute
CgaAttr CgaChar::getAttr()
{
return attr;
}
