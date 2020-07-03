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
		// TODO Ask if Port is really 3d4 or hexadecimal 0x3d4
		// decimal => 980
		INDEX_REGISTER = 0x3d4, 
		// decimal => 981
		DATA_REGISTER = 0x3d5
	};

	// Die Kommandos zum Cursor setzen
	enum Cursor {
		// cursor index not sure if costubs meant hexadecimal => 0x14 = 20
		// sets the cursor one above (high byte)
		CURSOR_HIGH = 14,
		// sets the cursor one below (low byte)
		CURSOR_LOW = 15
	};

	// Die Adresse des Video RAMs
	enum Video  {
		OFFSET0 = 0xb8000
	};

public:
	// Die Bildschirmdimensionen
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
	// hopefully we call the constructor of CgaAttr here (suppose)
	CgaAttr attr;
	IOPort8 index;
	IOPort8 data;
	// start adresse vom video ram  im konstruktor setzen 
	CgaChar* screen;
};

#endif
