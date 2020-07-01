#include "device/CgaScreen.h"
#include "device/CgaChannel.h"
#include "io/OutputChannel.h"
#include "device/CgaAttr.h"

/**
 * Diese Klasse wird die Methoden in CgaChannel.h defniieren bzw. implementieren::
 * CgaChannel()
 * CgaChannel(const CgaAttr& attr)
 * write(const char* data, int size)
 * blueScreen(const char* error)
 */

// Ausgabekanal mit Standardattributen
// setter Methode
// set the standard Attribute to the Channel
CgaChannel::CgaChannel()
{
    this->setAttr(CgaAttr());
}

// Ausgabekanal mit spezifischen Attributen
// setter Methode
// set a specific Attribute to the channel
CgaChannel::CgaChannel(const CgaAttr& attr)
{
    this->setAttr(attr);
}

// Die von OutputChannel deklarierte Ausgaberoutine
// Write the given String (char * starting from the first given char (pointer)
// Given the size of the Bytes used
int CgaChannel::write(const char* data, int size)
{
    for (int i = 0; i < size; i++) {
		this->show(data[i]);
	}
	return size;
}

// Bluescreen mit standard Fehlermeldung
// activate the blue screen when an error occured
// set the fore ground to White and back Ground to blue and set every position of the window to
// an empty char
void CgaChannel::blueScreen(const char* error)
{
    this->attr.setForeground(this->attr.WHITE);
	this->attr.setBackground(this->attr.BLUE);
	this->attr.setBlinkState(false);
	
	for (unsigned int i = 0; i < (COLUMNS * ROWS); i++) {
	
		this->screen[i].setChar((char) ' ');
		this->screen[i].setAttr(this->attr);

	}
	setCursor(0, 0);
	// while *error is something else then zero
	while (*error) {
		show(*error, this->attr);
		// increment char length so 1 byte
		// *error++;
		(char*) error++;
	}



}
