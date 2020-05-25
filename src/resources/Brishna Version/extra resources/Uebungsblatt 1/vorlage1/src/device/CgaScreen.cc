#include "../include/device/CgaScreen.h"

CgaScreen::CgaScreen() : attr(CgaAttr()), screen(), portIndex(IOPort8(0x3d4)), portData(IOPort8(0x3d5)) {
    initIntern();
    clear();
}

/**
 * Initializes some internal data.
 */
void CgaScreen::initIntern() {
    // videoRam Adress
    videoRam = (VideoRamCell *) 0xB8000;

    // Cursor
    indexCursorHigh = 14;
    indexCursorLow = 15;

    // GridLayout data
    rows = 25;
    columns = 80;
    videoCells = rows * columns;
    ramSize = videoCells * sizeof(VideoRamCell);

    // Initial attributes
    attr.setForeground(CgaAttr::LIGHT_GRAY);
    attr.setBackground(CgaAttr::BLACK);

};

/**
 * Calculates the index of a cell
 *
 * @param row
 * @param col
 * @return index of (row,col)
 */
int CgaScreen::ramIndex(int row, int col) {
    if ((row < 0) || (row >= rows) || (col < 0) || (col >= columns)) return -1; // Fehler
    return row * columns + col;
}

/**
 * Cleares screen and initializes some data
 *
 * @param _attr
 */
// Angegebene Attribute setzen und Bildschirm loeschen
CgaScreen::CgaScreen(CgaAttr _attr) : attr(CgaAttr()), screen(NULL), portIndex(IOPort8(0x3d4)),
                                      portData(IOPort8(0x3d5)) {
    initIntern();
    attr.setAttr(_attr);
    clear();
};

/**
 * Cleares the screen.
 * All cells will be set to the given attribute! (Standard: background: black, forefround: light_gray, no blink)
 */
// Loeschen des Bildschirms
void CgaScreen::clear() {
    int idx;             // index in den Video-RAM
    VideoRamCell cell;   // Inhalt einer Zelle aus Zeichen und Attribut

    attr.setForeground(CgaAttr::LIGHT_GRAY);
    attr.setBackground(CgaAttr::BLACK);
    attr.setBlinkState(false);
    setAttr(attr);

    cell.Character = 0;                                  // leeres Zeichen
    cell.Attribute = attr.getVideoAttribute() & 0x7F;  // aktuelle Attribute, aber ohne Blinken

    // go through every cell
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            idx = ramIndex(i, j);
            if (idx >= 0) {
                // Schreibe alles in den videoRam
                memcpy(videoRam + idx, (void *) &cell, sizeof(cell));
            }
        }
    }
    // Cursor auf (0,0) setzen
    setCursor(0, 0);
};

/**
 * Goes one line up. Cursor is set at the last line.
 * The last line will be empty (except, that the cursor stand in there).
 */
// Verschieben des Bildschirms um eine Zeile
void CgaScreen::scroll() {
    int firstIndex, lastIndex, idx;
    VideoRamCell cell;   // Inhalt einer Zelle aus Zeichen und Attribut

    // den Block ab der zweiten Zeile nach oben schieben
    firstIndex = ramIndex(1, 0);
    lastIndex = ramIndex(rows - 1, columns - 1);
    memcpy(videoRam + 0, ((VideoRamCell *) videoRam) + firstIndex, sizeof(cell) * (lastIndex - firstIndex + 1));

    // letzte Zeile mit aktuellen Attributen und Leerzeichen füllen
    cell.Character = 0; // leeres Zeichen

    CgaAttr stand_attr = CgaAttr();
    cell.Attribute = stand_attr.getVideoAttribute() & 0x7F;// aktuelle Attribute, aber ohne Blinken

    for (int j = 0; j < columns; j++) {
        idx = ramIndex(rows - 1, j);
        if (idx >= 0) {
            memcpy(videoRam + idx, (void *) &cell, sizeof(cell));
        }
    }

    // Cursor an den Anfang der letzen Zeile setzen
    setCursor(0, rows - 1);
};

// Setzen/Lesen der globalen Bildschirmattribute
void CgaScreen::setAttr(const CgaAttr &_attr) {
    attr.setAttr(_attr);
};

void CgaScreen::getAttr(CgaAttr &_attr) {
    _attr.setAttr(attr);
};

/**
 * Berechnet den Index, an dem der Cursor gerade steht.
 *
 * @return
 */
int CgaScreen::getCursorIndex() {
    BYTE cursorHigh, cursorLow;

    portIndex.write(14);
    cursorHigh = portData.read();
    portIndex.write(15);
    cursorLow = portData.read();

    // index im Video-RAM
    // Der 8 Shift nach links ist notwendig, damit man folgendes Muster erhält
    // CHigh:   XXXX XXXX 0000 0000
    // CLow :   0000 0000 XXXX XXXX
    // ==> CHigh + CLow = XXXX XXXX XXXX XXXX
    return (((int) cursorHigh) << 8) + (int) cursorLow;
}

/**
 * Wie zuvor erklärt, wird nun der index gesetzt.
 */
int CgaScreen::setCursorIndex(int idx) {
    BYTE cursorHigh, cursorLow;
    int index = idx;

    if ((index < 0) || (index >= rows * columns)) return 1; // Fehler

    cursorHigh = BYTE(index >> 8);
    cursorLow = BYTE(index & 0xFF);

    portIndex.write(15);
    portData.write(cursorLow);
    portIndex.write(14);
    portData.write(cursorHigh);

    return 0; // Kein Fehler
}

/**
 * Setzt/Bekommt unter Verwendung der vorigen Funktionen den Cursor
 */
// Setzen/Lesen des HW-Cursors
void CgaScreen::setCursor(int column, int row) {
    int index;

    index = ramIndex(row, column);
    setCursorIndex(index);
};

void CgaScreen::getCursor(int &column, int &row) {
    // index im Video-RAM
    int index = getCursorIndex();

    row = index / columns;
    column = index % columns;
};

/**
 * Beschreibt eine Zelle mit Attribut und Zeichen.
 */
// Anzeigen von c an aktueller Cursorposition
// Darstellung mit angegebenen Bildschirmattributen
void CgaScreen::show(char ch, const CgaAttr &_attr) {
    attr.setAttr(_attr);
    show(ch);
};

/**
 * Beschreibt eine Zeiler mit einem Zeichen unter Verwendung der in dieser Klasse
 * angegebenen Attribute.
 */
// Anzeigen von c an aktueller Cursorposition
// Darstellung mit aktuellen Bildschirmattributen
void CgaScreen::show(char ch) {
    int idx;             // index in den Video-RAM
    VideoRamCell cell;   // Inhalt einer Zelle aus Zeichen und Attribut

    // Zelle bereitstellen
    cell.Character = ch;
    cell.Attribute = attr.getVideoAttribute();

    // Berechnet die Position des Zeichens
    idx = getCursorIndex();
    // Beschreibt an die entsprechende Stelle
    memcpy(videoRam + idx, (void *) &cell, sizeof(cell));

    // Cursor eine Zelle weiter setzen
    idx++;
    // ggf. scrollen
    if (idx < rows * columns) {
        setCursorIndex(idx);
    } else {
        // hier muss gescrollt werden
        scroll();
    }
}