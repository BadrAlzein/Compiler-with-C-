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
	/** to exit 
	 * 1. kill the current activity 
	 * 2. reschedule (activate the first process from the list)
	*/
    kill((Activity *) active()); //active() will point to the current activity
	reschedule(); //send the next process on the top of ready list to the scedular
    
}

/* Explizites Terminieren des angegebenen Prozesses
	 * Der Prozesszustand ist korrekt zu setzen
	 * und 
	 * 1. der Prozess aus der Ready-Liste des Schedulers
	 * zu entfernen. 
	 * 2. Falls der aktive Prozess zerstoert wird,
	 * ist dem naechsten lauffaehigen Prozess die CPU
	 * zuzuteilen.
*/
void ActivityScheduler::kill(Activity *process){
    //change the mode to Process deleteing mode 
	process->changeTo(Activity::ZOMBIE);

    //remove the process from the ready list 
	remove((Schedulable *)process);

	//send the next process on the top of ready list to the scedular
	reschedule(); 
    
}
/* Der aktive Prozess ist, sofern er sich nicht im Zustand
	 * Blocked oder Zombie befindet, wieder auf die Ready-Liste
	 * zu setzen. Danach ist "to" mittels dispatch die Kontrolle
	 * zu übergeben.
*/
void ActivityScheduler::activate(Schedulable *to){
    
    
    
}

/* Suspendieren des aktiven Prozesses
* 1. Der korrekte Ausfuehrungszustand ist zu setzen
* und danach 
* 2.der naechste lauffaehige Prozess zu aktivieren.
*/
void ActivityScheduler::suspend(){
	/** to make a the Scheduler suspend his current Process 
	 * 1. get the current process and block it 
	 * 2. reschedule (activate the first process from the Ready list)
	 */

	//block the current activity  (getActivity() will get the current Activity) 
	getActivity()->changeTo(Activity::BLOCKED);
	
	//send the next process on the top of ready list to the scedular
	reschedule(); 
}

/*this will return a pointer to the current process Activity from dispatcher*/
Activity *ActivityScheduler::getActivity()
{
    return (Activity *)this->active();
    
}

