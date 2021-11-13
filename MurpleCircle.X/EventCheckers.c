/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "EventCheckers.h"
#include "ES_Events.h"
#include "serial.h"
#include "AD.h"
#include "roach.h"
#include "robot.h"
#include "BOARD.h"
//#include "TemplateHSM.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define BATTERY_DISCONNECT_THRESHOLD 175
#define ON_BLACK_TAPE 1
#define OFF_BLACK_TAPE 0

/*******************************************************************************
 * EVENTCHECKER_TEST SPECIFIC CODE                                                             *
 ******************************************************************************/
//#define EVENTCHECKER_TEST
#ifdef EVENTCHECKER_TEST
#include <stdio.h>
#include <ES_Events.h>
#define SaveEvent(x) do {eventName=__func__; storedEvent=x;} while (0)

static const char *eventName;
static ES_Event storedEvent;
#endif

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this EventChecker. They should be functions
   relevant to the behavior of this particular event checker */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                    *
 ******************************************************************************/

/* Any private module level variable that you might need for keeping track of
   events would be placed here. Private variables should be STATIC so that they
   are limited in scope to this module. */

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Funtion LightEventChecker(void)
 * @param none
 * @return TRUE or FALSE
 * @brief This function is an event checker that checks the light level against
 *        the light and dark thresholds and takes into account the hysteresis. 
 *        The previous state, INTO_LIGHT or INTO_DARK, of the light level is
 *        stored and used to compare with the current state of the light level.
 *        If an event occurs, TRUE will returned and if not FALSE will be
 *        returned
 */
uint8_t TapeSensorEventChecker(void) {
    static ES_EventTyp_t lastEvent = OFF_BT;

    // Setting a value because currentEvent would be initialized to some random 
    // value. 
    ES_EventTyp_t currentEvent = lastEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    int tapeSensorInput = Robot_ReadTapeSensors();

    if (tapeSensorInput == OFF_BLACK_TAPE) {
        currentEvent = OFF_BT;
    }else{
        currentEvent = ON_BT;
    }
    if (currentEvent != lastEvent) {
        thisEvent.EventType = currentEvent;
        thisEvent.EventParam = tapeSensorInput;
        lastEvent = currentEvent;
        returnVal = TRUE;
#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        //        PostTemplateHSM(thisEvent);
        //        PostGenericService(thisEvent);
#else
        SaveEvent(thisEvent);
#endif   
    }
    return (returnVal);
}

/* 
 * The Test Harness for the event checkers is conditionally compiled using
 * the EVENTCHECKER_TEST macro (defined either in the file or at the project level).
 * No other main() can exist within the project.
 * 
 * It requires a valid ES_Configure.h file in the project with the correct events in 
 * the enum, and the correct list of event checkers in the EVENT_CHECK_LIST.
 * 
 * The test harness will run each of your event detectors identically to the way the
 * ES_Framework will call them, and if an event is detected it will print out the function
 * name, event, and event parameter. Use this to test your event checking code and
 * ensure that it is fully functional.
 * 
 * If you are locking up the output, most likely you are generating too many events.
 * Remember that events are detectable changes, not a state in itself.
 * 
 * Once you have fully tested your event checking code, you can leave it in its own
 * project and point to it from your other projects. If the EVENTCHECKER_TEST marco is
 * defined in the project, no changes are necessary for your event checkers to work
 * with your other projects.
 */
#ifdef EVENTCHECKER_TEST
#include <stdio.h>
static uint8_t(*EventList[])(void) = {EVENT_CHECK_LIST};

void PrintEvent(void);

void main(void) {
    BOARD_Init();
    Roach_Init();
    /* user initialization code goes here */

    // Do not alter anything below this line
    int i;

    printf("\r\nEvent checking test harness for %s", __FILE__);

    while (1) {
        if (IsTransmitEmpty()) {
            for (i = 0; i< sizeof (EventList) >> 2; i++) {
                if (EventList[i]() == TRUE) {
                    PrintEvent();
                    break;
                }

            }
        }


    }
}

void PrintEvent(void) {
    printf("\r\nFunc: %s\tEvent: %s\tParam: 0x%X", eventName,
            EventNames[storedEvent.EventType], storedEvent.EventParam);
}
#endif