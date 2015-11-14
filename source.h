#ifndef SOURCE_H
#define SOURCE_H

#include "events.h"

class Source : public Process
{
public:
    Source(EventList *list);
    bool RTS(void);
};


#endif
