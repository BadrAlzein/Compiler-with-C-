#include "device/CgaChar.h"
#include "device/CgaAttr.h"

// setzen des Zeichens
void CgaChar::setChar(char c)
{
	this->c = c;
}

// auslesen des Zeichens
char CgaChar::getChar()
{
	return this->c;
}

// setzen der Darstellungsattribure
void CgaChar::setAttr(const CgaAttr& attr)
{
	this->attr = attr;
}

// auslesen der Darstellungsattribute
CgaAttr CgaChar::getAttr()
{
	return this->attr;
}
