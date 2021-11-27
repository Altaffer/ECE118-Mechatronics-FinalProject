/******************************************************************************/
/* Sub State Machine - [NAME]
 * 
 * Descriptions to be added
 *  
 * UCSC ECE118 Final Project -  Fall 2021
 * Horace & Emma & Luca
 ******************************************************************************/
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "TopLevel.h"
#include "ScanForBeaconSub.h"
#include "robot.h"


#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
//States have not been renamed - HZ 11/12
typedef enum {
    InitPSubState,
    Turn,
    FindPing,
    Reverse,
    NoSubService
} SubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "Turn",
    "FindPing",
    "Reverse",
    "NoSubService"
};

#define TURN_SPEED 50
#define FRONT_TAPE 0x0008 // 1000 - Change this to the right one


/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
uint8_t CCW_Turn(void);
uint8_t CW_Turn(void);
uint8_t stop_bot(void);
/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static SubHSMState_t CurrentState = InitPSubState; // initial state

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitScanForBeacon(void)
{
    ES_Event returnEvent;
    CurrentState = InitPSubState;
    returnEvent = RunScanForBeacon(INIT_EVENT);
    StartScan = 0;
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunTemplateSubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the heirarchical state
 *        machine, as this is called any time a new event is passed to the event
 *        queue. This function will be called recursively to implement the correct
 *        order for a state transition to be: exit current state -> enter next state
 *        using the ES_EXIT and ES_ENTRY events.
 * @note Remember to rename to something appropriate.
 *       The lower level state machines are run first, to see if the event is dealt
 *       with there rather than at the current level. ES_EXIT and ES_ENTRY events are
 *       not consumed as these need to pass pack to the higher level state machine.
 * @author J. Edward Carryer, 2011.10.23 19:25
 * @author Gabriel H Elkaim, 2011.10.23 19:25 */
ES_Event RunScanForBeacon(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE; // use to flag transition
    SubHSMState_t nextState; 
    static uint8_t tower_counter = 0;//counts how many to go when reversing
    static uint16_t min_elapse_time = 999;//max possible is 704, which does 
                                            //not generate an event
    

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                nextState = NoSubService;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                CCW_Turn();
            }
            break;
        case NoSubService: /* After initialzing or executing, it sits here for the next 
                              time it gets called. */
            if (StartScan)// only respond to an actual event
            {
                nextState = Turn;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                StartScan = 0;
            }
            break;
        case Turn:
            if (ThisEvent.EventType == FOUND_BEACON) {
                nextState = FindPing;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            } else if (ThisEvent.EventType == BOT_BT_CHANGED && (ThisEvent.EventParam & FRONT_TAPE)) {
                nextState = Reverse;
                makeTransition = TRUE;
                CW_Turn();
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;
        case FindPing:
            if (ThisEvent.EventType == FOUND_PING) {
                nextState = Turn;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                if (min_elapse_time > ThisEvent.EventParam){
                    min_elapse_time = ThisEvent.EventParam;
                    tower_counter = 0;
                } else {
                    tower_counter++;
                }
            }
            break;
        case Reverse:
            if (ThisEvent.EventType == FOUND_BEACON) {
                if (tower_counter-- == 0) {
                    stop_bot();
                    nextState = InitPSubState;
                    makeTransition = FALSE;//This makes sure that it sits at the InitState
                    //ThisEvent.EventType = ES_NO_EVENT; //passing the event to super state
                } else {
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                nextState = FindPing;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;
        
        default: // all unhandled events fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunScanForBeacon(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunScanForBeacon(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}



/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
uint8_t CCW_Turn(void) {
    Robot_LeftMtrSpeed(-1*TURN_SPEED);
    Robot_RightMtrSpeed(TURN_SPEED);
    return 0;
}

uint8_t CW_Turn(void) {
    Robot_LeftMtrSpeed(TURN_SPEED);
    Robot_RightMtrSpeed(-1*TURN_SPEED);
    return 0;
}

uint8_t stop_bot(void) {
    Robot_LeftMtrSpeed(0);
    Robot_RightMtrSpeed(0);
    return 0;
}


