/****************************************************************************
 * ColdTestCell
 ****************************************************************************/
#include <string>

#include "coldtestcell.h"
#include "simulate.h"
#include "event.h"

ColdTestCell::ColdTestCell(EventList *list, Traverser *Traverser)
{
    eventlist = list;
    traverser = Traverser;
    currState = NoWork; // Assumed to have a finished OK engine in the cell
    // and be ready for it to be collected.
    unloadEnable = true;
    loading = false;
    unloading = false;
    loadEnable = false;

    PartLoaded = false;
    partReady = false;       // TODO: Check initial state assumption
    CellisRunning = false;
    ProcessingComplete = true;
    loadingComplete = false; // TODO: Added - Check state table
}


bool ColdTestCell::run(void)
{
    STATE oldState, originalState;
    
    originalState = currState;
    do {
        oldState = currState;
        switch (currState) {
        case NoWork:
            // To exit no work state, we need to have confirmation of
            // loading from the traverser.
            if (traverser->RTS(this)) {
                m_CTS = true;
                currState = Loading;
                loading = true;
                eventlist->push(new Event(LoadingTime, this, Event::LoadingComplete));
            }
            break;
        case Loading:
            if (PartLoaded) {
                loadEnable = false;
                currState = Running;
                eventlist->push(new Event(CycleTime, this, Event::ProcessComplete));
            }
            break;
        case Running:
            if (!CellisRunning) {
                unloadEnable = true;
                currState = FullWork;
            }
            break;
        case FullWork:
            break;
        default:
            err(std::string("Reached default case in ColdTestCell::run()"));
        }
    } while (currState != oldState);
    return !(originalState == currState);
}

void ColdTestCell::HandleEvent(Event *event)
{
    switch (event->eventType)
    {
    case Event::ProcessComplete:
        CellisRunning = false;
        unloadEnable = true;
        break;
    case Event::LoadingComplete:
        m_CTS = false;
        PartLoaded = true;
        break;
    case Event::UnloadingComplete:
        PartLoaded = false;
        break;
    }
}

bool ColdTestCell::PartReady(void)
{
    return partReady;
}

void ColdTestCell::Unload(void)
{
    unloading = true;
    partReady = false;
}

bool ColdTestCell::CTS(void)
{
    return m_CTS;
}


bool ColdTestCell::RTS(void)
{
    return m_RTS;
}

