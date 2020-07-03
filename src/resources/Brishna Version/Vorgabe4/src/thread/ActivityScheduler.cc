#include "thread/ActivityScheduler.h"
#include "io/PrintStream.h"
#include "device/Clock.h"
#include "interrupts/IntLock.h"
extern Clock clock;

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
void ActivityScheduler::exit()
{
     IntLock lock; //safe this kritische Abschnitt
	/** to exit 
	 * 1. kill the current activity 
	 * 2. reschedule (activate the first process from the list)
	*/
	kill((Activity *)active()); //active() will point to the current activity
	reschedule();				//send the next process on the top of ready list to the scedular
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
void ActivityScheduler::kill(Activity *process)
{
     IntLock lock; //safe this kritische Abschnitt wegen exit (coroutine)
	//change the mode to Process deleteing mode
	process->changeTo(Activity::ZOMBIE);

	//remove the process from the ready list
	remove((Schedulable *)process);

	Activity *Act = this->getCurrentActivity();
	//if (Act->isRunning() && Act == process)
    if (Act == process)
	{
		this->reschedule();
	}
}
/* 1.Der aktive Prozess ist, sofern er sich
 	 * 	1.1. nicht im Zustand Blocked -> not blocked
	 * 	1.2. oder Zombie befindet, 	-> not zombie 
	 * 	1.3. wieder auf die Ready-Liste zu setzen. -> not waitint -> is Running currently
	 *  1.4. Add it to the Ready list
* 2.Danach ist "to" mittels dispatch die Kontrolle zu übergeben.
*/
void ActivityScheduler::activate(Schedulable *to)
{
 IntLock lock; //safe this kritische Abschnitt 
	Activity *currentAct = this->getCurrentActivity(); //get the current activity
    
 /** deal with current Act ***/   
	if (currentAct->isRunning())
	{
		currentAct->changeTo(Activity::READY);		   //change the activity to Ready
		scheduler.schedule((Schedulable *)currentAct); //add it to the Ready list
	}

/**deal with target Activity */

  Activity *targetAct = (Activity *)to;
	
 /** deal with empty readylist***/   
	if (targetAct == 0)
	{
        //make sure that the ready list is empty
		if (currentAct->isZombie() || currentAct->isBlocked()){ 
			//trigger that will decide if the cpu is busy waiting or not
           if (IsActiveWaiting){
               //while there are not activitys in the ready list
                 while(targetAct == 0) {
					//switch to halting mode -> not active watiing anymore
                    IsActiveWaiting=false;
                   //(cased by Intlock) -> enable Interrupt so halt can wait until an interrupt comes
                   cpu.enableInterrupts();
                   //halt the cpu with an enable interrupts
                   cpu.halt();
                   //(cased by Intlock) -> disable the interrupts again
                   cpu.disableInterrupts();
                       //remove target from ready list
                   targetAct = (Activity *)readylist.dequeue();	
                	
                }
                /** Readylist is not empty anymore **/
                
                //switch to active waiting mode
                IsActiveWaiting = true;
                
                /** deal with activate a normal target Act ***/ 
                if (targetAct != 0){
                    //if the is still a current activity running 
                    if (currentAct->isRunning())
                            {
                                  //change the current activity to Ready
                                    currentAct->changeTo(Activity::READY);		 
                                    //add it to the Ready list
                                    scheduler.schedule((Schedulable *)currentAct); 
                            }
                    //deal with the target activity 
                     targetAct->changeTo(Activity::RUNNING); 
                     dispatch(targetAct);	
                    
                }
            }
		}
	}

/** deal with activate a normal target Act ***/   
if (targetAct != 0)
	{
		//make the target Act running
		targetAct->changeTo(Activity::RUNNING); //make the target Running
		dispatch(targetAct);					//swich from current active Act to the target Act
	}
}


/* Suspendieren des aktiven Prozesses
* 1. Der korrekte Ausfuehrungszustand ist zu setzen
* und danach 
* 2.der naechste lauffaehige Prozess zu aktivieren.
*/
void ActivityScheduler::suspend()
{
    IntLock lock; //safe this kritische Abschnitt
    
	/** to make a the Scheduler suspend his current Process 
	 * 1. get the current process and block it 
	 * 2. reschedule (activate the first process from the Ready list)
	 */

	//block the current activity  (getCurrentActivity() will get the current Activity)
	getCurrentActivity()->changeTo(Activity::BLOCKED);

	//send the next process on the top of ready list to the scedular
	this->reschedule();
}


/** resheduler if the quatum has reached the ticks of the clk then reset the clk */
void ActivityScheduler::checkSlice()
{
    IntLock lock ;
	Schedulable *active = (Schedulable *) getCurrentActivity();
    
     //  out.print(active->quantum());
	if (active->quantum() <=  clock.ticks())
	{
     //  out.print("checkslice");
       // out.println();
		clock.resetTicks(); //<= BRISHNA
		reschedule(); //reschedule aufrufen, wenn Zeitscheibe(Quantum) abgelaufen ist
	}
}



