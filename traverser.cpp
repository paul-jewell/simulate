
/****************************************************************************
 * Traverser.cpp
 *
 ****************************************************************************/

#include "traverser.h"
#include "event.h"
#include "simulate.h"
#include <string>

Traverser::Traverser(EventList *eventlist)
{
    m_eventlist = eventlist;
}


void Traverser::HandleEvent(Event *evnt)
{
    switch (evnt->eventType) {
    case ev_LoadingComplete:
        m_CTS = false;
        break;
    case ev_atCell1:
    case ev_atCell2:
    case ev_atCell3:
    case ev_atLoadingStation:
        
    default:
        err(std::string("Unhandled event in Traverser::EventHandler()"));
    }
}



bool Traverser::run(void)
{
    // base logic for traverser operation
    // Note: StateChange may be true when the function is called
    // If so, it should be left as true

    STATE oldState, originalState;

    originalState = State;
    do {
        oldState = State;
        switch (State) {
        case st_WaitforPart: // Waiting for part to be loaded from conveyor
            m_CTS = true;
            if (m_infeed->RTS()) {
                State = st_Loading;
                Event * event = new Event(LoadingTime, this, ev_LoadingComplete);
                m_eventlist->push(event);
            }
            break;
        case st_Loading:
            if (!m_CTS) { // m_CTS is cleared by the event handler
                State = st_PartLoaded;
            }
            break;
        case st_PartLoaded:
            // Need to decide where to go. Initial logic - check the three
            // cells, and go to the first available (no HV processing)
            if (m_cell1->CTS()) {
                State = st_MovingtoCell1;
                m_eventlist->push(new Event(LoadtoCell1Time, this, ev_atCell1));
            } else if (m_cell2->CTS()) {
                State = st_MovingtoCell2;
                m_eventlist->push(new Event(LoadtoCell2Time, this, ev_atCell2));
            } else if (m_cell3->CTS()) {
                State = st_MovingtoCell3;
                m_eventlist->push(new Event(LoadtoCell3Time, this, ev_atCell3));
            }
            break;
        case st_MovingtoCell1:
            if (m_atCell1) {
                State = st_AtCell1;
                m_cell1_RTS = true;
            }
            break;
        case st_MovingtoCell2:
            if (m_atCell2) {
                State = st_AtCell2;
                m_cell2_RTS = true;
            }
            break;
        case st_MovingtoCell3:
            if (m_atCell3) {
                State = st_AtCell3;
                m_cell3_RTS = true;
            }
            break;
        case st_AtCell1:
            if (m_cell1->CTS()) {
                State = st_LoadingCell1;
            }
            break;
        case st_AtCell2:
            if (m_cell2->CTS()) {
                State = st_LoadingCell2;
            }
            break;
        case st_AtCell3:
            if (m_cell3->CTS()) {
                State = st_LoadingCell3;
            }
            break;
        case st_LoadingCell1:
            if (!m_cell1->CTS()) { // loading completed
                State = st_MovingtoLoadingStation;
                m_eventlist->push(new Event(Cell1toLoadingStnTime,
                                     this, ev_atLoadingStation));
            }
            break;
        case st_LoadingCell2:
            if (!m_cell2->CTS()) { // loading completed
                State = st_MovingtoLoadingStation;
                m_eventlist->push(new Event(Cell2toLoadingStnTime,
                                     this, ev_atLoadingStation));
            }
            break;
        case st_LoadingCell3:
            if (!m_cell3->CTS()) { // loading completed
                 State = st_MovingtoLoadingStation;
                m_eventlist->push(new Event(Cell3toLoadingStnTime,
                                     this, ev_atLoadingStation));
            }
            break;
        case st_MovingtoLoadingStation:
            if (m_atLoadingStation)
                State = st_WaitforPart;
            break;
        default:
            err(std::string("Reached default case in traverser::run()"));
        }
    } while (State != oldState);
    return !(originalState == State);
}


bool Traverser::CTS(void)
{
    return m_CTS;
}


bool Traverser::RTS(ColdTestCell *cell)
{
    if (cell == m_cell1)
        return m_cell1_RTS;
    else if (cell == m_cell2)
        return m_cell2_RTS;
    else if (cell == m_cell3)
        return m_cell3_RTS;
    else {
        err(std::string("Cell pointer error in Traverser::RTS()"));
        return false;
    }
}

