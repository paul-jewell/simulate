
#include <iostream>
#include <stdlib.h>
#include <string>

#include "events.h"
#include "traverser.h"
#include "coldtestcell.h"
#include "source.h"
#include "sink.h"
#include "simulate.h"

long SimulationTime = 0;

int main(int argc, char **argv)
{
    EventList eventlist;
    Traverser traverser(&eventlist);
    ColdTestCell cell1(&eventlist,&traverser);
    ColdTestCell cell2(&eventlist, &traverser);
    ColdTestCell cell3(&eventlist, &traverser);
    Source supply(&eventlist);
    Sink derig(&eventlist);

    // Connect up production layout
    
    traverser.cell1(&cell1);
    traverser.cell2(&cell2);
    traverser.cell3(&cell3);
    traverser.infeed(&supply);
//    traverser.outfeed(derig);
}


void err(std::string str)
{
    std::cerr << str << std::endl;
}

void err(char *msg)
{
    std::cerr << msg << std::endl;
    exit(1);
}

/*
int testmain(int argc, char **argv)
{
    Event myEvent;
    myEvent = Event(300);

    std::cout << "myEvent time: " << myEvent.getTime() << std::endl;
    EventList.push(myEvent);
    
    EventList.push(Event(200));
    EventList.push(Event(150));

    std::cout << "three events pushed - now outputing: " << std::endl;
        
    while (! EventList.empty()) {
        myEvent = EventList.top();
        std::cout << myEvent.getTime() << std::endl;
        EventList.pop();
    }
}


void simulate()
{
    Event currEvent;
    while (! EventList.empty()) {
        currEvent = EventList.top();
        simulationTime = currEvent.time;
        currEvent.callback(); // Call event creation routine

        // Iterate through the processes and check states

        bool StateChange = false;
        do {
            StateChange = Traverser.run() ||
                ColdTest1.run() ||
                ColdTest2.run() ||
                ColdTest3.run();
        } while (statechange == true);

        // Process statistics
    }
}

    
  
  
*/
