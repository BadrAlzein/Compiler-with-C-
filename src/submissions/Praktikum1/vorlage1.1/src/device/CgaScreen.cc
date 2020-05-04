#include "device/CgaScreen.h"
#include "device/CgaAttr.h"
#include "io/IOPort.h"

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

// TODO Problem we doesnt use the attributes use attr instead of 0
// Loeschen des Bildschirms
void CgaScreen::clear()
{
	// set all ascii chars to empty string
	// set the background of every row and column to black
	this->setAttr(CgaAttr());
	for (unsigned i = 0; i < (COLUMNS * ROWS); i++) {
		this->screen[i].setChar((char) ' ');
		this->screen[i].setAttr(this->attr);
	}
	// TODO put the cursor to the top left hand corner
	setCursor(0, 0);
}

// Verschieben des Bildschirms um eine Zeile
void CgaScreen::scroll()
{
	// dont know if scroll down or up
	// delete the first row
	// put every byte minus amount of ROWS
	// shift every char and attribute on screen about Screen.COLUMNS (80) * 2 = 160 bytes
	// ROWS - 1 because one complete column is deleted
	unsigned int beforeLastRow = COLUMNS * (ROWS - 1) * 2;
	for (unsigned int i = 0; i < beforeLastRow; i++) {
		this->screen[i] = this->screen[i + COLUMNS];
	}
	// delete the last row
	unsigned oneRow = COLUMNS * 2;
	for (unsigned int i = beforeLastRow; i < beforeLastRow + oneRow; i++) {
		if (i % 2 == 0)
		{
			this->screen[i].setChar((char) ' ');
		} else {
			this->screen[i].setAttr(this->attr);
		}
	}
}

// Setzen des HW-Cursors
/*
Um den Inhalt eines Steuerregisters vom Videocontroller abzufragen oder zu setzen,
muss zunaechst über das Indexregister der Index des gewünschten Steuerregisters ausgegeben werden.
Anschließend kann über das Datenregister auf das so adressierte Steuerregister zugegriffen werden.
*/
void CgaScreen::setCursor(int column, int row)
{
	// dont multiply by 2 because cursor works without 2 bytes (ascii + CgaAttr)
	unsigned int cursorAddress = column + row * COLUMNS;
	// cursorAddress += Video.OFFSET0;
	// via index register write the index of the control register
	index = IOPort8(INDEX);
	index.write(CURSOR_LOW);
	// now we can access control register over the data register
	data = IOPort8(DATA);
	// 0xff = 255 = 11111111
	// & bitwise AND shortcut
	// 1100000 AND 11111111 = 1100000
	// write low byte
	// & 0xff norms the binary to 1 byte so 8 bit
	// this is necessary for the 8 bit port (plausible / Jessis trivial)
	data.write(cursorAddress & 0xff);
	// write high cursor byte
	index.write(CURSOR_HIGH);
	// right shift to delete the current above 8 bits
	// reads the next 8 bits
	// 00010100 >> 2 = 00000101
	// write high byte
	// above bytes have to be set for cursor high
	// 16 bit cursor
	data.write((cursorAddress >> 8) & 0xff);
}

// Lesen des HW-Cursors
// the passed address will be filled with the cursor column and row
void CgaScreen::getCursor(int& column, int& row)
{
	index = IOPort8(INDEX);
	index.write(CURSOR_LOW);
	data = IOPort8(DATA);
	// 8 bits
	unsigned lowByte = data.read();
	index.write(CURSOR_HIGH);
	// 8 bits
	unsigned highByte = data.read();
	// calculate the column and row
	// left shift and or operation
	short cursorAdress = (highByte << 8) | lowByte;
	// column doesnt matter the rows it only counts the last row so modulo 80
	column = cursorAdress % COLUMNS;
	// row only accept full columns so 80 chars
	// and every half row would not accepted
	row = (int) (cursorAdress / COLUMNS);
}

// Anzeigen von c an aktueller Cursorposition
// Darstellung mit angegebenen Bildschirmattributen
// Implement \n Zeilenvorschub
void CgaScreen::show(char ch, const CgaAttr& attr)
{
	int column;
	int row;
	getCursor(column, row);
	char* cursorAddress = (char*) (2 * (column + row * COLUMNS));
	// take the right place in vram
	cursorAddress += OFFSET0;


	getCursor(column, row);
	if (ch == '\n') { 
		if (row < 25) {
			setCursor(0, row + 1);
			getCursor(column, row);
		}
	} else if (ch == '\r') {
		setCursor(0, row);
		getCursor(column, row);
	}
	// \n will never be reached here !!!!
	if ((short) ch > 31 && (short) ch < 127) {
		// first byte is the char ascii letter
		*cursorAddress = ch;
		// second byte -> one address
		cursorAddress += 1;
		// the pointer on the design attributes
		// TODO NOT SURE ABOUT THIS
		// void setAttr(const CgaAttr& attr)
		// void getAttr(CgaAttr& attr)
		this->setAttr(attr);
		*cursorAddress = this->attr.getAttr();

		if (column < 79) {
			setCursor(column + 1, row);
		} else {
			if (row < 25) {
				setCursor(0, row + 1);
			} else {
				scroll();
				setCursor(0, 25);
			}
		}
		// shifts the cursor by one
		// 79 because cursor starts with 0
	}
}
