#ifndef CgaScreen_h
#define CgaScreen_h

#include <stdio.h>
#include <string.h>
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

protected:
    CgaAttr attr;
    CgaChar *screen;

    VideoRamCell *videoRam;

    // Cursor control
    BYTE indexCursorHigh, indexCursorLow;
    IOPort8 portIndex;   // Port des Indexregisters
    IOPort8 portData;    // Port des Datenregisters

    int rows, columns, ramSize, videoCells;

private:
    void initIntern();

    int ramIndex(int row, int col);

    int getCursorIndex();

    int setCursorIndex(int Idx);

public:

    // Standardattribute waehlen und Bildschirm loeschen
    CgaScreen();

    // Angegebene Attribute setzen und Bildschirm loeschen
    explicit CgaScreen(CgaAttr _attr);

    // Loeschen des Bildschirms
    void clear();

    // Verschieben des Bildschirms um eine Zeile
    void scroll();

    // Setzen/Lesen der globalen Bildschirmattribute
    void setAttr(const CgaAttr &_attr);

    void getAttr(CgaAttr &_attr);

    // Setzen/Lesen des HW-Cursors
    void setCursor(int column, int row);

    void getCursor(int &column, int &row);


    // Anzeigen von c an aktueller Cursorposition
    // Darstellung mit angegebenen Bildschirmattributen
    void show(char ch, const CgaAttr &attr);

    // Anzeigen von c an aktueller Cursorposition
    // Darstellung mit aktuellen Bildschirmattributen
    void show(char ch);

};

#endif
