/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "EventCheckers.h"
#include "ES_Events.h"
#include "ES_Timers.h"
#include "serial.h"
#include "AD.h"
#include "roach.h"
#include "robot.h"
#include "BOARD.h"
#include "TopLevel.h"
#include "timers.h"
#include "stdio.h"
#include "stdlib.h"

#include "IO_Ports.h"


/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define BATTERY_DISCONNECT_THRESHOLD 175
#define ON_BLACK_TAPE 1
#define OFF_BLACK_TAPE 0
#define TW_UPPER_BOUND 500
#define TW_LOWER_BOUND 200
#define BEACON_UPPER_BOUND 500
#define BEACON_LOWER_BOUND 200
#define BEACON_DETECTED 0
#define BEACON_NOT_DETECTED 1
#define PING_MAX 700
#define SHOOTER 48 //0b 11 0000
#define BOTTOM 15 //0b 00 1111

//comment this out if you don't want to consider prev values for the track wire's
//   hysteresis bounds
#define TAKE_PREV

//enable this if you want to see spamming prints at each event to debug
//#define DEBUG_PRINTS
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
#ifndef USE_TAPE_SERVICE
    static ES_EventTyp_t lastEvent = ES_NO_EVENT;
    static uint8_t past_val = 0 ;
    // Setting a value because currentEvent would be initialized to some random 
    // value. 
    ES_EventTyp_t currentEvent = lastEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    int tapeSensorInput = Robot_ReadTapeSensors();
    uint8_t change = tapeSensorInput ^ past_val;

    if (!change) {
        currentEvent = ES_NO_EVENT;
    } else if (change & BOTTOM) {
        currentEvent = BOT_BT_CHANGED;
    } else {
        currentEvent = SHOOTER_BT_CHANGED;
    }
#ifdef DEBUG_PRINTS
    if (currentEvent == BOT_BT_CHANGED) {
        printf("Bottom Tape Sensor Change: %d.\r\n", tapeSensorInput);
    } else if (currentEvent == SHOOTER_BT_CHANGED){
        printf("Shooter Tape Sensor Change: %d.\r\n", tapeSensorInput);
    }
#endif
    if (currentEvent != lastEvent) {
        thisEvent.EventType = currentEvent;
        thisEvent.EventParam = tapeSensorInput;
        PostTopLevel(thisEvent); // added 11/14
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
#endif //using service?
    return (0); 
}

/**
 * @Function TrackWireEventChecker(void)
 * @param void
 * @return TRUE or FALSE
 * @brief 2 options: if you defined "TAKE_PREV", it will compare the previous 
 *          Track wire values with the current ones. Returns True and post event
 *          if there is change, False otherwise. This is default.
 * 
 *          If you didn't define "TAKE_PREV", it will only look at the current
 *          values of the Track wire values and post sensor outputs continuously
 *          until the value drops below the LOWER_BOUND. 
 * @author Horace, 11/14 */

uint8_t TrackWireEventChecker(void) {
    static ES_EventTyp_t lastEvent = ES_NO_EVENT; 
    // Setting a value because currentEvent would be initialized to some random 
    // value. 
    ES_EventTyp_t currentEvent = lastEvent;
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    uint32_t TrackWireInput = Robot_ReadTrackWire();
    uint8_t recording = 0; //this is a flag to indicate if the track wire is detected
        //if it does, then it starts to record the ADC output to find the distance
        //between the track wire and the sensor
        //initial state: es-no-event

    // hysteresis bounds 
    if (TrackWireInput > TW_UPPER_BOUND) {
#ifdef DEBUG_PRINTS
        printf("TrackWire found.\r\n");
#endif
        recording = FOUND_TRACK_WIRE;
    } else if (TrackWireInput < TW_LOWER_BOUND) {
#ifdef DEBUG_PRINTS
        printf("TrackWire lost.\r\n"); 
#endif
        recording = 0; //ES_NO_EVENT
    }
    
    
    // This one does not consider the prev values 
    // pick the one you want by changing the define value in the beginning
    // This will post continuously. Only good for updating distance in real time
#ifndef TAKE_PREV    
    thisEvent.EventType = recording; //either FOUND or NO EVENT
    // alternatively: (if LOST event is needed)
    //thisEvent.EventType = recording? FOUND_TRACK_WIRE:LOST_TRACK_WIRE;//either FOUND or LOST
    thisEvent.EventParam = TrackWireInput;
    PostTopLevel(thisEvent);
    return (TRUE);
#endif    
    
    // This one takes consideration of the prev values 
    currentEvent = recording;//either FOUND or NO EVENT
    // alternatively: (if LOST event is needed)
    //currentEvent = recording? FOUND_TRACK_WIRE:LOST_TRACK_WIRE;//either FOUND or LOST
    if (currentEvent != lastEvent) {
        thisEvent.EventType = currentEvent; 
        thisEvent.EventParam = TrackWireInput;
        PostTopLevel(thisEvent);
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

/**
 * @Function BeaconEventChecker(void)
 * @param void
 * @return TRUE or FALSE
 * @brief Compares the previous beacon values with the current ones. Returns 
 *          True and post event if there is change, False otherwise. 
 * @author Horace, 11/14 */
uint8_t BeaconEventChecker(void) {
    static ES_EventTyp_t lastEvent = ES_NO_EVENT; 
    ES_EventTyp_t currentEvent = lastEvent;
    ES_Event thisEvent;
    uint8_t returnVal = (FALSE);
    uint8_t BeaconInput = Robot_ReadBeaconSensor(); 

    // hysteresis bounds - we don't need it anymore HZ 11/19
    if (BeaconInput == BEACON_DETECTED) {
#ifdef DEBUG_PRINTS
        printf("Beacon detected.\r\n");
#endif
        currentEvent = FOUND_BEACON;
    } else if (BeaconInput == BEACON_NOT_DETECTED) {
#ifdef DEBUG_PRINTS
        printf("Beacon lost.\r\n"); 
#endif
        currentEvent = 0; //ES_NO_EVENT
    }
    if (currentEvent != lastEvent) {
        thisEvent.EventType = currentEvent; 
        thisEvent.EventParam = BeaconInput;
        PostTopLevel(thisEvent);
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

/**
 * @Function BeaconEventChecker(void)
 * @param void
 * @return TRUE or FALSE
 * @brief Compares the previous beacon values with the current ones. Returns 
 *          True and post event if there is change, False otherwise. 
 * @author Horace, 11/14 */
uint8_t PingEventChecker(void) {
    static ES_EventTyp_t lastEvent = ES_NO_EVENT; 
    static uint8_t past_state = 0;
    static uint8_t curr_state = 0;
    static uint8_t flag = 0;//this is not necessary but secures the output
    static uint32_t start_time = 0;
    static uint16_t elapse_time = 0;
    //static uint16_t counter = 0;
    ES_EventTyp_t currentEvent = lastEvent;
    ES_Event thisEvent;
    uint8_t returnVal = (FALSE);
    uint8_t PingInput = Robot_ReadPingSensor(); 

    curr_state = PingInput;
    if (curr_state > past_state) {
        start_time = TIMERS_GetTime();
        currentEvent = ES_NO_EVENT;
        flag = 1;
    } else if (curr_state < past_state && flag) {
        elapse_time = (TIMERS_GetTime() - start_time);
        currentEvent = FOUND_PING;
        flag = 0;
        
    }
    //if (flag) counter++;//this can be unstable but is very fast - backup plan
    past_state = curr_state;
#ifndef TEST_HARNESSES
    if (currentEvent == FOUND_PING && elapse_time < PING_MAX) {
#else
    if (currentEvent == FOUND_PING) {
        printf("%d\r\n", elapse_time);
#endif
        //printf("%d\r\n", elapse_time);
        thisEvent.EventType = currentEvent; 
        thisEvent.EventParam = elapse_time;
        PostTopLevel(thisEvent);
        currentEvent = ES_NO_EVENT;
        lastEvent = currentEvent;
        returnVal = TRUE;
        //counter = 0;
    

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
    Robot_Init();
    /* user initialization code goes here */
    TIMERS_Init();
    ES_Timer_Init();
    IO_PortsSetPortInputs(PORTW, PIN3);
    //PWM_Init();
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