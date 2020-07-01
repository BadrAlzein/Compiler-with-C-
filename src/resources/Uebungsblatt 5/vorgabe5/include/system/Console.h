#ifndef Console_h
#define Console_h

#include "io/InputChannel.h"
#include "io/OutputChannel.h"

#include "system/Semaphore.h"

/**
 *  Console:	Die Systemkonsole
 */
class Console: 	public InputChannel, public OutputChannel{
public:
	Console(InputChannel& input, OutputChannel& output): semaphore(Semaphore(1)), inputChannel(&input), outputChannel(&output) {}

	/** 	Konsole reservieren
	 */
	void attach();

	/** 	Konsole wieder freigeben
	 */
	void detach();

	/** 	Daten auf der Console ausgeben
	 */
	virtual int write(const char* data, int size);

	/** 	Jedes von der Tastatur eingelesene Zeichen
	 * 	soll auf dem Bildschirm dargestellt werden (Echo Funktion!)
	 * 	Wenn ein '\n' erkannt wurde oder bereits "size" Zeichen
	 *	gelesen wurden, ist eine Zeile zuende und read() kehrt zurueck.
	 *	Alle gelesenen Ascii-zeichen sind in den Puffer einzutragen
	 *	und zaehlen als gueltiges Zeichen!
	 */
	virtual int read(char* data, int size);

	/** 	Liefert das n�chste Zeichen aus dem Eingabepuffer zur�ck.
	 */
	char read();

	// --------------- Methoden aus OutputChannel -----------------

    /**
     * print bluescreen
     */
    virtual void blueScreen(const char* msg)
    {
        blueScreen(msg);
    }

    virtual int write(char *data, int size)
    {
        return outputChannel->write(data,size);
    }

    virtual int write(char *data)
    {
        return outputChannel->write(data);
    }

private:
    Semaphore   semaphore;

    // Channels
    InputChannel* inputChannel;
    OutputChannel* outputChannel;

};

#endif
