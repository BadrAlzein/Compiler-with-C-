#include "tools/Calc.h"

#include "device/CgaChannel.h" // ermöglicht Kontrolle über Cursor
#include "device/Keyboard.h"   // ermöglicht Eingaben durch Tastatur
#include "io/PrintStream.h"    // ermöglicht Linefeeds und Ausgabe von Zahlen

extern CgaChannel cga;
extern PrintStream out;

Calculator::Calculator()
{
    init();
}

Calculator::Calculator(void *sp) : Activity(sp)
{
    init();
    wakeup();
}

/**
     * Initialisiert den Calculator.
     *
     * Um in einen definierten Anfangszustand zu gelangen, sollte
     * (1) der Eingabepuffer initialisiert werden und (2) der
     * Bildschirm geleert werden.
     *
     * Sollte aufgerufen werden, bevor die eigentliche Ausführung
     * des Calculators beginnt.
     */
void Calculator::init()
{
    location = 0;
    clearBuffer();
    cga.clear();
}
/**
     * Das eigentliche Programm des Calculators.
     *
     * Bei dem Calculator handelt es sich im Prinzip um eine sogenannte
     * Read-Eval-Print-Loop (REPL). Ihr lest also wiederholt Zeichen
     * von der Tastatur ein, puffert diese und wertet die
     * resultierende Zeichenkette auf Bestätigung aus.
     *
     * Beim Einlesen und Puffern von Zeichen muss darauf geachtet werden,
     * dass nur ASCII-Zeichen gepuffert werden, während andere Zeichen
     * wie Zeilenumbrüche oder Pfeil-Tasten separat behandelt werden.
     * Bei Eingabe der Escape-Taste, soll das Programm beenden.
     *
     * Ist die Auswertung erfolgreich, wird das Ergebnis ausgegeben.
     * Andernfalls soll eine Fehlermeldung ausgegeben werden.
     * Die jeweilige Ausgabe erfolgt auf einer neuen Zeile.
     *
     * Die Eingabe eines weiteren Ausdrucks erfolgt stets
     * auf einer neuen Zeile. Ein Ausdruck darf dabei nie
     * länger sein als der zugrunde liegende Eingabepuffer.
     * Letzterer wiederum darf nicht mehr Zeichen als
     * eine Zeile auf dem CGA-Bildschirm haben (siehe
     * EXPR_SIZE_MAX).
     */
void Calculator::body()
{

    /** Die Klasse Key beschreibt ein logisches Zeichen,
      *  das heißt ein ASCII-Zeichen oder ein Steuerzeichen.
      */
    Key button;

    while (button.getValue() != 27) //solange END/ESC nicht gedrueckt wird
    {
        /**
         * Diese Methode liefert ein Zeichen aus dem Tastaturpuffer
         * zurück. Diese Methode blockiert, wenn der Puffer leer ist.
         */
        button = keyboard.read();

        if (button.getValue() == 75) //wenn Pfeiltaste links gedrueckt wird, dann wollen wir den Cursor nach links bewegen
        {
            /**
             * Das Betätigen der Pfeil-Links-Taste soll den Cursor 
             * genau eine Position nach links bewegen. Beachtet
             * hierbei etwaige Randfälle.
             */
            this->moveLeft();
        }

        if (button.getValue() == 77) //rechte Pfeiltaste
        {
            /**
             * Das Betätigen der Pfeil-Rechts-Taste soll den Cursor
             * genau eine Position nach rechts bewegen. Beachtet
             * hierbei etwaige Randfälle.
             */
            this->moveRight();
        }

        //Wenn ASCII-Zeichen, dann insert
        if (button.isAscii() == true)
        {
            insert(button.getValue());
            //count++;
            //buffer[count];
        }
    }
    out.println(" Taschenrechner gestoppt.");
}

/**
     * Behandelt die Eingabe eines ASCII-Zeichens.
     *
     * Falls möglich, wird das Zeichen an der aktuellen Position eingefügt.
     *
     * Hierzu müssen ggf. bereits eingegebene Zeichen verschoben werden
     * Überlegt euch, wie ihr verfahrt wenn, die maximale Ausdruckslänge
     * durch die Eingabe des neuen Zeichens überschritten wird.
     *
     * Beachtet außerdem, dass jedes gültige Zeichen gepuffert werden muss,
     * damit der Interpreter den insgesamten Ausdruck auswerten kann.
     *
     * @param c
     *      Ein ASCII-Zeichen
     */
void Calculator::insert(char c)
{
    //if (interp.isDigit(c))
    //{
    //}
    // 8 is backspace

    if (c == 8)
    {
        // Delete und moveLeft/moveRight muss trotzdem ausfuehrbar sein, auch wenn der Buffer voll ist!
        int row;
        int column;
        cga.getCursor(column, row);
        if (column != 0)
        {
            cga.setCursor(column - 1, row);
            cga.getCursor(column, row);
            location--;
            buffer[location] = 0;
            out.print(' ');
            cga.getCursor(column, row);
            cga.setCursor(column - 1, row);
            cga.getCursor(column, row);
        }
    }
    if (c == 10)
        {
            // ascii letter is 10 for new line
            enter();
        }
    if (location <= 32)
    {
        if (interp.isOperand(c))
        {
            handleInsertAtLocation();
            buffer[location] = c;
            out.print(c);
            location++;
        }
        else if (interp.isDigit(c))
        {
            handleInsertAtLocation();
            buffer[location] = c;
            location++;
            out.print(c);
        }
        else if (interp.isWhitespace(c))
        {
            handleInsertAtLocation();
            out.print(' ');
        }
        else if (interp.isHex(c))
        {
            handleInsertAtLocation();
            buffer[location] = c;
            location++;
            out.print(c);
        }
        else if (interp.isNotHex(c))
        {
            handleInsertAtLocation();
            buffer[location] = c;
            location++;
            out.print(c);
        }
    }
}

/**
 * Hilfsmethode, um das Einfuegen zu ermoeglichen, wenn noch
 * Zeichen rechts der Position stehen, indem die Zeichen rechts
 * der Position (von hinten an) nach Rechts verschoben werden,
 * sodass eine Luecke fuer das neue Element entsteht.
 */
void Calculator ::handleInsertAtLocation()
{
    if (buffer[location] == 0)
    {
        // zahl im buffer 0 hat keine wirkung
    }
    else
    {
        int j;
        // alle Elemente rechts von der Position, werden nach rechts fuer den insert verschoben -> Luecke fuer den Insert entsteht
        for (j = 32; j > location; j--)
        {
            buffer[j] = buffer[j - 1];
        }
        // 0 fuer eingabe eines zeichens an diese stelle
        buffer[location] = 0;
        int col;
        int row;
        cga.getCursor(col, row);
        out.print(' ');
        unsigned i = 0;
        // alle Zeichen nach dem Character an Stelle der Position werden nochmal geprinted, damit sie aktualisiert werden
        for (i = location + 1; i <= 32; i++)
        {
            out.print(buffer[i]);
        }
        cga.setCursor(col, row);
    }
}

/**
     * Behandelt das Betätigen der Eingabe-Taste.
     *
     * Das Betätigen der Eingabe-Taste soll zur Folge haben,
     * der aktuell gepufferte Ausdruck ausgewertet wird.
     *
     * Ist die Auswertung erfolgreich, soll das Ergebnis ausgegeben werden.
     * Andernfalls ist eine dem Rückgabe-Status angemessene Fehlermeldung
     * auszugeben. Dies erfolgt in der nächsten Zeile.
     *
     * Für die Eingabe des nächsten Ausdrucks sollte der Cursor
     * entsprechend
     */
void Calculator::enter()
{
    int result;
    out.println();

    /**
     * Wertet den gegebenen Ausdruck aus. Das Ergebnis wird in 'result' gespeichert.
     * Tritt während der Auswertung ein Fehler auf, wird ein von null verschiedener
     * Fehlercode zurückgegeben.
     * 
     * @return
     * Null, wenn die Auswertung erfolgreich war; sonst einen Fehlercode
     */
    //wenn interpreter eval != 0, dann falschen ausdruck eingebeben-> error ausprinten
    if (interp.eval(buffer, result) != 0)
    {
        printErrorMsg(interp.eval(buffer, result));
    }
    //sonst richtig, also Ergebnis printen
    if (interp.eval(buffer, result) == 0)
    {
        out.print(result);
    }
    clearBuffer();
    location = 0;
    //Ergebnis wurde ausgegeben also buffer für nächsten ausdruck vorbereiten
    //clearBuffer();
    out.println();
}

/**
     * Behandelt das Betätigen der Pfeil-Links-Taste.
     *
     * Das Betätigen der Pfeil-Links-Taste soll den Cursor
     * genau eine Position nach links bewegen. Beachtet
     * hierbei etwaige Randfälle.
     */
void Calculator::moveLeft()
{
    //Column, Row bekommen
    int column, row = 0;
    cga.getCursor(column, row);

    //wenn wir am Anfang einer Spalte sind, dann eine Zeile nach oben und zur letzte Spalte springen
    /*
    if (row != 0 && column == 0)
    {
        cga.setCursor(EXPR_SIZE_MAX, row - 1);
    }
     */
    //wenn keiner von beiden null, dann einfach eine Spalte zurück
    if (row != 0 && column != 0)
    {
        cga.setCursor(column - 1, row);
        location--;
    }

    if (row == 0 && column != 0)
    {
        cga.setCursor(column - 1, row);
        location--;
    }
    //nichts tun, sonst laufen wir auß dem cga-Bereich
    if (row == 0 && column == 0)
    {
        location = 0;
        cga.setCursor(0, 0);
    }
    if (row != 0 && column == 0)
    {
        location = 0;
        cga.setCursor(0, row);
    }
}

/**
     * Behandelt das Betätigen der Pfeil-Rechts-Taste.
     *
     * Das Betätigen der Pfeil-Rechts-Taste soll den Cursor
     * genau eine Position nach rechts bewegen. Beachtet
     * hierbei etwaige Randfälle.
     */
void Calculator::moveRight()
{
    int column, row = 0;
    cga.getCursor(column, row);

    //wenn am ende des Bildschirms, dann clearen und bei 0,0 starten
    //32, maximale Ausdruckslaenge
    if (row == 25 && column == 32)
    {
        cga.clear();
        cga.setCursor(0, 0);
        location++;
    }
    //wenn wir über die Spalten rechts rüber laufen
    if (row != 25 && column > 32)
    {
        //cga.setCursor(column, row);
    }
    if (row != 25 && column <= 32)
    {
        cga.setCursor(column + 1, row);
        location++;
    }
}

/** Schreibt den Eingabe-Puffer in den Grafikspeicher */
void Calculator::renderBuffer()
{
    // Cursor sichern
    int column, row;
    cga.getCursor(column, row);

    // Zeile schreiben
    cga.setCursor(0, row);
    cga.write(buffer, EXPR_SIZE_MAX);

    // Cursor wiederherstellen
    cga.setCursor(column, row);
}

/** Leert den Eingabepuffer */
void Calculator::clearBuffer()
{
    // Alle Zeichen nullen und Null-Byte hinter der höchsten Stelle setzen
    for (unsigned i = 0; i <= EXPR_SIZE_MAX; ++i)
        buffer[i] = 0;
}

void Calculator::printErrorMsg(unsigned code)
{
    switch (code)
    {
    case Interpreter::UNEXP_EOT:
        out.print("Error: Unexpected end of expression!");
        break;

    case Interpreter::UNEXP_SYMBOL:
        out.print("Error: Unexpected symbol!");
        break;

    case Interpreter::ARITHM_ERROR:
        out.print("Error: Arithmetic error!");
        break;

    case Interpreter::BAD_BUFFER:
        out.print("Error: Invalid buffer!");
        break;

    default:
        break;
    }
}
