/************************************************************
 * event.cpp
 ************************************************************/

#include "events.h"

Event::Event()
{
    EventTime = 0;
}

Event::Event(long time = 0)
{
    EventTime = time;
}

Event::Event(long time, Process *proc, int e)
{
    EventTime = time;
    eventReceiver = proc;
    eventType = e;
}


long Event::getTime()
{
    return EventTime;
}
