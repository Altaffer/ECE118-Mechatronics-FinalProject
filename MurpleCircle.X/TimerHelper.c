// timer helpers
// integrate this into Toplevel.c or create a header

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "TopLevel.h"
//#include "TimerHelper.h" //depending on if you wanna keep helpers seperate


#include <stdio.h>
#include <stdlib.h>

uint8_t ExampleTimer_Helper(ES_Event ThisEvent){
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
        posting.EventType = ExampleTimerExp; //When the timer expires, it generates this event
        PostToplevel(posting);//then send the event to the toplevel
        printf("ExampleTimerEXP, %d\r\n", posting.EventType); // debug use.
        break;
    default:
        break;
    }
    return 0;
}