#ifndef PrintStream_h
#define PrintStream_h

#include "io/OutputChannel.h"

/*
 * PrintStream:	Diese Klasse ist aehnlich der Java-PrintStream Klasse
 *		Sie konvertiert u.A. numerische Werte in sichtbare Zeichen
 *		und gibt Sie auf dem im Konstruktor spezifizierten
 *		Ausgabekanal aus.
 *		Daraus ergeben sich 2 Teilaufgaben:
 *
 *		1. Die Feststellung der Ziffern einer Zahl
 *		2. Die Umwandlung der Ziffern in darstellbare Zeichen
 *
 *		Man beachte, dass diese Klasse unabhaengig
 *		von dem tatsaechlich verwendeten Ausgabekanal arbeitet.
 *
 *		Anmerkung: Diese Klasse werden wir spaeter noch in
 *		C++ konforme Ausgabe umwandeln.
 */

class PrintStream {

public:

    explicit PrintStream(OutputChannel *chan);

    explicit PrintStream(OutputChannel &chan);

    // Ausgabe eines mit einem NULL-Byte terminierten Strings
    void print(char *str);

    void print(char ch);

    void print(const char* str);

    // Ausgabe eines Strings mit anschliessendem Zeilenvorschub
    void println(char *str);

    void println(const char* str);

    // Zeilenvorschub
    void println();

    // numerische Werte werden zur Basis 'base' Ausgegeben
    // implementiere die Basen 2, 10 und 16
    void print(int x, int base = DECIMAL);

    void print(unsigned x, int base = DECIMAL);

    // Zeigertypen werden immer zur Basis 16 ausgegeben!
    void print(void *p);

    //void assignConstStr(char *buffer, const char *Source);

private:

    enum Base {
        BINARY = 2,
        DECIMAL = 10,
        HEX = 16
    };

    OutputChannel &channel;

};

#endif
