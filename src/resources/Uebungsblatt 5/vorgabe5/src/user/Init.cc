#include "user/Init.h"
#include "user/Background.h"
#include "user/Hello.h"
#include "user/Environment.h"
#include "sync/Monitor.h"
#include "io/PrintStream.h"

// die Stacks fuer unsere Threads


static unsigned stack0[1024];
static unsigned stack1[1024];
static unsigned stack2[1024];
static unsigned stack3[1024];


// Hier startet das Hauptprogramm der Applikation!

void Init::run()
{
	console.attach();
	out.println("Application::body() is running\n");
	console.detach();

	monitor.enter();

	Hello anton("Anton",12, 1, &stack0[1024]); // 10
    //Background bg(&stack3[1024], 3000);
    //Hello tim("Tim", 6, 1, &stack3[1024]);
	Hello caesar("Caesar", 5, 1, &stack2[1024]); // 3
    Hello berta("Berta", 9, 1, &stack1[1024]); // 10


    monitor.leave();

	console.attach();
    out.print(&anton);
    out.println();
    //out.print(&berta);
    out.println();
    //out.print(&bg);
    out.println();
    //out.print(&caesar);
    out.println();
	out.println("Application::body() threads created!\n");
	console.detach();
}
