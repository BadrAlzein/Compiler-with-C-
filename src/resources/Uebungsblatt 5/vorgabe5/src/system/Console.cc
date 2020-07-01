#include "system/Console.h"
#include "system/Semaphore.h"
#include "device/Keyboard.h"
#include "device/Key.h"

/*Console::Console(InputChannel& input, OutputChannel& output) {

    semaphore = Semaphore(1);

    inputChannel    = &input;
    outputChannel   = &output;

}*/

	/** 	Konsole reservieren
	 */
void Console::attach() {
    semaphore.wait();
}

	/** 	Konsole wieder freigeben
	 */
void Console::detach() {
    semaphore.signal();
}

	/** 	Daten auf der Console ausgeben
	 */
int Console::write(const char* data, int size) {

    return outputChannel->write((char*) data, size);

}

	/** 	Jedes von der Tastatur eingelesene Zeichen
	 * 	soll auf dem Bildschirm dargestellt werden (Echo Funktion!)
	 * 	Wenn ein '\n' erkannt wurde oder bereits "size" Zeichen
	 *	gelesen wurden, ist eine Zeile zuende und read() kehrt zurueck.
	 *	Alle gelesenen Ascii-zeichen sind in den Puffer einzutragen
	 *	und zaehlen als gueltiges Zeichen!
	 */
int Console::read(char* data, int size) {

    char* buchstabe = data;
    int i = 0;

    while (i < size) {

        inputChannel->read(data+i, 1);
        outputChannel->write(data+i, 1);

        i++;
        if (*buchstabe == 10) {
            break;
        }
        buchstabe++;
    }

    return i;
}

	/** 	Liefert das nächste Zeichen aus dem Eingabepuffer zurück.
	 */
char Console::read() {

    char data;
    int size = 1;

    inputChannel->read(&data, size);

	return data;
}
