#include "device/CgaScreen.h"
#include "device/CgaChannel.h"
#include "io/OutputChannel.h"
#include "device/CgaAttr.h"

// Ausgabekanal mit Standardattributen
CgaChannel::CgaChannel()
{
	// screen* = Video.OFFSET0;
	// CgaAttr attr;
	// setAttr(&attr);
	// clear(); clear does also set the cursor to (0,0)
	this->setAttr(CgaAttr());
}

// Ausgabekanal mit spezifischen Attributen
CgaChannel::CgaChannel(const CgaAttr &attr)
{
	this->setAttr(attr);
}

// Hinweis: der Rückgabewert spiegelt die Anzahl der ausgegebenen Zeichen wieder
// Die von OutputChannel deklarierte Ausgaberoutine
// size is the size of bytes of the word
// char* data takes the adress of an char
int CgaChannel::write(const char *data, int size)
{
	// Anzeigen von c an aktueller Cursorposition
	// Darstellung mit aktuellen Bildschirmattributen
	// void show(char ch)
	// TODO check if this is right
	for (int i = 0; i < size; i++)
	{
		// show call possible because CgaChannel inheriteds from CgaScreen
		this->show(data[i]);
	}
	return size;
}

// Bluescreen mit eigener Fehlermeldung
void CgaChannel::blueScreen(const char *error)
{
	this->attr.setForeground(this->attr.WHITE);
	this->attr.setBackground(this->attr.BLUE);
	this->attr.setBlinkState(false);
	// set all ascii chars to empty string
	// set the background of every row and column to black
	for (unsigned int i = 0; i < (COLUMNS * ROWS); i++)
	{
		// number i is even
		// set the ascii letter to empty char
		this->screen[i].setChar((char)' ');
		// number i is odd
		this->screen[i].setAttr(this->attr);
	}
	setCursor(0, 0);
	// while *error is something else then zero
	while (*error)
	{
		show(*error, this->attr);
		// increment char length so 1 byte
		// *error++;
		(char *)error++;
	}
}
