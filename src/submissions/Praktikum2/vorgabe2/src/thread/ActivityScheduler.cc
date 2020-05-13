#include "thread/ActivityScheduler.h"
#include "io/PrintStream.h"



/* This class will implements all func from the class in thread/ActivityScheduler.h
 * exit()
 * activate()
 * suspend()
 * kill()
 * getActivitySchudler()
 */



/* Terminieren des aktiven Prozesses,
* und Wechsel zum naechsten lauffaehigen Prozess
*/
void ActivityScheduler::exit(){
    
    
    
    
}

/* Explizites Terminieren des angegebenen Prozesses
	 * Der Prozesszustand ist korrekt zu setzen
	 * und der Prozess aus der Ready-Liste des Schedulers
	 * zu entfernen. Falls der aktive Prozess zerstoert wird,
	 * ist dem naechsten lauffaehigen Prozess die CPU
	 * zuzuteilen.
*/
void ActivityScheduler::kill(){
    
    
    
}
/* Der aktive Prozess ist, sofern er sich nicht im Zustand
	 * Blocked oder Zombie befindet, wieder auf die Ready-Liste
	 * zu setzen. Danach ist "to" mittels dispatch die Kontrolle
	 * zu übergeben.
*/
void ActivityScheduler::activate(){
    
    
    
}

/* Suspendieren des aktiven Prozesses
* Der korrekte Ausfuehrungszustand ist zu setzen
* und danach der naechste lauffaehige Prozess zu aktivieren.
*/
void ActivityScheduler::suspend(){
    
    
}




void ActivityScheduler::getActivitySchudler(){
    
    
}
