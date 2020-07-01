#include "tools/Calc.h"

#include "device/CgaChannel.h" // ermöglicht Kontrolle über Cursor
#include "device/Keyboard.h" // ermöglicht Eingaben durch Tastatur
#include "io/PrintStream.h" // ermöglicht Linefeeds und Ausgabe von Zahlen
#include "device/CodeTable.h"

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

    char c = 0;

    do {

        c = (keyboard.read()).getValue();

        if (CodeTable::isControl(c)) {

            //Fallunterscheidung für Kontrolltasten
            switch (c) {
                case 54: case 55 : case 56: case 42:
                    insert(c);
                    break;
                case (CodeTable::ENTER) :
                    enter();
                    break;

                case (CodeTable::LEFT) :
                    moveLeft();
                    break;

                case (CodeTable::RIGHT) :
                    moveRight();
                    break;

                case (CodeTable::INS) :
                    insPressed = not insPressed;
                    break;
                case (CodeTable::DEL) :
                    int column, row;
                    cga.getCursor(column, row);
                    for (int i = column; i<32;i++){
                       if(buffer[i+1]!= 0){
                        buffer[i] = buffer[i+1];
                        }else{
                        buffer[i]=0;
                        break;
                        }
                    }
                    renderBuffer();
                    break;
                case (CodeTable::BS) :
                     cga.getCursor(column, row);
                     if(buffer[column] != 0){
                        for (int i = column; i<32;i++){
                            if(buffer[i+1]!= 0){
                                buffer[i] = buffer[i+1];
                            }else{
                                buffer[i]=0;
                                break;
                            }
                        }
                    }else{
                        buffer[column-1] = 0;
                    }
                    renderBuffer();
                    cga.setCursor(column-1,row);
                    break;
                    


            }

        } else {

            insert(c);

        }



    } while (c != CodeTable::ESC); // esc


    out.println();
    out.println();
    out.print("EXIT");

}

void Calculator::insert(char c)
{
    int column, row;
    cga.getCursor(column, row);
    if(column < 32){
        // Buffer in den Grafikspeicher..
        if(insPressed){
            out.print(c);

        }else { //falls das nicht der letzte ist und  ins nicht pressed ist dann reststring soll um 1 nach rechts verschoben sein//falls aber ins pushed true ist dann muss neue character einfach die alten uberschieben.
            out.print(c);
            if(buffer[column +1] != 0){
                for(int i=31; i>column; i--){
                    buffer[i] = buffer[i-1];
                }
            }
        }
        // In den Buffer schreiben
        buffer[column] = c;

    }
    
    renderBuffer();


}

void Calculator::enter()
{

    out.print("\n");
    int result;
    if(!interp.eval(&buffer[0],result)){
        out.print("= ");
        out.print(result);

    } else {
        printErrorMsg(interp.eval(&buffer[0],result));
    }
    out.print("\n");
    clearBuffer();
}

void Calculator::moveLeft()
{
    int column, row;
    cga.getCursor(column, row);
    column--;

    cga.setCursor(column, row);
}

void Calculator::moveRight()
{
    int column, row;
    cga.getCursor(column, row);

    if (buffer[column] != 0) {
        column++;
        cga.setCursor(column, row);
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
    for (unsigned i=0; i<=EXPR_SIZE_MAX; ++i){   
        buffer[i] = 0;
    }
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

char Calculator::firstChar() {

    unsigned counter = 0;

    while (counter < sizeof(buffer) && buffer[counter] == 32) {
        counter++;
    }

    return buffer[counter];

}
