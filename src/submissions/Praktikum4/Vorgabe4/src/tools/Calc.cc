#include "tools/Calc.h"

#include "device/CgaChannel.h" // ermöglicht Kontrolle über Cursor
#include "device/Keyboard.h" // ermöglicht Eingaben durch Tastatur
#include "io/PrintStream.h" // ermöglicht Linefeeds und Ausgabe von Zahlen

extern CgaChannel cga;
extern PrintStream out;

Calculator::Calculator()
{
    init();
}

Calculator::Calculator(void* sp)
    : Activity(sp)
{
    init();
    wakeup();
}

void Calculator::init()
{
    clearBuffer();
    cga.clear();
}

void Calculator::body()
{
    Key button;

    while (button.getValue() != 27) { // sichere dass der Knopf nicht END/ESC
        button = keyboard.read();

        if (button.getValue() == 75) { // wenn die linke Pfeiltaste gedrückt wid
            this -> moveLeft();
        }

        if (button.getValue() == 77) { // wenn die rechte pfeiltaste gedrückt wird
            this -> moveRight();
        }

        if (button.isAscii()) { // Wenn der Knopf vom Typ ASCII dann insert
            insert(button.getValue());
        }
    }

    out.println("Taschenrechner bendet");


}

void Calculator::insert(char c)
{
    if (c == 8) { //Backspace(lösche und bewege sich nach links)
        int row;
        int column;
        cga.getCursor(column, row);
        if (column != 0) {
            cga.setCursor(column -1, row);
            cga.getCursor(column, row);
            location--;
            buffer[location] = 0;
            out.print(' ');
            cga.getCursor(column, row);
            cga.setCursor(column -1, row);
            cga.getCursor(column, row);
        }

        if (c == 10) { // ASCII Zeichen für eine neue Zeile
            enter();
        }

        if (location <= 32) {
            if(interp.isOperand(c)) {
                buffer[location] = c;
                out.print(c);
                location++;
            }
        }
        else if (interp.isDigit(c)) {
            buffer[location] = c;
            location++;
            out.print(c);
        }
        else if (interp.isNotHex(c)) {
            buffer[location] = c;
            location++;
            out.print(c);
        }
         else if (interp.isHex(c)) {
             buffer[location] = c;
             location++;
             out.print(c);
         }
        else if (interp.isWhitespace(c)) {
            out.print(' ');
        }
    }

}

void Calculator::enter()
{
    int result;
    out.println();

    if(interp.eval(buffer, result) != 0) {
        printErrorMsg(interp.eval(buffer, result));
    }

    if(interp.eval(buffer, result) == 0) {
        out.print(result);
    }
    clearBuffer();
    location = 0;
    out.println();
}

void Calculator::moveLeft()
{
    int column = 0;
    int row = 0;
    cga.getCursor(column, row);

    if (row != 0 && column !=0) {
        cga.setCursor(column -1, row);
        location--;
    }

    if (row == 0 && column != 0) {
        cga.setCursor(column - 1, row);
        location--;
    }

    if (row == 0 && column == 0) {
        location = 0;
        cga.setCursor(0,0);
    }

    if (row !=0 && column == 0) {
        location = 0;
        cga.setCursor(0, row);
    }


}

void Calculator::moveRight()
{
    int column = 0;
    int row = 0;
    cga.getCursor(column, row);

    if(row == 25 && column == 32) {
        cga.clear();
        cga.setCursor(0,0);
        location++;
    }

    if (row != 25 && column > 32) {

    }
    if (row != 25 && column <= 32) {
        cga.setCursor(column + 1, row);
        location++;
    }

}

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

void Calculator::clearBuffer()
{
    // Alle Zeichen nullen und Null-Byte hinter der höchsten Stelle setzen
    for (unsigned i=0; i<=EXPR_SIZE_MAX; ++i)
        buffer[i] = 0;
}

void Calculator::printErrorMsg(unsigned code)
{
    switch (code) {
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
