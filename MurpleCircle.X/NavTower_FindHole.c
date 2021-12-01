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
#include "NavTowerSub.h"
#include "NavTower_FindHole.h"
#include "robot.h"
#include "ParkSub.h"
#include "TestTopLevel.h"


#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
//States have not been renamed - HZ 11/12

typedef enum {
    InitPSubState,
    Reverse,
    Turn,
    Forward,
    Backwards,
    NoSubService
} SubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "Reverse",
    "Turn",
    "Forward",
    "Backwards",
    "NoSubService"
};

#define FIRST_TAPE 1 // 01
#define SECOND_TAPE 2 // 10
#define BOTH_TAPE 3 // 11
#define BACK_BUMP 8



/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static SubHSMState_t CurrentState = InitPSubState; // initial state
uint8_t StartFindHole;

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
uint8_t InitFindHole(void) {
    ES_Event returnEvent;
    InitPark();
    CurrentState = InitPSubState;
    returnEvent = RunFindHole(INIT_EVENT);
    StartFindHole = 0;
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
ES_Event RunFindHole(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    SubHSMState_t nextState;


    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                nextState = NoSubService;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;
        case NoSubService: /* After initialzing or executing, it sits here for the next 
                              time it gets called. */
            if (StartFindHole) {//when there is actually an event
                nextState = Turn;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                StartFindHole = 0;
            }
            break;
//        case Reverse:
//            if (ThisEvent.EventType == ES_ENTRY) {
//                //state entry
//                //reverse a bit
//                Robot_LeftMtrSpeed(FIND_HOLE_REVERSE_L);
//                Robot_RightMtrSpeed(FIND_HOLE_REVERSE_R);
//                ES_Timer_InitTimer(MotionTimer, FINDHOLE_REV_TIME);
//            }
//            if (ThisEvent.EventType == MOTION_TIMER_EXP) {
//                nextState = Turn;
//                makeTransition = TRUE;
//                ThisEvent.EventType = ES_NO_EVENT;
//            }
//            if (ThisEvent.EventType == ES_EXIT) {
//                //state exit
//                ES_Timer_StopTimer(MotionTimer);
//                Robot_LeftMtrSpeed(0);
//                Robot_RightMtrSpeed(0);
//            }
//            break;
        case Turn:
            if (ThisEvent.EventType == ES_ENTRY) {
                //state entry
                Robot_LeftMtrSpeed(FIND_HOLE_REVERSE_L);
                Robot_RightMtrSpeed(FIND_HOLE_REVERSE_R);
//                ES_Timer_InitTimer(MotionTimer, FINDHOLE_FORWARD_TIME);
            }
            if (ThisEvent.EventType == BUMP_EVENT &&
                    ThisEvent.EventParam == BACK_BUMP) {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            if (ThisEvent.EventType == ES_EXIT) {
                //state exit
//                ES_Timer_StopTimer(MotionTimer);
                Robot_LeftMtrSpeed(0);
                Robot_RightMtrSpeed(0);
            }
            break;
        case Forward:
            if (ThisEvent.EventType == ES_ENTRY) {
                //state entry
                Robot_LeftMtrSpeed(60);
                Robot_RightMtrSpeed(60);
                ES_Timer_InitTimer(MotionTimer, FINDHOLE_EXPIRE_TIME);
            }
            if (ThisEvent.EventType == MOTION_TIMER_EXP) {
                nextState = Backwards;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            } else if (ThisEvent.EventType == SHOOTER_BT_CHANGED) {
                switch (ThisEvent.EventParam){
                    case FIRST_TAPE: //only found one - needs forward more
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    case SECOND_TAPE: //only found the other one - went too far - need backwards
                        nextState = Backwards;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    case BOTH_TAPE:
                        nextState = NoSubService;
                        makeTransition = TRUE;//This makes sure that it sits at the InitState
                        ThisEvent.EventType = FOUND_HOLE;
                        Robot_LeftMtrSpeed(0);
                        Robot_RightMtrSpeed(0);
                        break;
                    default:
                        break;
                }
            }
            if (ThisEvent.EventType == ES_EXIT) {
                //state exit
                ES_Timer_StopTimer(MotionTimer);
                Robot_LeftMtrSpeed(0);
                Robot_RightMtrSpeed(0);
            }
            break;
        case Backwards:
            if (ThisEvent.EventType == ES_ENTRY) {
                //state entry
                Robot_LeftMtrSpeed(-60);
                Robot_RightMtrSpeed(-60);
                ES_Timer_InitTimer(MotionTimer, FINDHOLE_FORWARD_TIME);
            }
            if (ThisEvent.EventType == MOTION_TIMER_EXP) {
                nextState = Forward;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            } else if (ThisEvent.EventType == SHOOTER_BT_CHANGED) {
                switch (ThisEvent.EventParam){
                    case SECOND_TAPE: //only found one - needs forward more
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    case FIRST_TAPE: //only found the other one - went too far - need backwards
                        nextState = Forward;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    case BOTH_TAPE:
                        nextState = NoSubService;
                        makeTransition = TRUE;//This makes sure that it sits at the InitState
                        ThisEvent.EventType = FOUND_HOLE;
                        Robot_LeftMtrSpeed(0);
                        Robot_RightMtrSpeed(0);
                        break;
                    default:
                        break;
                }
            }
            if (ThisEvent.EventType == ES_EXIT) {
                //state exit
                ES_Timer_StopTimer(MotionTimer);
                Robot_LeftMtrSpeed(0);
                Robot_RightMtrSpeed(0);
            }
            break;
        
        default: // all unhandled events fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunFindHole(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunFindHole(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}



/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/


