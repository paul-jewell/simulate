#ifndef COLDTESTCELL_H
#define COLDTESTCELL_H
/****************************************************************************
 * ColdTestCell
 ****************************************************************************/

class ColdTestCell;

#include "events.h"
#include "process.h"
#include "traverser.h"

class ColdTestCell : public Process
{
public:
    ColdTestCell(EventList *list, Traverser *Traverser);
    
    bool run(void);
    bool PartReady(void);
    void Unload(void);
    void Load();

    bool CTS(void);
    bool RTS(void);
    
    static const int LoadingTime = 4;
    static const int CycleTime = 60;

private:
    enum STATE {
        NoWork,
        Loading,
        Unloading,
        Running,
        FullWork
    } currState;

    bool m_CTS;
    bool m_RTS;
    
    void ProcessEvent(Event event);
    
    EventList *eventlist;

    Traverser *traverser;
    
    // ...Interlocks to interface other objects
    bool unloadEnable;      // ... to be taken from cell
    bool loading;           // ... in progress
    bool unloading;         // ... in progress
    bool loadEnable;
    bool partReady;
    // ...Internal states
    bool PartLoaded;        // ... and ready to test
    bool CellisRunning;     // ... Under test
    bool ProcessingComplete;
    bool loadingComplete;
};


#endif
