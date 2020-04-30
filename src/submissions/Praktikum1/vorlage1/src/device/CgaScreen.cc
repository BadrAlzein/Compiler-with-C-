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
CgaScreen::CgaScreen(): index(INDEX), data(DATA)
{

//delete the screen
clear();
}



// Standardattribute waehlen und Bildschirm loeschen
CgaScreen::CgaScreen(): index(INDEX), data(DATA)
{



//delete the screen
clear();
}


// Loeschen des Bildschirms
void CgaScreen::clear()
{


}


// Verschieben des Bildschirms um eine Zeile
void CgaScreen::scroll()
{


}

// Setzen des HW-Cursors
void CgaScreen::setCursor(int column, int row)
{


}

// Lesen des HW-Cursors
void CgaScreen::getCursor(int& column, int& row)
{


}

// Anzeigen von c an aktueller Cursorposition
    	// Darstellung mit angegebenen Bildschirmattributen
void CgaScreen::show(char ch, const CgaAttr& attr)
{




}