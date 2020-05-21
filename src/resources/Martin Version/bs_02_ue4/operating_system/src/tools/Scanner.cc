#include "tools/Scanner.h"

void Scanner::consume()
{
    if (lookahead() != '\0')
        ++position;
}

void Scanner::consumeWS()
{
    char ch;
    while (lookahead(&ch) && isWhitespace(ch))
        consume();
}

char Scanner::lookahead()
{
    if (position >= length)
        return 0;

    return input[position];
}

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
 * Ueberprueft, ob char c eine Ziffer ist (48,...,57)
 * 
 * @param ch Char, der ueberprueft werden soll
 */
bool Scanner::isDigit(char ch)
{
    //Ziffern sind von 48 - 57
    return ch >= 48 && ch <= 57;
}

/**
 * Ueberprueft, ob char c ein blankspace ist
 * 
 * @param ch Char, der ueberprueft werden soll
 */
bool Scanner::isWhitespace(char ch)
{
    //blank ist 32
    return ch == 32;
}

/**
 * Prueft, ob Char ch ein "-" (ch == 45),
 * "%" (ch == 37), "+" (char == 43), "/" (char == 47) 
 * oder ein "*" (char == 42) ist
 */
bool Scanner::isOperant(char ch)
{
    if ((ch == 45) || (ch == 37) || (ch == 43) || (ch == 47) || (ch == 42))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Prueft, ob Char nicht Hex ist 
 * (Bugfix, sonst koennen keine Buchstaben ausgegeben werden, die nicht Hexadezimal sind)
 */
bool Scanner ::isNotHex(char ch)
{
    if ((ch >= 97) && (ch <= 122))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Prueft, ob Char Hex fuer Adressen-Angaben
 */
bool Scanner ::isHex(char ch)
{
    if ((((ch >= 97) && (ch <= 102)) || (ch == ' ') || (ch == 120)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Prueft, ob Char Klammer zu oder Klammer auf ist (fuer Klammerausdruecke)
 */
bool Scanner ::isBrackets(char ch)
{
    if ((ch == 41) || (ch == 40))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Scanner::init(char *input)
{
    this->input = input;
    position = 0;
    length = 0;
    for (; *input != 0; ++input)
        ++length;
}
