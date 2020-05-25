#include "../include/device/CgaChannel.h"

#include <string.h>

// ------------------ Helper -----------------------------

/**
 * Reads the length of a string
 *
 * @param c String
 * @return Length of c
 */
int helper_strlen(char *c) {
    if (c == NULL) return 0;
    int len = 0;

    char *p;
    // p zeigt auf einen char
    p = c;
    // \0 ist das Ende eines Strings
    while (*p != '\0') {
        // Length inkrementieren
        len++;
        // Auf den nächsten Char zeigen
        p++;
    }
    return len;
}

/**
 * Appends s ON c.
 *
 * @param c First String (Output value)
 * @param s Appended Stirng
 */
void helper_strcat(char *c, char *s) {
    if (c == NULL) return;
    if (s == NULL) return;

    // ans Ende von c gehen
    char *p;
    p = c;
    while (*p != '\0') {
        p++;
    }

    // ans Ende von s, dabei anhängen
    char *t;
    t = s;
    while (*t != '\0') {
        *p = *t;
        p++;
        t++;
    }
}

/**
 * Reverts a string. (abc ==> cba)
 *
 * @param c String for Input and Output
 */
void helper_strrev(char *c) {
    int len = helper_strlen(c);
    int len2 = len / 2;
    char *p, *t, ch;

    // Anfang von c
    t = c;
    // Das Ende von c
    p = c + (len - 1);
    for (int i = 0; i < len2; i++) {
        // Zeichen austauschen
        ch = *t;
        *t = *p;
        *p = ch;
        // Zeiger an die nächste Stelle
        t++;
        p--;
    }
}

/**
 * Converts an integer to a char.
 *
 * @param v
 *                  Integer to be converted.
 * @param buffer
 *                  Returnlocation
 * @param maxLen
 *                  How long the char is at maximum.
 */
void int2Char(int v, char *buffer, int maxLen) {
    int dividend, divisor, remainder;
    int /*n,*/ i, sign;

    // Ist der return gegeben?
    if (!buffer) return;
    // Ist die Länge überhaupt größer 0 ?
    if (maxLen > 0) *buffer = '\0';

    // Grenze für int abfangen
    if ((unsigned int) v == 0x80000000) {
        if (maxLen < 12) return;
        strcpy(buffer, "-2147483648");
        return;
    }
    // Ist die Zahl vorhanden?
    if (!v) {
        if (maxLen > 1) {
            buffer[0] = '0';
            buffer[1] = '\0';
        };
        return;
    }

    // Vorzeichen herausfinden
    sign = v > 0 ? 1 : -1;
    if (v < 0) dividend = -v; else dividend = v;

    // Konvertiert die gegebene Zahl zur Basis 10
    divisor = 10;   // Basis 10
    i = 0;
    while ((dividend != 0) && (i < (maxLen - 1))) {
        remainder = dividend % divisor;
        dividend = dividend / divisor;
        buffer[i++] = (char) (48 + (remainder & 0xF));
        //n = i % 4;
    };
    if ((sign < 0) && (i < (maxLen - 1))) buffer[i++] = '-';
    buffer[i] = '\0';
    helper_strrev(buffer);
};

/**
 * The same as above, but with unsigned.
 *
 * @param v
 * @param buffer
 * @param maxLen
 */
void int2CharU(unsigned int v, char *buffer, int maxLen) {
    unsigned int dividend, divisor, remainder;
    unsigned int /*n,*/ i;

    if (!buffer) return;
    if (maxLen > 0) *buffer = '\0';

    if (!v) {
        if (maxLen > 1) {
            buffer[0] = '0';
            buffer[1] = '\0';
        };
        return;
    }

    divisor = 10;   // Basis 10
    i = 0;
    while ((dividend != 0) && (i < (unsigned int)(maxLen - 1))) {
        remainder = dividend % divisor;
        dividend = dividend / divisor;
        buffer[i++] = (char) (48 + (remainder & 0xF));
        //n = i % 4;
    };
    buffer[i] = '\0';
    helper_strrev(buffer);
};

/**
 * Converts a bite to Hex.
 *
 * @param bbyte
 *                  Byte to be converted
 * @param chi
 *                  High value of c
 * @param clo
 *                  Low value of c
 */
void byteToHex(unsigned char bbyte, char &chi, char &clo) {
    BYTE hi, lo;

    hi = (BYTE)((BYTE) bbyte >> 4) & 0xF;
    lo = (BYTE)((BYTE) bbyte & 0xF);
    chi = '0';
    if ((hi >= 0) && (hi <= 9)) {
        chi = (char) (hi + '0');
    } else {
        if ((hi >= 10) && (hi <= 15)) {
            chi = (char) (hi - 10 + 'A');
        }
    }
    clo = '0';
    if ((lo >= 0) && (lo <= 9)) {
        clo = (char) (lo + '0');
    } else {
        if ((lo >= 10) && (lo <= 15)) {
            clo = (char) (lo - 10 + 'A');
        }
    }
}

/**
 * Converts an integer to its Hexrepresentation as char.
 *
 * @param v
 *                  Integer to be converted.
 * @param buffer
 *                  Returnlocation
 * @param maxLen
 *                  Maximum length of the char.
 */
void int2CharHex(int v, char *buffer, int maxLen) {

    // Wir haben bereits eine Funktion, um Bytes zu Hex zu konvertieren.
    // Disese setzen wir hier ein.
    char chi[4], clo[4];
    BYTE bbyte[4];
    int idx = 0;

    // Wenn die Eingabe 0 ist, dass "00" zurückgeben
    if (v == 0) {
        strcpy(buffer, "00");
        return;
    }


    // Ein Integer ist 32 bit breit.
    // Durch Bitmasken, wird hier der Integer zu einem 4 Byte konvertiert.
    bbyte[0] = (v >> 0) & 0xFF;
    bbyte[1] = (v >> 8) & 0xFF;
    bbyte[2] = (v >> 16) & 0xFF;
    bbyte[3] = (v >> 24) & 0xFF;
    for (int i = 0; i < 4; i++)
        byteToHex(bbyte[i], chi[i], clo[i]);


    for (int i = 3; i >= 0; i--) {
        if (bbyte[i] != 0) {
            // Den Chars die Werte zuweisen
            // Dabei erhalten High & Low jeweile eine Hälfte des Inters
            *(buffer + idx++) = chi[i];
            *(buffer + idx++) = clo[i];
        }
    }
    // Finaler Wert
    *(buffer + idx) = '\0';
}

/**
 * Converts an Integer to a binary, represented by a char.
 *
 * @param v
 *                  Integer
 * @param buffer
 *                  Returnlocation
 * @param maxLen
 *                  Maximum length of the char
 */
void int2CharBase2(int v, char *buffer, int maxLen) {
    int idx, t;
    char ch;

    // Ist der Übergabewert 0 ?
    if (v == 0) {
        *(buffer + 0) = '0';
        *(buffer + 1) = '\0';
        return;
    }


    // Kopiert letztendlich nur die BIT Repräsentation des Integers.
    // Man sieht, dass man am Ende das ganze umgedreht erhält.
    t = v;
    for (int i = 0; i < 32; i++) {
        // Alles wegwerfen, außer das erste Bit.
        // Ergibt 1 oder 0 ?
        if ((t & 0x01) != 0) {
            ch = '1';
        } else {
            ch = '0';
        }

        *(buffer + idx++) = ch;
        t = t >> 1;
        if (t == 0) break;
    }
    *(buffer + idx) = '\0';

    helper_strrev(buffer);
}

/**
 * Was needed during developement.
 * Converts a const char to a simple char
 *
 * @param buffer
 *                  New Char
 * @param source

 *                  Const Char
 */
void assignConstStr(char *buffer, const char *source) {
    int idx = 0;
    char ch;

    *buffer = '\0';
    do {
        ch = *(source + idx);
        *(buffer + idx++) = ch;
    } while (ch != '\0');
}

// ------------------ Helper -----------------------------

CgaChannel::CgaChannel() {

};

// Ausgabekanal mit spezifischen Attributen
CgaChannel::CgaChannel(const CgaAttr &_attr) {
    attr.setAttr(_attr);
};

// Die von OutputChannel deklarierte Ausgaberoutine
int CgaChannel::write(char *data) {
    if (data == NULL) {
        // Bluescreen
        return 0;
    }
    int len;
    len = helper_strlen(data);
    return write(data, len);
}

// Die von OutputChannel deklarierte Ausgaberoutine
int CgaChannel::write(char *data, int size) {
    char ch;

    // Error?
    if (data == NULL) {
        blueScreen(ERROR_NULL_POINTER, "Error ");
    }

    // Ist nur jede Menge Formalia
    for (int i = 0; i < size; i++) {
        ch = *(data + i);
        if (ch == '\r') {
            int row, column;
            getCursor(column, row);
            setCursor(0, row);
        } else if (ch == '\n') {
            int row, column;
            getCursor(column, row);
            if (row == (rows - 1))
                scroll();
            else
                setCursor(0, row + 1);
        } else show(ch);
    }



    // Alles super gelaufen
    return 0;
};

// Bluescreen mit eigener Fehlermeldung
void CgaChannel::blueScreen(const char *error) {
    blueScreen(ERROR_OTHER, error);
}

// Bluescreen mit eigener Fehlermeldung
void CgaChannel::blueScreen(int errorCode, const char *error) {
    char s[32];
    char sMsg[512];
    char sError[512];

    s[0] = '\0';
    sMsg[0] = '\0';

    // sError <= error
    assignConstStr((char *) &sError, error);

    strcpy((char *) &sMsg, "Error ");
    if (errorCode != ERROR_OTHER) {
        int2Char(errorCode, (char *) &s, 32);
        helper_strcat((char *) &sMsg, (char *) &s);
    }

    //Idee von vorher:
    //char *buffer = NULL;
    //assignConstStr(buffer, ": ");
    //
    //helper_strcat((char *) &sMsg, buffer);

    helper_strcat((char *) &sMsg, (char *) ": ");
    helper_strcat((char *) &sMsg, (char *) &sError);
    // hier müsste man noch die Länge überwachen, aber die Meldungen kommen nur vom eigenen Programm und da achten wir selbst drauf


    CgaAttr blueAttr;
    blueAttr.setBackground(CgaAttr::BLUE);
    blueAttr.setForeground(CgaAttr::WHITE);
    blueAttr.setBlinkState(false);


    setAttr(blueAttr);

    //filling the screen with blue tiles
    int idx;             // Index in den Video-RAM
    VideoRamCell cell;   // Inhalt einer Zelle aus Zeichen und Attribut


    cell.Character = 0;                                  // leeres Zeichen
    cell.Attribute = attr.getVideoAttribute() & 0x7F;  // aktuelle Attribute, aber ohne Blinken

    // go through every cell
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if ((i < 0) || (i >= 25) || (j < 0) || (j >= 80)) { idx = -1; } else { idx = i * 80 + j; }; // Fehler
            if (idx >= 0) {
                // Schreibe alles in den videoRam
                memcpy(videoRam + idx, (void *) &cell, sizeof(cell));
            }
        }
    }
    // Cursor auf (0,0) setzen
    setCursor(0, 0);

    write((char *) &sMsg, helper_strlen((char *) &sMsg));
};