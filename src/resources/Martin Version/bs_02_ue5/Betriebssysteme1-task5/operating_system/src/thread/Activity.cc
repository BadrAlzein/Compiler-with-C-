#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"
#include "io/PrintStream.h"

extern PrintStream out;

/* Aufsetzen eines Threads, der initiale Zustand ist "Blocked",
 * da der Thread erst laufen darf, wenn der spezielle Konstruktor
 * der abgeleiteten Klasse abgearbeitet ist. Die Aktivierung
 * erfolgt von der abgeleiteten Klasse mittels "wakeup".
*/
/**Können Coroutine-Konstruktor (und damit eine Coroutine erzeugen) aufrufen 
 * und mit Top of Stack initialisieren, geht aber nur mithilfe der Initialisierungsliste, 
 * weil sonst Fehler
 * */
Activity::Activity(void *tos, int slices) // Initialer Zustand ist blocked, damit der Thread nicht sofort läuft
	: Schedulable(slices), Coroutine(tos), state(BLOCKED)
{

	
	// Die Aktivierung erfolgt von der abgeleiteten Klasse (Activity) mittels "wakeup".
	
}

/* Verpacken des aktuellen Kontrollflusses als Thread.
 * Wird nur fuer den Hauptkontrollfluss "main" benoetigt.
 * Es wird hier kein Stack initialisiert.
 * Beachte das Activity wegen der Vererbungsbeziehung von
 * Coroutine abstrakt ist. Bei Bedarf muss "body" direkt
 * aufgerufen werden.
 */
Activity::Activity(int slices) // Verpacken des aktuellen Kontrollflusses als Thread. void *tos = 0, //Zustand Blocked, damit Activity/Thread nicht sofort läuft
	: Schedulable(slices), Coroutine(), state(BLOCKED)
{

	// Es wird hier kein Stack initialisiert.
	// -> laueft auf main thread also wenn *tos = 0, dann ist in coroutine das schon abgefangen
	// Beachte das Activity wegen der Vererbungsbeziehung von
	// Coroutine abstrakt ist. Bei Bedarf muss "body" direkt
	// aufgerufen werden.
	/* Dies ist der Rumpf der Coroutine
	 * und muss in abgeleiteten Klassen definiert werden.
	 */
	// virtual void body() = 0;
	// after an activity is created it would be stupid if we do not activate
	this->state = READY;
	//scheduler.schedule((Schedulable *)this);
	/* Initialisieren der ersten Aktivität, des Schedulers
	 * und des Dispatchers.
	 * Wird nur einmal aufgerufen.
	 work on main stack
	 on scheduler we can access anywhere because of extern
	 */
	// void start(Activity* act)
	scheduler.start(this);
}

/* Im Destruktor muss ein explizites Terminieren dieser Aktivitaet erfolgen.
 * Das muss geschehen, da aufgrund der Aufrufreihenfolge von
 * Destruktoren bereits der abgeleitete Teil des Activity-Objekts zerstoert
 * wurde und diese Aktivitaet daher keine Laufzeit mehr erhalten darf.
 * Das Warten auf die Beendigung (mittels join()) muss im Destruktor der
 * von Activity am weitesten abgeleiteten Klasse erfolgen.
 */
Activity::~Activity()
{
	// call join or kill
	/* 	Explizites Terminieren des angegebenen Prozesses
	Der Prozesszustand ist korrekt zu setzen
	und der Prozess aus der Ready-Liste des Schedulers
	zu entfernen. Falls der aktive Prozess zerstoert wird,
	ist dem naechsten lauffaehigen Prozess die CPU
	zuzuteilen.
	 
	void kill(Activity *);

	Terminieren des aktiven Prozesses,
	und Wechsel zum naechsten lauffaehigen Prozess
	
	void exit();
	Für den
	Fall, dass ein Anwender vergisst join () oder kill () im Destruktor einer abgeleiteten Klasse auf-
	zurufen, soll der Activity Destruktor auf jeden Fall ein kill () ausführen. Damit ist sichergestellt,
	dass keine ’Prozessleichen’ auf der Ready-Liste zu finden sind.
	*/
	this->exit();
}

/* Veranlasst den Scheduler, diese Aktivitaet zu suspendieren.
	 */
void Activity::sleep()
{
	/* suspend descritpion
	 *	Suspendieren des aktiven Prozesses
	 * Der korrekte Ausfuehrungszustand ist zu setzen
	 * und danach der naechste lauffaehige Prozess zu aktivieren. Das macht alles suspend
	 */
	// auf scheduler kann zugegriffen werden da in Activity Scheduler extern fuer scheduler
	
/*	if(this->isRunning()) {
		scheduler.suspend();
	} else if(this->isReady()) {
		// if blocked its already blocked
		this->state = BLOCKED;	
	}*/
		
	//out.println("sleep");
	scheduler.suspend();
}

/* Veranlasst den Scheduler, diese Aktivitaet aufzuwecken.
	 */
void Activity::wakeup()
{
	/* 
		virtual void activate(Schedulable* to); 
	* Der aktive Prozess ist, sofern er sich nicht im Zustand
	 * Blocked oder Zombie befindet, wieder auf die Ready-Liste
	 * zu setzen. Danach ist "to" mittels dispatch die Kontrolle
	 * zu �bergeben.
	 */
	// void ActivityScheduler::activate(Schedulable *to)
	if (this->isBlocked())
	{

		//Funktion activate ist nicht erreichbar mit scheduler.activate,
		//deshalb cast nach Activity* welche erbende Klasse ist also auch auf die Methode activate verfügt
		//scheduler.activate((Schedulable *)this);
		this->state = READY;
		scheduler.schedule((Schedulable *)this);
	}
	// ready state is not mentioned because its already on the ready list
}

/* Diese Aktivitaet gibt die CPU vorruebergehend ab. */
void Activity::yield()
{
	// activate the front of list with activate
	// void Scheduler::reschedule()
	// the next item in list gets the cpu
	// could use activityscheduler because its inherited of scheduler and knows reschedule()
	scheduler.reschedule();
}

/* Diese Aktivitaet wird terminiert. Hier muss eine eventuell
 * auf die Beendigung wartende Aktivit�t geweckt werden.
 */
void Activity::exit()
{
	// Hier muss eine eventuell auf die Beendigung wartende Aktivit�t geweckt werden.
	// 1. gehe alle elemente in der suspendierten liste durch und wecke alle wartenden activities
	// 2. töte alle geweckten activities
	// void ActivityScheduler::kill(Activity *act)
	// kill terminiert diese Aktivitaet explizit
	if (blob != 0)
	{
		Activity* blobble = blob;
		blob = 0;		
		blobble->wakeup();
		
	}
	
	// dann die jetztige activity terminieren
	scheduler.kill(this);
	// next kommt von schedulable und dann chain
	// wenn next in chain ein null pointer ist dann hoert while auf
}

/* Der aktuelle Prozess wird solange schlafen gelegt, bis der
 * Prozess auf dem join aufgerufen wird beendet ist. Das
 * Wecken des wartenden Prozesses uebernimmt exit.
 */
void Activity::join()
{
	/*
	Durch den Aufruf der Methode join wird der gerade laufende Prozess suspendiert.
	*/
	/* Suspendieren des aktiven Prozesses
	 * Der korrekte Ausfuehrungszustand ist zu setzen
	 * und danach der naechste lauffaehige Prozess zu aktivieren.
	 */
	// aktiviert implizit den naechsten lauffaehigen prozess
	// der aktuelle prozess wird schlafen gelegt
	// ein anderer prozess muss erst beendet werden, dann kann der aktuelle prozess weiter machen
	
	//Activity* next = scheduler.dequeue();	
	Activity *act = (Activity *)scheduler.active();
	blob = act;
	if ((this->isZombie()) || (act == this)) {
		return;
	} else {	
		
		act->sleep();
	}
	// jetzt aktiviere den prozess auf den join aufgerufen wurde
	// indem wir die cpu der naechsten aktivitaet ueberlassen
	//this->yield();
	// das wecken des wartenden prozess uebernimmt exit
}
/* Aendern des Ausfuehrungszustandes. Diese Methode sollte nur vom
 * Scheduler verwendet werden.
 */
void Activity::changeTo(State state)
{
	//setzen den Membervariablen state auf den Zustand des Parameters state
	this->state = state;
}
