#ifndef PROCESS_H
#define PROCESS_H

#include "event.h"

class Process
{
public:
    virtual bool run(void) = 0;
    virtual void HandleEvent(Event *event) = 0;
};

#endif
