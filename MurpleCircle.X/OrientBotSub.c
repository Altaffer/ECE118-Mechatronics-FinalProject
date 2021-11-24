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
#include "OrientBotSub.h"
#include "robot.h"
#include "timers.h"

#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
//States have not been renamed - HZ 11/12

typedef enum {
    InitPSubState,
    NoSubService,
    Spin,
    Spiral,
    Adjust,
    FindCorner
} SubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "NoSubService",
    "Spin",
    "Spiral",
    "Adjust",
    "FindCorner"
};



/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/

uint8_t goForward(void);

uint8_t spin(void);

uint8_t spiral(void);

uint8_t stop(void);

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
uint8_t InitOrientBot(void) {
    ES_Event returnEvent;
    CurrentState = InitPSubState;
    returnEvent = RunOrientBot(INIT_EVENT);
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
ES_Event RunOrientBot(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    SubHSMState_t nextState;
    static int counter = 1;

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
            if (0) {// some trigger event to indicate 
                ;
            }

        case Spin: // 360 deg pivot turn to the left looking for BT
            if (ThisEvent.EventType == ES_ENTRY) {
                // Setting a time for a 360 spin (needs to be calibrated) 
                ES_Timer_InitTimer(SpinTimer, TIMER_360);
                spin();
                // if BT is detected go to Adjust (NEEDS TO BE FINISHED)
            }

            if (ThisEvent.EventType == ES_TIMEOUT) {
                // Transition to Spiral if BT is not detected
                if (ThisEvent.EventParam == SpinTimer) {
                    nextState = Spiral;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
            }

            if (ThisEvent.EventType == ES_EXIT) {
                // Stop the Robot before transition
                stop();
            }
            break;

        case Spiral: // indefinite gradual turn spiraling to the left
            if (ThisEvent.EventType == ES_ENTRY) {
                // Setting a time for an indefinite 360 spiral spin (needs to be calibrated) 
                spiral();
                // if BT is detected go to Adjust (NEEDS TO BE FINISHED)
            }

            if (ThisEvent.EventType == ES_EXIT) {
                // Stop the Robot before transition
                stop();
            }
            break;

        case Adjust: // Make the bot parallel with the BT once it is located (NOT FINISHED))
            if (ThisEvent.EventType == ES_ENTRY) {
                // If the left BT sensor is detected
                // Turn gradually to the left until mid sensors are detected
                spiral();
                // When mid sensors are detected transition to Find Corner
                // If the right BT sensor is detected
                // Turn gradually to right until mid sensors are detected
                Robot_LeftMtrSpeed(RGRAD_L);
                Robot_RightMtrSpeed(RGRAD_R);
            }

            if (ThisEvent.EventType == ES_EXIT) {
                // Stop the Robot before transition
                stop();
            }

        case FindCorner: // follow BT until the front and left sensor detects BT
            if (ThisEvent.EventType == ES_ENTRY){
                    // Go Straight
                    goForward();
                        // if left BT sensor is detected but not center, grad turn left
                        // if right bT sensor is detected but not center, grad turn right
                    // if left BT Sensor and mid sensors are detected Corner is found
                }
            if (ThisEvent.EventType == ES_EXIT) {
                // Stop the Robot before transition
                stop();

        default: // all unhandled events fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunOrientBot(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunOrientBot(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}
}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

uint8_t goForward(void) {
    //something here to make the bot go forward at full speed
    Robot_LeftMtrSpeed(FWD_speed);
    Robot_RightMtrSpeed(FWD_speed);

    return 0; //this could be used to indicated true or false. Not necessary tho. 
}

uint8_t spin(void) {
    //turn bot
    Robot_LeftMtrSpeed(LPIVOT_L);
    Robot_RightMtrSpeed(LPIVOT_R);
    return 0;
}

uint8_t spiral(void) {
    //turn bot
    Robot_LeftMtrSpeed(LGRAD_L);
    Robot_RightMtrSpeed(LGRAD_R);
    return 0;
}

uint8_t stop(void) { //one concern - if the gearhead is too powerful we may need to slow down first
    //stop the bot
    Robot_LeftMtrSpeed(STOP_speed);
    Robot_RightMtrSpeed(STOP_speed);


    return 0;
}