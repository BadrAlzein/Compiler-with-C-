#ifndef Hello_h
#define Hello_h

#include "system/Thread.h"
#include "system/Console.h"
/*
Bisher konnten ’Benutzer-Programme’ (wie Hello) Datenstrukturen des Kerns (etwa die Rea-
dyList) manipulieren. Nun sollen Benutzer- und System-Teil voneinander getrennt werden. Als
Schnittstelle dient die Klasse Thread, von der sich alle Anwendungsprogramme ableiten. Da
Thread privat von Activity erbt, haben abgeleitete Klassen nicht mehr direkt Zugriff auf Ba-
sisklassen im Kern. Thread ist für das Betreten und Verlassen des Kerns verantwortlich. Zur
leichteren Handhabung gibt es analog zur Klasse IntLock eine Klasse KernelLock.
 */
class Hello: public Thread {
public:
	enum { LINE_SIZE = 512 };

	/** Konstruktor mit den bekannten Argumenten..
	 */
	Hello(const char* name, int runs, int slice, void* sp);

	/* Im Destruktor muss auf die Beendigung von "body()"
	 * gewartet werden!
	 */
	~Hello();

	virtual void run();

private:

	int runs;		// Anzahl der Durchlaeufe
	const char* name; 	// Name dieses Threads

	char line[LINE_SIZE];  	// Zeilenpuffer
};

#endif
