#ifndef TRAVERSER_H
#define TRAVERSER_H
/*****************************************************************************
 * traverser.h  
 * -----------
 *
 * conveyor section between line and cold test cells. Feeds three cells,
 * and also has a buffer for HV engines
 *
 *****************************************************************************/

#include <iostream>

class Traverser;

#include "coldtestcell.h"
#include "process.h"
#include "source.h"
#include "events.h"

class Traverser : public Process
{
public:

    Traverser(EventList *eventlist);
    
    bool run(void);
    void ProcessEvent(Event *evnt);
    bool RTS(ColdTestCell *cell);
    bool CTS(void);
        
    // Helper functions to initialise the process net
    void cell1(ColdTestCell *c1) { m_cell1 = c1; };
    void cell2(ColdTestCell *c2) { m_cell2 = c2; };
    void cell3(ColdTestCell *c3) { m_cell3 = c3; };
    void infeed(Source *in)     { m_infeed = in; };
      
    enum STATE {
        st_WaitforPart,
        st_Loading,
        st_PartLoaded,
        st_MovingtoCell1,
        st_MovingtoCell2,
        st_MovingtoCell3,
        st_AtCell1,
        st_AtCell2,
        st_AtCell3,
        st_LoadingCell1,
        st_LoadingCell2,
        st_LoadingCell3,
        st_MovingtoLoadingStation
    };

    enum EVENT_TYPE {
        ev_LoadingComplete,
        ev_atCell1,
        ev_atCell2,
        ev_atCell3,
        ev_atLoadingStation,
    };
        
private:
    STATE State;
    
    ColdTestCell *m_cell1;
    ColdTestCell *m_cell2;
    ColdTestCell *m_cell3;
    Source *m_infeed;
    EventList *m_eventlist;

    bool m_Loading;
    bool m_atCell1;
    bool m_atCell2;
    bool m_atCell3;
    bool m_atLoadingStation;
    bool m_CTS;       // Ready to receive part from infeed
    bool m_cell1_RTS; // Signal downstream cells that part is ready
    bool m_cell2_RTS; // to load
    bool m_cell3_RTS;

    static const float LoadingTime = 10.0; // seconds
    static const float LoadtoCell1Time = 10.0;
    static const float LoadtoCell2Time = 10.0;
    static const float LoadtoCell3Time = 10.0;
    static const float Cell1toLoadingStnTime = 20.0;
    static const float Cell2toLoadingStnTime = 15.0;
    static const float Cell3toLoadingStnTime = 10.0;
    
    
};

#endif
