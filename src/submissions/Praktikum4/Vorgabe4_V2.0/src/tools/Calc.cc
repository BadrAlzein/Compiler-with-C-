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
    Key button;
    //see if the shift Left or Right is pressed
    if (button.getValue()==42 ||button.getValue()==54 ){
        shiftPressed=true;
    }
    // as long as the end or esc button are not pressed we should take input from the user
    // otherwise the programm should print a message that the calculator has been stopeed
    while (button.getValue() != 27) 
    {
    
        // this methode give back a charachter form the Keyboard buffer
        // this will be blocked when the buffer is empty
        button = keyboard.read();

        //check if the button pressed is the left arrow button, then we should be able to move to the left
        //where 75 is a representation of the left arrow (Check Codetable)
        if (button.getValue() == 75 &&shiftPressed) 
        {
            this->moveLeft();
            
        }

        //check if the button pressed is the right arrow button, then we should be able to move to the right
        //where 77 is a representation of the right arrow (Check Codetable)
         if (button.getValue() == 77 && shiftPressed) 
        {
            this->moveRight();
            
        }

        // check if the button from type ASCII then it will be handeld in the insert methode
         if (button.isAscii())
        {
            insert(button.getValue());
        
        }
    }
    out.println(" Calculator has stopped.");
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
     //check if the given charachter is a backspace then we should be able to delete a charachter at that position
     //and move the cursor one step backwards
    if (c == 8)  
    {
        
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
    //check if the given charachter is a new line charachter which means that the user pressed the enter button
    //that's why if the user had a valid expression it will be calculated
    else if (c == 10)
        {
            // ascii letter is 10 for new line
            enter();
        }
    else if (location <= EXPR_SIZE_MAX )   //Expr Size
    {
        
         if (interp.isWhitespace(c))
        {
            handleInsert();
            out.print(' ');
            
        }
     
        else {
            // here we will be able to add the rest of the charachters to the screen, where we add them to the buffer
            handleInsert();
            buffer[location] = c;
            location++;
            out.print(c);

        }
    }
}

/**
 * this methode will help us inserting new charachters when there are other charachters at the right side of our current
 * position, so they can shift to the write and give their place to other charachters
 * 
*/
void Calculator ::handleInsert()
{
    if (buffer[location] == 0)
    {
        // the number at the buffer 0 will have no effect
    } 
    else {
        // all elements that are the right side of our position will be shifted to the right
        for (int j = EXPR_SIZE_MAX; j > location; j--)
        {
            buffer[j] = buffer[j - 1];
        }
        // 0 fuer eingabe eines zeichens an diese stelle
        buffer[location] = 0;
        int col,row;
        cga.getCursor(col, row);
        out.print(' ');
        //unsigned i = 0;
    
        // all charachters after this position will be printed again
        for (unsigned i = location + 1; i <= EXPR_SIZE_MAX; i++)
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

    // check if the given expression is not valid then we should print the error message
    if (interp.eval(buffer, result) != 0)
    {
        printErrorMsg(interp.eval(buffer, result));
    }
    // if the expression is valid then it will be evaluated the result will be printed to the screen
    if (interp.eval(buffer, result) == 0)
    {
        out.print(result);
    }
    clearBuffer();
    location = 0;
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
    
    int column, row = 0;
    cga.getCursor(column, row);


    // check if both row and coulmn are not zero then we can move to the left along the y axis
    // where we just decrement the column, and move the cursor along with it
    if (row != 0 && column != 0)
    {
        cga.setCursor(column - 1, row);
        location--;
    }

    // do the same as above cause we are moving along the y axis for moving to the left
    if (row == 0 && column != 0)
    {
        cga.setCursor(column - 1, row);
        location--;
    }
    // when we are at 0,0 then we should'nt be able to move to the left
    // otherwise we will leave cga screen
    if (row == 0 && column == 0)
    {
        location = 0;
        cga.setCursor(0, 0);
    }
    // do the same as above and stay at the same place
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

    
    //when we at the end of the screen then we should be able to clear it and go back to the start
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
