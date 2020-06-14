#include "tools/Scanner.h"

/**
     * move the lesekopf one position to the right .
     * do nothing if the end of buffer is reached .
    (consume) the first character will be consumed and can not be pushed back
     */
void Scanner::consume()
{
    if (lookahead() != '\0')
        ++position;
}
/**
     * Bewegt den Lesekopf um eine Position nach rechts.
     * Hat keinen Effekt wenn das Ende des Puffers erreicht ist.
     */
void Scanner::consumeWS()
{
    char ch;
    while (lookahead(&ch) && isWhitespace(ch))
        consume();
}
//delievers the character on the actual position (can be a null byte \0).
char Scanner::lookahead()
{
    // length of string
    if (position >= length)
     return 0;

    return input[position];
}
/**
     * Speichert das Zeichen an der aktuellen Leseposition in 'dest'.
     * Prüft außerdem, ob das Ende des Puffers erreicht ist. Das ist
     * hilfreich, wenn das aktuelle Zeichen nur dann verarbeitet
     * werden soll, wenn es nicht das Null-Byte ist.
     *
     * @param dest
     *      Ziel zum Speichern des aktuellen Zeichens.
     * @return
     *      True wenn aktuelles Zeichen nicht das Null-Byte ist, sonst false.
     */
bool Scanner::lookahead(char *dest)
{
    if (dest == 0)
        return false;

    if (position >= length)
        return false;

    *dest = input[position];
    return (*dest != '\0');
}
/**
     * Prüft, ob das Zeichen eine Ziffer repräsentiert [0..9]
     *
     * @param ch
     *       Ein ASCII-Zeichen.
     * @return
     *       True wenn das Zeichen eine Ziffer repräsentiert, sonst false.
     */
bool Scanner::isDigit(char ch)
{
    // digits are from 48 - 57
    if (ch >= 48 && ch <= 57)
        return true;
    return false;
}
/**
 * check if char ch is a blank space  which is 32 in Ascii table
 * */
bool Scanner::isWhitespace(char ch)
{
    return ch == 32;
}

/**
     * check if char ch is a (- which is 45), (% which is 37) , (/ which is 47),(* which is 42),(+ which is 423   
     *
     * @param ch
     *       Ein ASCII-Zeichen.
     * @return
     *       True wenn es sich um ein Whitespace-Zeichen handelt, sonst false.
     */

bool Scanner::isOperand(char ch)
{
    if ((ch == 45) || (ch == 37) || (ch == 43) || (ch == 47) || (ch == 42))
        return true;
    return false;
}

/**
     * check if char ch is a Hex for adress info
     *
     * @param ch
     *       Ein ASCII-Zeichen.
     * @return
     *       True wenn es sich um ein Whitespace-Zeichen handelt, sonst false.
     */

bool Scanner::isHex(char ch)
{

    if ((((ch >= 97) && (ch <= 102)) || (ch == ' ') || (ch == 120)))
        return true;

    return false;
}

/**
     * check if char ch is not Hex
     * @param ch
     *       Ein ASCII-Zeichen.
     * @return
     *       True wenn es sich um ein Whitespace-Zeichen handelt, sonst false.
     */
bool Scanner::isNotHex(char ch)
{
    if ((ch >= 97) && (ch <= 122))
        return true;
        
    return false;
}
/**
     * check if char ch is a bracket  
     *
     * @param ch
     *       Ein ASCII-Zeichen.
     * @return
     *       True wenn es sich um ein Whitespace-Zeichen handelt, sonst false.
     */
bool Scanner::isBrackets(char ch)
{
    if ((ch == 41) || (ch == 40))
        return true;

    return false;
}
/**
     * (Re-)Initialisiert diesen Scanner.
     *
     * Diese Funktion muss aufgerufen werden, damit der Scanner
     * auf die gewünschte Eingabe zugreifen kann. Außerdem werden
     * alle Attribute wie der Lesekopf etc. zurückgesetzt.
     *
     * @param input
     *      Zeiger auf die zu lesende Zeichenkette.
     */
void Scanner::init(char *input)
{
    this->input = input;
    position = 0;
    length = 0;
    for (; *input != 0; ++input)
        ++length;
}
