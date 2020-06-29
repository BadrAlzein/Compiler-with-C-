#include "system/Console.h"
#include "device/Keyboard.h"

/** 	Konsole reservieren
	 */
/**
     * Der Zugriff auf die Console darf erst erfolgen, nachdem diese reserviert (attach)
wurde. 
     */
void Console::attach()
{
    //sperren
    onOff.wait();
}

/** 	Konsole wieder freigeben
	 */
/**
     * Nach der Benutzung muß die Console wieder freigegeben werden (detach). Die innere
Synchronisation erfolgt dabei über eine Semaphore.
     */
void Console::detach()
{
    //wieder freigeben
    onOff.signal();
}

/** 	Daten auf der Console ausgeben
	 */
int Console::write(const char *data, int size)
{
    return output.write(data, size);
}

/** 	Jedes von der Tastatur eingelesene Zeichen
* 	soll auf dem Bildschirm dargestellt werden (Echo Funktion!)
* 	Wenn ein '\n' erkannt wurde oder bereits "size" Zeichen
*	gelesen wurden, ist eine Zeile zuende und read() kehrt zurueck.
*	Alle gelesenen Ascii-zeichen sind in den Puffer einzutragen
*	und zaehlen als gueltiges Zeichen!
*/
int Console::read(char *data, int size)
{
    // check the end of line an return \n
    char c = 0;
    // because size is also int
    int temp = 0; 
    while(size > temp) {
        if ((c == '\n')) {
            break;
        }
        // read the input char
        // Liefert das n�chste Zeichen aus dem Eingabepuffer zur�ck.
        c = this->read();
        // ausgabe auf der console
        output.write(c);

        // Alle gelesenen Ascii-zeichen sind in den Puffer einzutragen!
        data[temp] = c;
        // laenge der ausgegebenen zeichen
        temp++;
    }
    return temp;
}

/** 	Liefert das n�chste Zeichen aus dem Eingabepuffer zur�ck.
	 */
char Console::read()
{
    /*
        Diese Methode liefert ein Zeichen aus dem Tastaturpuffer
        zur�ck. Diese Methode blockiert, wenn der Puffer leer ist.
     */
    char bufferChar;
    // has size 1 for char
    char* location = &bufferChar;
    input.read(location, 1);
    return bufferChar;
}