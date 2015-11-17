/***************************************************************************
 * source.cpp.......: Manages the engine feed into the traverser.
 ***************************************************************************/

#include "source.h"
#include "event.h"


Source::Source(EventList *list)
{
    m_EventList = list;
}

bool Source::RTS(void)
{
    return m_RTS;
}

bool Source::run(void)
{
}

void Source::HandleEvent(Event *event)
{
    // Handle event
}

