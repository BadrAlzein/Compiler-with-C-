#ifndef CgaChannel_h
#define CgaChannel_h

#include "io/OutputChannel.h"
#include "device/CgaScreen.h"

#include <stdio.h>
#include <string.h>

/*
 * CgaChannel:	Diese Klasse implementiert einen Ausgabekanal
 *		fuer den CGA-Bildschirm
 *
 *		Sie *muss* die 'write' Methode implementieren,
 *		und alle write() Aufrufe geeignet auf den CgaScreen abbilden.
 *
 *      Man beachte:
 *		Unter den auszugebenden Zeichen befinden
 *		sich sogenannte Steuerzeichen, die geeignet
 *		zu interpretieren sind.
 *
 *		Es reicht fuer diese Uebung, wenn Ihr die
 *		Steuerzeichen '\n' (newline, NL) und '\r' (Carriage Return, CR)
 *		interpretiert.
 *		Bei CR ist der Cursor auf den Anfang der aktuellen Zeile
 *		zu setzen. Bei NL wird der Cursor auf den Anfang
 *		der naechsten Zeile gesetzt.
 */


#define ERROR_OK            0
#define ERROR_NULL_POINTER  1

#define ERROR_OTHER         100

class CgaChannel : public OutputChannel, public CgaScreen {
public:
    // Ausgabekanal mit Standardattributen
    CgaChannel();

    // Ausgabekanal mit spezifischen Attributen
    explicit CgaChannel(const CgaAttr &_attr);

    // Die von OutputChannel deklarierte Ausgaberoutine
    virtual int write(char *data, int size);

    virtual int write(char *data);

    // Bluescreen mit standard Fehlermeldung
    void blueScreen() {
        blueScreen(ERROR_OK, "ERROR");
    }

    // Bluescreen mit eigener Fehlermeldung
    virtual void blueScreen(const char *error);

    virtual void blueScreen(int ErrorCode, const char *error);
};

void int2CharU(unsigned int v, char *buffer, int maxLen);

void int2Char(int v, char *buffer, int maxLen);

void int2CharHex(int v, char *buffer, int maxLen);

void int2CharBase2(int v, char *buffer, int maxLen);

void strcat(char *c, char *s);

void assignConstStr(char *buffer, const char *source);


#endif
