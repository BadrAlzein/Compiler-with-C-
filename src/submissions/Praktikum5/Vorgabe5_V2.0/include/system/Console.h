#ifndef Console_h
#define Console_h

#include "io/InputChannel.h"
#include "io/OutputChannel.h"
#include "system/Semaphore.h"

/**
 *  Console:	Die Systemkonsole
 * the implentation of Console to avoid the running processes being interrupted so that nothing
 * can be manupliated from another process(Example in the assignment with anton's password)
 * the Console can be accessed only if it's attached and then after that
 * it should be detached
 */
class Console: 	public InputChannel, public OutputChannel{
public:
	Console(InputChannel& input, OutputChannel& output)
	: input (input), output(output), onOff(Semaphore(1)){
		
	}

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

    /**
     * print bluescreen
     */
    virtual void blueScreen(const char* msg)
    {
        output.blueScreen(msg);
    }
private:
	InputChannel &input;
	OutputChannel &output;
	Semaphore onOff;
};

#endif
