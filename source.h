#ifndef SOURCE_H
#define SOURCE_H

#include "event.h"

class Source : public Process
{
public:
    Source(EventList *list);
    bool RTS(void);

    bool run(void);
    void HandleEvent(Event *event);
    
 private:
    EventList *m_EventList; // Pointer to eventlist
    bool m_RTS;             // Part ready to deliver to Traverser
};


#endif
