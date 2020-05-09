#include "user/Hello.h"

#include "user/Environment.h"
/*
Bei vorherigen Aufgaben habt ihr vielleicht schon bemerkt, dass es ungünstig ist, während der
Bildschirmausgabe unterbrochen zu werden. Wenn der nächste Prozess auch Daten ausgibt, ist
das Ergebnis kaum lesbar.
Die Vorgabe enthält Beispiel-Anwendungen (Hello-Threads). Diese geben Informationen auf
dem Bildschirm aus und erwarten danach Eingaben des Benutzers. Dazwischen darf kein anderer
Prozess Ein-/Ausgabeoperationen machen. Stellt euch zur Veranschaulichung vor, dass Anton
nach einem Passwort fragt. Direkt nach der Ausgabe ’Bitte Passwort eingeben:’ wird Anton
unterbrochen und der Scheduler aktiviert Berta. Berta liest nun das Passwort und gelangt damit
an geheime Informationen.
 */
Hello::Hello(const char* name, int runs, int slice, void* sp) 
: Thread(sp, slice)
{
	this->name = name;
	this->runs = runs;

	out.print(name);
	out.println(" is created!");
	start();
}

Hello::~Hello()
{
	console.attach();
	out.print("Waiting for termination of ");
	out.println(name);
	console.detach();
	this->join();
	console.attach();
	out.print(name);
	out.println(" is terminated");
	console.detach();
}

void Hello::run()
{
	console.attach();
	out.print(name);
	out.println("is running ");
	console.detach();

	for (int i = 0; i < runs; i++) {
		console.attach(); // Konsole reservieren

		out.print(name);
		out.print("> ");

		int size = console.read(line, LINE_SIZE);

		out.print("got: ");
		out.print(size);
		out.print(" ");

		line[size-1] = '\0'; // '\n' durch '\0' ersetzen

		// jetzt koennen wir die Zeile ausgeben
		out.println(line);

		console.detach(); // und freigeben
	}

	console.attach();
	out.print(name);
	out.println("finished");
	console.detach();
}
