#include "device/CgaScreen.h"
#include "device/CgaAttr.h"
#include "io/IOPort.h"

/**
 * Diese Klasse wird die Methoden in CgaScreen.h defniieren bzw. implementieren::
 * CgaScreen()
 * explicit CgaScreen(CgaAttr attr);
 * void clear ();
 * void scroll();
 * setCursor();
 * getCursor();
 * void show(char ch, const CgaAttr& attr);
 */

// Standardattribute waehlen und Bildschirm loeschen
CgaScreen::CgaScreen() : index(INDEX), data(DATA)
{
	/* Standardattribute waehlen
this will create a default (standard) attribut and set the character attribut with it 
let the paramets on default ->  fg=WHITE bg=BLACK  blink=false
*/
	CgaAttr attribut = CgaAttr();
	setAttr(attribut);

	//pass the starting adress of the charachter to the video-RAM
	screen = (CgaChar *)OFFSET0;

	//Bildschirm loeschen
	clear();
}

// Angegebene Attribute setzen und Bildschirm loeschen
CgaScreen::CgaScreen(CgaAttr attr) : index(INDEX), data(DATA)
{
	/*
Angegebene Attribute setzen
just set the given attribut using setAttr() from Class CgaScreen
*/
	setAttr(attr);

	//pass the starting adress of the charachter to the video-RAM
	screen = (CgaChar *)OFFSET0;

	//delete the screen
	clear();
}

// Loeschen des Bildschirms
/* switch every possible character on the Screen to a blank 
	that means: 
	1. reset every Screen Charachter:
		1.1. zeichen to " "
		1.2. create a default attr to use it for clearing other attributs
	2. reset the cursor to the starting position x=0, y = 0 
*/
void CgaScreen::clear()
{
	char blank = ' ';  //switch all charachters with blank
	int cursorPos = 0; //the starting pos of the cursor

	//every Screen can have max. 80 X 25 character = 2000 Char
	int screenSize = COLUMNS * ROWS;
	//create a default attr to use it for clearing other attributs
	CgaAttr attr = CgaAttr();

	//start reseting from first char to the end
	for (int i = 0; i < screenSize; i++)
	{
		//set the attribut to default
		screen[i].setAttr(attr);
		//set the "zeichen" to blank
		screen[i].setChar(blank);
	}
	//reset the cursor to the starting position x=0, y = 0
	setCursor(cursorPos, cursorPos);
}



// Verschieben des Bildschirms um eine Zeile
// read Wiki -> cga 
void CgaScreen::scroll()
{
	/* To Scroll (Wiki): 
		Um den Bildschirm zu scrollen muss der gesamte Textspeicher 
		ab der 2. Zeile zur 1. Zeile kopiert werden und die letzte Zeile gelöscht werden.
	*/
	int RowBytes = COLUMNS * 2; //bytes cor charachters in one row (every character is 2 bytes)
	char blank = ' ';			//switch all charachters with blank

	// the bytes for every row wihtout the last one  (rows - 1)
	int newScreenSize = (RowBytes) * (ROWS - 1);

	//the screen size after deleting + the deleted row = full screen size
	int fullScreenSize = newScreenSize + RowBytes;

	//move every caracter one row downwords
	for (int i = 0; i < newScreenSize; i++)
	{
		screen[i] = screen[i + COLUMNS];
	}

	/* delete the last row from the screen 
		start deleting from Rows-1 until the final row:: (n-1)->(n) 
		the deleting process: 
			the screen startes with a charachter and follow up by attribut
			like 0 is char 1 is attr .. 
			-> gerade ist char 
			-> ungerade ist attr

		*/
	for (int i = newScreenSize; i < fullScreenSize; i++)
	{
		if (i % 2 == 0)
		{
			screen[i].setChar(blank);
		}
		else if (i % 2 != 0)
		{
			screen[i].setAttr(attr);
		}
	}
}


// Setzen des HW-Cursors
void CgaScreen::setCursor(int column, int row)
{
}

// Lesen des HW-Cursors
void CgaScreen::getCursor(int &column, int &row)
{
}

// Anzeigen von c an aktueller Cursorposition
// Darstellung mit angegebenen Bildschirmattributen
void CgaScreen::show(char ch, const CgaAttr &attr)
{
}
