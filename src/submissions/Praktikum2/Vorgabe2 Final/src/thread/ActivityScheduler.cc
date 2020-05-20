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

	
	Activity *Act = this->getCurrentActivity();
	if (Act->isRunning() && Act==process){
		reschedule(); 
	}
}
/* 1.Der aktive Prozess ist, sofern er sich
 	 * 	1.1. nicht im Zustand Blocked -> not blocked
	 * 	1.2. oder Zombie befindet, 	-> not zombie 
	 * 	1.3. wieder auf die Ready-Liste zu setzen. -> not waitint -> is Running currently
	 *  1.4. Add it to the Ready list
* 2.Danach ist "to" mittels dispatch die Kontrolle zu übergeben.
*/
void ActivityScheduler::activate(Schedulable *to){

	/* this func send the running act to the ready and take a act from Ready list 
		and make it to running 
	*/


	Activity *newAct = this->getCurrentActivity(); //get the current activity
	//define the active process conditions
	bool notZombie = ! newAct->isZombie();
	bool notBlocked = ! newAct->isBlocked();
	bool isRunning = newAct->isRunning();
	bool isActiveAct = notZombie && (notBlocked && isRunning);
    
	//if there is an active process then add it to the Ready list  
	if (isActiveAct){
		newAct->changeTo(Activity::READY); //change the activity to Ready
		scheduler.schedule((Schedulable *)newAct);	//add it to the Ready list
	} 
	Activity *targetAct = (Activity *)to; 

	/*Pending 
		Nullpointer Exception	
	 */
	while (targetAct == 0){
		if(! newAct->isRunning()){
			targetAct = (Activity *)readylist.dequeue();
		}
	}
	if (targetAct!=0) {
		//make the target Act running
		
		targetAct->changeTo(Activity::RUNNING); //make the target Running
		dispatch(targetAct); //swich from current active Act to the target Act 
	}
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

	//block the current activity  (getCurrentActivity() will get the current Activity) 
	getCurrentActivity()->changeTo(Activity::BLOCKED);
	
	//send the next process on the top of ready list to the scedular
	reschedule(); 
}


