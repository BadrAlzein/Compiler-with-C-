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
    //location = 0;
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

    Key button;
    char c;
    // as long as the pressed button is not the escape button, then we should read what the user pressed (where 27 is a representation of the escape button)
    while(button.getValue() != 27) {
        button = keyboard.read();
        c = button.getValue();
        // check if the pressed button is the left arrow (Where 75 is a representation of Left arrow CHECK Code Table)
        if(button.getValue() == 75) {
            this -> moveLeft();
        }
        // check if the pressed button is the right arrow (Where 77 is a representation of right arrow CHECK Code Table)
        if(button.getValue() == 77) {
            this -> moveRight();
        }
        if(button.isAscii()) {
            switch (c) {
                case '\n':              // check if the given ASCII code is representation of the the enter button
                    enter();
                    break;
                case 8:              //check for backspace
                    int column;
                    int row;

                    cga.getCursor(column,row);

                    // check if not at the first column otherwise we can't backspace and get out of cga screen.
                    // if we are not at 0 columns then we should delete the charachter before the cursor and replace it with and 
                    // empty string and move to the left along with cursor
                    if (column != 0) {
                        cga.setCursor(column - 1, row);
                        cga.getCursor(column, row);
                        location--;
                        buffer[location] = 0;
                        out.print(' ');
                        cga.getCursor(column, row);
                        cga.setCursor(column - 1, row);
                        cga.getCursor(column, row);
                    }
                    break;
                    
                    default:
                    insert(c);         //in case of a normal charachters then insert will handle it
                    break;
            }
        }
            
        }

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
    int column, row;
    cga.getCursor(column, row);

    int position = column;
        // if the expression has reached it's max length then there will be no insert anymore
        if(buffer[EXPR_SIZE_MAX - 1] != 0) {
            return;
        }
        //in case of writing a charachter that has other charachters on the right side of it, this they should be shifted
        if(buffer[position] !=0) {
            for(int i = EXPR_SIZE_MAX; i > position; i--) {
                buffer[i] = buffer[i-1];
            }

            buffer[position] = c;
            renderBuffer();
        } else {
            //adding a given charachter to the buffer
            buffer[position] = c;
            moveRight();
            renderBuffer();
        }



    //if(insertChar) {
        //check if the expression is at it's maximal legth then we can't add anything
        
    /* } else {
        //buffer[position] = c;
        //renderBuffer();
    } */
}

/**
 * this methode is a help function for inserting data into the buffer, when other data
 * are already given at the right side of the position, where everything right from the
 * written charachter will be shifted to the right
 * 
 */



/*void Calculator ::handleInsertAtLocation()
{
    //if (buffer[location] == 0)
    //{
    //}
    //else
    //{
        int j;
        // all elements that are written at the right of the position will be shifted
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
    //}
}*/

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
    // check if the interpreter is not equal to 0 then given expression is not defined in the grammar
    // and print the error message    
    if (interp.eval(buffer, result) != 0)
    {
        printErrorMsg(interp.eval(buffer, result));
    }
    // if it's equal to 0 that means that the given expression is correct then evaluate it and print it
    // to the screen.
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

    // check if the rows and colums are not equal to zero, so we can subtract one from the colums
    // which actually means moving the cursor on one position to the left
    if (row != 0 && column != 0)
    {
        cga.setCursor(column - 1, row);
        location--;
    }
    // check if the colum is not equal to zero and move one step to the left
    if (row == 0 && column != 0)
    {
        cga.setCursor(column - 1, row);
        location--;
    }
    //if we are at 0,0 then don't do anything because we can't get out of the cga screen
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

    // check if the cursor at (25,32) which means last row and 32 on colums (maximal expression length)
    // then move to (0,0)
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
