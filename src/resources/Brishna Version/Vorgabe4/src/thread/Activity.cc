#include "thread/Activity.h"
#include "thread/ActivityScheduler.h"
#include "io/PrintStream.h"

/* Aufsetzen eines Threads, der initiale Zustand ist "Blocked",
 * da der Thread erst laufen darf, wenn der spezielle Konstruktor
 * der abgeleiteten Klasse abgearbeitet ist. Die Aktivierung
 * erfolgt von der abgeleiteten Klasse mittels "wakeup".
*/
/**
initialisinglist from the activity.h class
the initail state is blocked and waiting for a
 task to take place

**/
Activity::Activity(void *tos, int slices) :  Schedulable(slices) , Coroutine(tos), state (BLOCKED)
{
	//Blocked: It is a time interval when a process is
	// waiting for an event like I/O operations to complete.
	//this->state = BLOCKED;
	// waiti
	// the thread will be activated with the help of class Activity
}

/* Verpacken des aktuellen Kontrollflusses als Thread.
	 * Wird nur f�r den Hauptkontrollfluss "main" ben�tigt.
	 * Es wird hier kein Stack initialisiert.
	 * Beachte das Activity wegen der Vererbungsbeziehung von
	 * Coroutine abstrakt ist. Bei Bedarf muss "body" direkt
	 * aufgerufen werden.
	 */
// after creating the activity it should be activated

Activity::Activity(int slices) : Schedulable(slices),Coroutine(), state(BLOCKED)
{
	this->state = READY;
	scheduler.start(this);
}

/* Im Destruktor muss ein explizites Terminieren dieser Aktivitaet erfolgen.
	 * Das muss geschehen, da aufgrund der Aufrufreihenfolge von
	 * Destruktoren bereits der abgeleitete Teil des Activity-Objekts zerstoert
	 * wurde und diese Aktivitaet daher keine Laufzeit mehr erhalten darf.
	 * Das Warten auf die Beendigung (mittels join()) muss im Destruktor der
	 * von Activity am weitesten abgeleiteten Klasse erfolgen.
	 */
// to allow us to access the member of the derived class we
//use the virtual function
// *Avtivity is the base class pointer that we use to access the base class memebers
// cpp permits the base pointer to point to any any object derived from the base class, it cann not access
//the members of the derived class thats why virtual func is used
//~Activity is the destructor and it destroys the object as soon as it goes out of the scoop
Activity::~Activity()
{
	//kill func taken from Scheduler , kills the current process
	//as soon as a process executes the last instruction , this function will be called
	scheduler.kill(this);
}

/* Veranlasst den Scheduler, diese Aktivitaet zu suspendieren.
	 */

//sleep causes the thread to definitly stop executing for a given amount of time
//if no other process or thread needs to be run then CPU will go to power saving mode
void Activity::sleep()
{
	//suspend the active process
	//sleep can be called from and active process
	//Suspended: Suspended state defines the time when a process is ready for
	// execution but has not been placed in the ready queue by OS.
	scheduler.suspend();
}

/* Veranlasst den Scheduler, diese Aktivitaet aufzuwecken.
	 */
void Activity::wakeup()
{
       IntLock lock;
	if (isBlocked()) //BadrADDD
	{
		this->state = READY;
		// queue the Process
		scheduler.schedule(this);
	}
}

/* Diese Aktivitaet gibt die CPU vorruebergehend ab. */
void Activity::yield()
{

	/*
	this method will pause the execution of currently running process so that the other
	waiting thread with the same priority which are waiting in the queue get the CPU to execute.
	if there is no waiting thread then this thread will start its execution
	*/
	scheduler.reschedule();
}

/* Diese Aktivitaet wird terminiert. Hier muss eine eventuell
 * auf die Beendigung wartende Aktivit�t geweckt werden.
 */
void Activity::exit()
{
	/*
	the activity that is supposed to be terminated , will be wakenup here
	so basicly we check for all the elements in suspending list and wake all the waiting ativities up
	and kill the waken activities (defined in ActivitySceduler.cc)

	*/

	if (joinACtivity != 0)
	{
		joinACtivity->wakeup();
		joinACtivity = 0;
	}

	scheduler.exit();
}

/* Der aktuelle Prozess wird solange schlafen gelegt, bis der
	 * Prozess auf dem join aufgerufen wird beendet ist. Das
	 * Wecken des wartenden Prozesses �bernimmt exit.
	 */
/*
stops currently executing thread and wait for another to complete, 
then it wil start its execution again
e.g if any executing thread (getCurrentActivity()) calls join() on joinActivity like (joinAvtivity.thread2)
getCurrentActivity will enter (waiting) sleep state untill thread2 complets its execution
after that it will resume its execution
*/

void Activity::join()
{
     IntLock lock;
    
    //active transfers the pointer on the active process(from dispatcher)
    // i set the new process (child process) to the current running process and put the parent process on sleep untill the chiled process completes the task
    Activity *runningProcess = scheduler.getCurrentActivity();
    
   if ( this != runningProcess && !(this->isZombie())){
       
        this->joinACtivity =runningProcess;
        
       scheduler.suspend();
   }
    
   // runningProcess->sleep();
	//.getCurrentActivity() will get the current active process
	// joinActivity is the new activity
	
    /*
    joinACtivity = scheduler.getCurrentActivity();
    
	if ((!isZombie())) // ignore if its a zombie state, 
	{
		if (this != joinACtivity)
		{
			joinACtivity->sleep();
		}
	}
	*/
    
    
}
