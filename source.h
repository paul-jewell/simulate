#ifndef SOURCE_H
#define SOURCE_H

class Source;

#include "event.h"
#include "traverser.h"

class Source : public Process
{
public:
    Source(EventList *list, Traverser *traverser);
    bool RTS(void);

    bool run(void);
    void HandleEvent(Event *event);

private:
    EventList *m_EventList; // Pointer to eventlist
    bool m_RTS;             // Part ready to deliver to Traverser
    Traverser *m_Traverser; // Pointer to traverser
    enum STATE{
        st_WaitForPart,
        st_WaitingtoSend,
        st_SendingPart,
    } State;

    enum EVENT_TYPE{
        ev_PartAvailable
    };
    
    int PartArrivalTime(void);
};


#endif
