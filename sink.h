#ifndef SINK_H
#define SINK_H

class Sink : public Process
{
public:
    Sink(EventList *list) { eventlist = list; };

    bool run(void) { return true; } ;
    void HandleEvent(Event *event) { };
private:
    EventList *eventlist;
};


#endif
