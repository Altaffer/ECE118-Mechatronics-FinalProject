// timer helpers
// integrate this into Toplevel.c or create a header

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "TopLevel.h"
#include "TimerHelper.h" 
#include "AD.h"
#include "ES_Timers.h"
#include <robot.h>

#include <stdio.h>
#include <stdlib.h>

uint8_t TurnTimerHelper(ES_Event ThisEvent){
    ES_Event posting;
    
    switch (ThisEvent.EventType) {
    case ES_INIT: //do nothing (initializing)
        break;
    
    /* do nothng */
    case ES_TIMERACTIVE:
    case ES_TIMERSTOPPED:
        break; // We don't use these events

    /* run internal event checkers */
    case ES_TIMEOUT:
        posting.EventParam = 1;
        posting.EventType = TURN_TIMER_EXP; //When the timer expires, it generates this event
        PostTopLevel(posting);//then send the event to the toplevel
        printf("ExampleTimerEXP, %d\r\n", posting.EventType); // debug use.
        break;
    default:
        break;
    }
    return 0;
}

uint8_t MotionTimerHelper(ES_Event ThisEvent){
    ES_Event posting;
    
    switch (ThisEvent.EventType) {
    case ES_INIT: //do nothing (initializing)
        break;
    
    /* do nothng */
    case ES_TIMERACTIVE:
    case ES_TIMERSTOPPED:
        break; // We don't use these events

    /* run internal event checkers */
    case ES_TIMEOUT:
        posting.EventParam = 1;
        posting.EventType = MOTION_TIMER_EXP; //When the timer expires, it generates this event
        PostTopLevel(posting);//then send the event to the toplevel
        printf("ExampleTimerEXP, %d\r\n", posting.EventType); // debug use.
        ES_Timer_StopTimer(MotionTimer);
        break;
    default:
        break;
    }
    return 0;
}