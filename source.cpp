/***************************************************************************
 * source.cpp.......: Manages the engine feed into the traverser.
 ***************************************************************************/

#include "source.h"
#include "event.h"
#include "simulate.h"

Source::Source(EventList *list, Traverser *traverser)
    : m_EventList(list), m_RTS(true), State(st_WaitingtoSend)
{
}


bool Source::RTS(void)
{
    return m_RTS;
}

bool Source::run(void)
{
    STATE oldState, originalState;
    originalState = State;
    do {
        switch (State) {
        case st_WaitingtoSend:
            if (m_Traverser->CTS()) {
                m_RTS = true; //Indicate ready to send part
                State = st_SendingPart;
            }
            break;
        case st_SendingPart:
            if (!m_Traverser->CTS()) { // Part sending completed
                State = st_WaitForPart;
                m_EventList->push(new Event(PartArrivalTime(),
                                            this, ev_PartAvailable));
            }
            break;
        default:
            err(std::string("Unhandled event in Source::run()\n"));
        }
        return originalState != State;
    } while (oldState != State);
    return originalState != State;
}

void Source::HandleEvent(Event *event)
{
    switch (event->getEventType()) {
    case ev_PartAvailable:
        // Get the next engine from the list
        m_RTS = true; // Indicate part ready
        State = st_WaitingtoSend;
        break;
    default:
        err(std::string("Unhandled event in Source::HandleEvent()\n"));
    }
}

int Source::PartArrivalTime(void)
{
    // TODO: consider variation in interarrival times
    return 45;
}
