/***************************************************************************
 * events.h..........: event object - contains the information relating
 *                     a simulation event
 *                     eventList object - time ordered list of events
 ***************************************************************************/

#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <vector>
#include <queue>

#include "process.h"

class Event {
private:
    long EventTime; // Simulation time
    
public:
    // TODO: Move event types into individual element 
    enum EventType {
        PartatProcessEntrance,
        ProcessComplete,
        LoadingComplete,
        UnloadingComplete
    };

    Event();
    Event(long time);
    Event(long time, Process *proc, int e);

    long getTime();
    Process *eventReceiver;
    int eventType;
};

class CompareEvent { // used for sorting the events in the EventList
public:
    bool operator()(Event &e1, Event &e2)
    {
        if (e1.getTime() > e2.getTime())
            return true;
        else
            return false;
    }
};

typedef std::priority_queue<Event, std::vector<Event>, CompareEvent> EventList;

#endif
