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
#include "robot.h"
#include "FindNewCornerSub.h"


#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
//States have not been renamed - HZ 11/12

typedef enum {
    InitPSubState,
    NoSubService,
    Find1,
    Turn,
    Find2
} SubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "NoSubService",
    "Find1",
    "Turn",
    "Find2"
};



/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/

//uint8_t goForward(void);
//
//uint8_t turn(void);
//
//uint8_t stop(void);

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
uint8_t InitFindNewCorner(void) {
    ES_Event returnEvent;
    CurrentState = InitPSubState;
    returnEvent = RunFindNewCorner(INIT_EVENT);
    StartFindNewCorner = 0;
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
ES_Event RunFindNewCorner(ES_Event ThisEvent) {
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
            if (StartFindNewCorner) {//when starting
                nextState = Find1;
                makeTransition = TRUE;
                StartFindNewCorner = 0;
            }
            break;
        case Find1: // Finds the first corner in the rotation
            if (ThisEvent.EventType == ES_ENTRY) {
                // Go Forward
                goForward();
            }
            // If left and middle BT sensors detected 
            if (Robot_ReadTapeSensors() == (0b0001 + 0b0010 + 0b1000)) {
                nextState = Turn;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            if (ThisEvent.EventType == ES_EXIT) {
                // Stop the Robot
                stop();
            }
            break;

        case Turn: // Turn 90 deg 
            if (ThisEvent.EventType == ES_ENTRY) {
                // Spins 90 until timer ends
                ES_Timer_InitTimer(SpinTimer, TIMER_90);
                turnBot(LPIVOT_L, LPIVOT_R);
            }

            if (ThisEvent.EventType == ES_TIMEOUT) {
                // timer end transition to find2
                if (ThisEvent.EventParam == SpinTimer) {
                    nextState = Find2;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
            }

            if (ThisEvent.EventType == ES_EXIT) {
                // stops the robot before exit
                stop();
            }

            break;

        case Find2: // Finds the second corner in the rotation
            if (ThisEvent.EventType == ES_ENTRY) {
                // Go Forward
                goForward();

            }
            if (Robot_ReadTapeSensors() == (0b0001 + 0b0010 + 0b1000)) {
                nextState = Turn;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            if (ThisEvent.EventType == ES_EXIT) {
                // Stop the Robot
                stop();
                ThisEvent.EventType = FOUND_NEW_CORNER;
                ThisEvent.EventParam = 1;
                PostTopLevel(ThisEvent);
            }
            break;

        default: // all unhandled events fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunFindNewCorner(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunFindNewCorner(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
