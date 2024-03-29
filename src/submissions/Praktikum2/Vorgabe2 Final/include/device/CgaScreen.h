#ifndef CgaScreen_h
#define CgaScreen_h

#include "device/CgaAttr.h"
#include "device/CgaChar.h"
#include "io/IOPort.h"

/*
 * CgaScreen:	Diese Klasse ist der Softwareprototyp fuer den
 *		CGA-Bildschirm
 *		
 *      Hier soll es ausschliesslich um die Kontrolle der Hardware
 *      gehen. Komplexere Aufgaben koennen in den erbenden Klassen
 *      implementiert werden.
 */


class CgaScreen {

private:

	// Die I/O-Ports des Grafikcontrollers
	enum Ports  {
		INDEX = 0x3d4, 
		DATA = 0x3d5
	};

	enum Cursor {
		CURSOR_HIGH = 14,
		CURSOR_LOW = 15
	};

	enum Video  {
		OFFSET0 = 0xb8000
	};

public:

	enum Screen {
		ROWS = 25,
		COLUMNS = 80
	};

	// Standardattribute waehlen und Bildschirm loeschen
	CgaScreen();

	// Angegebene Attribute setzen und Bildschirm loeschen
	explicit CgaScreen(CgaAttr attr);

	// Loeschen des Bildschirms
	void clear();

	// Verschieben des Bildschirms um eine Zeile
	void scroll();

	// Setzen der globalen Bildschirmattribute
	// pass a reference
	void setAttr(const CgaAttr& attr)
	{
		this->attr = attr;
	}

	// Lesen der globalen Bildschirmattribute
	void getAttr(CgaAttr& attr)
	{
		attr = this->attr;
	}

	// Setzen des HW-Cursors
	void setCursor(int column, int row);
	// Lesen des HW-Cursors
	void getCursor(int& column, int& row);


	// Anzeigen von c an aktueller Cursorposition
    	// Darstellung mit angegebenen Bildschirmattributen
	void show(char ch, const CgaAttr& attr);

	// Anzeigen von c an aktueller Cursorposition
    	// Darstellung mit aktuellen Bildschirmattributen
	void show(char ch)
	{
		// this-> is also reference so address of attr so CgaAttr&
		show(ch, this->attr);
	}


protected:
	CgaAttr attr;
	IOPort8 index;
	IOPort8 data; 
	CgaChar* screen;
};

#endif
