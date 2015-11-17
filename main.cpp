/*******************************************************************************
 * main.cpp
 * --------
 * Cold test simulation to confirm the ratio impact through discrete event
 * simulation
 *
 * by............: Paul Jewell
 * Date Started..: 30th October 2015
 *******************************************************************************/


#include <iostream>
#include <string>

#include "event.h"
#include "traverser.h"
#include "coldtestcell.h"
#include "source.h"
#include "sink.h"
#include "simulate.h"


long SimulationTime = 0;

int main(int argc, char **argv)
{
    EventList eventlist;
    ProcessList processes;

    long ev_EndSimulation = 0;
    
    Traverser traverser(&eventlist);
    ColdTestCell cell1(&eventlist,&traverser);
    ColdTestCell cell2(&eventlist, &traverser);
    ColdTestCell cell3(&eventlist, &traverser);
    Source supply(&eventlist, &traverser);
    Sink derig(&eventlist);

    processes.push_back(&traverser);
    processes.push_back(&cell1);
    processes.push_back(&cell2);
    processes.push_back(&cell3);
    processes.push_back(&supply);
    processes.push_back(&derig);
    
    // Connect up production layout
    
    traverser.cell1(&cell1);
    traverser.cell2(&cell2);
    traverser.cell3(&cell3);
    traverser.infeed(&supply);
    traverser.outfeed(&derig);

    // Initialise the processes

    eventlist.push(new Event(100000,
                             nullptr,
                             ev_EndSimulation)); // End Simulation Event
    bool change;
    do {
        change = false;
        for (ProcessList::iterator i = processes.begin();
                 i != processes.end(); i++)
            change |= (*i)->run(); // Run each process until no change
    } while (change);


    // Run the event management loop.
    while (Event *event = eventlist.top()) {
        eventlist.pop(); // Remove the top element from the list
        SimulationTime += event->getTime(); // Advance simulation time
        if (event->getEventType() == ev_EndSimulation)
            break;
        event->getProcess()->HandleEvent(event);
        delete event; // no longer needed
    }
}


void err(std::string str)
{
    std::cerr << str << std::endl;
    exit(1);
}

void err(char *msg)
{
    std::cerr << msg << std::endl;
    exit(1);
}
