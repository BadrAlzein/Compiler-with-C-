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
	this->setAttr(attribut);

	//pass the starting adress of the charachter to the video-RAM
	this->screen = (CgaChar *)OFFSET0;

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
	this->setAttr(attr);

	//pass the starting adress of the charachter to the video-RAM
	this->screen = (CgaChar *)OFFSET0;

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
		this->screen[i].setAttr(attr);
		//set the "zeichen" to blank
		this->screen[i].setChar(blank);
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

	//move every caracter one row upwords
	//copy loop
	for (int i = 0; i < newScreenSize; i++)
	{
		this->screen[i] = this->screen[i + COLUMNS];
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
			this->screen[i].setChar(blank);
		}
		else if (i % 2 != 0)
		{
			this->screen[i].setAttr(attr);
		}
	}
	  // Cursor an den Anfang der letzen Zeile setzen
    setCursor(0, 25 - 1);
}


/* Setzen des HW-Cursors
 * change the current cursor to a diffrent position
 * for the I/O use the IOPort8 because its already given in Screen.h
*/
void CgaScreen::setCursor(int column, int row)
{
	/*see Wiki https://www.lowlevel.eu/wiki/Color_Graphics_Adapter#Cursor_Address
	  Die Register 14 und 15 setzen die Cursor-Adresse, die sich aus der Cursor-Position berechnet.
	*/
	unsigned short cursor_address = column + row * COLUMNS; //row * COLUMNS -> now u stay at the start of the right line

//low bytes ************
	/*
	verbindung CgaScreen.h mit IOPort.h
	define the two variabels from CgaScreen.h (data & index)
	use this two to save registers info inside the Controller Register
	*/

	index = IOPort8(INDEX); //pass index of Index Register (nur schreiben) 
	//save the high bytes of the cursor
	index.write(CURSOR_LOW);
	data = IOPort8(DATA);	//pass the data of data Register (lesen & schreiben) 
	/*
	enter cursor_address (low bytes Register 15)
	0xff is in hex FF which is ...0000 11111111 so 
	“& 0xff” masks the variable so it leaves only the value in the last 8 bits,
	and ignores all the rest of the bits.
	*/
	data.write(cursor_address & 0xff);	

//HEIGH bytes************

	//enter the low bytes of the cursor
	index.write(CURSOR_HIGH);

	/*
	enter cursor_address (high bytesRegister 14)
	with an 8 bit shift to delete the current address 
		1. shift the cursor_address to the far right,da cursor_address (its the form HHHHHHHH LLLLLLLL)
		2. use  & 0xff to enter only the first 8 bits from cursor_address
	*/
	data.write((cursor_address >> 8) & 0xff);

}

// Lesen des HW-Cursors
/*
	umgekehrt wie set Cursor
*/
void CgaScreen::getCursor(int &column, int &row)
{
	unsigned short cursor_address; //the cursor_address of the given pos
	int low_cursorAddress = 0; //save the loweer bytes of the cursorAddress
	int hight_cursorAddress = 0; //save the higher bytes of the cursorAddress

//low bytes ************

	/*
	verbindung CgaScreen.h mit IOPort.h
	define the two variabels from CgaScreen.h (data & index)
	use this two to save registers info inside the Controller Register
	*/
	index = IOPort8(INDEX); //pass index of Index Register (nur schreiben) 
	//save the high bytes R 14
	index.write(CURSOR_LOW);
	data = IOPort8(DATA);	//pass the data of data Register (lesen & schreiben) 
	//enter the low bytes of the cursor
	low_cursorAddress = data.read();
	
//HEIGH bytes************

	index.write(CURSOR_HIGH);
	
	//return the low and high cursor adsress from data 	hight_cursorAddress= 0000000 HHHHHHH
	hight_cursorAddress = data.read();
	//make the hight_cursorAddress = HHHHHHH 0000000 for making place to the lower bytes
	hight_cursorAddress = hight_cursorAddress<<8; 
	//form the cursor_address (its the form HHHHHHHH LLLLLLLL)
	cursor_address = hight_cursorAddress | low_cursorAddress ;

	/*get position from the adress (revers the formel)
		1. a row is a 80 column so to find a row pos of a cursor simply div 80
		2. now use the row in the formel :: cursor_address = column + row * COLUMNS to find column
	*/
	row	= (int) (cursor_address /COLUMNS);
	column = cursor_address - (row * COLUMNS); //!!(pending)
}

// Anzeigen von c an aktueller Cursorposition
// Darstellung mit angegebenen Bildschirmattributen
void CgaScreen::show(char ch, const CgaAttr& attr)
{
	int column;
	int row;
	getCursor(column, row);
	char* cursorAddress = (char*) (2 * (column + row * COLUMNS));
	cursorAddress += OFFSET0;
	getCursor(column, row);
	if (ch == '\n') { 
		if (row < 24) {
			setCursor(0, row + 1);
			getCursor(column, row);
		}else if (row == 24)
		{
			this->scroll();
			setCursor(0, row);
		}
	} else if (ch == '\r') {
		setCursor(0, row);
		getCursor(column, row);
	}
	if ((short) ch > 31 && (short) ch < 127) {
		*cursorAddress = ch;
		cursorAddress += 1;
		this->setAttr(attr);
		*cursorAddress = this->attr.getAttr();
		if (column < 79) {
			setCursor(column + 1, row);
		} else {
			if (row < 24) {
				setCursor(0, row + 1);
			} else if (row == 24) {
				this->scroll();
				setCursor(0, 24);
			}
		}
	}
}
