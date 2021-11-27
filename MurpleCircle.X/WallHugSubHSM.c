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
#include "WallHugSubHSM.h"
#include "robot.h"


#include <stdio.h>
#include <stdlib.h>



/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
//States have not been renamed - HZ 11/12

typedef enum {
    InitPSubState,
    //FirstState, which was the template state
    Driving,
    Hiding,
    Reversing,
    Driving2
} SubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"Driving",
    "Hiding",
    "Reversing",
    "Driving2"
};






/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
uint8_t robot_reverse(void);

uint8_t robot_forward(void);

uint8_t robot_stop(void);

uint8_t robot_forward_2(void);

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
uint8_t InitWallHug(void) {
    ES_Event returnEvent;
    CurrentState = InitPSubState;
    returnEvent = RunWallHug(INIT_EVENT);
    StartWallHug = 0;
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
ES_Event RunWallHug(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    SubHSMState_t nextState;


    ES_Tattle(); // trace call stack


    switch (CurrentState) {
    case InitPSubState: // If current state is initial Psedudo State
        if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
        {
            // this is where you would put any actions associated with the
            // transition from the initial pseudo-state into the actual
            // initial state

            // now put the machine into the actual initial state
            nextState = Driving;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
        }
        break;

    case Driving: // in the first state, replace this with appropriate state
        if (ThisEvent.EventType == ES_ENTRY) {
                robot_forward();
                ES_Timer_InitTimer(MotionTimer, WALL_HUG_FORWARD_TIME);
            }
        switch (ThisEvent.EventType) {
            case BUMP_EVENT:
                nextState = Reversing;
                robot_reverse();//pivot turn
                ES_Timer_InitTimer(MotionTimer, WALL_HUG_REVERSE_TIME);
                ThisEvent.EventType = ES_NO_EVENT;
                makeTransition = TRUE;
                break;
            case MOTION_TIMER_EXP:
                nextState = Driving2;
                robot_forward_2();//at a larger angle
                ES_Timer_InitTimer(MotionTimer, WALL_HUG_FORWARD_TIME*4);
                ThisEvent.EventType = ES_NO_EVENT;
                makeTransition = TRUE;
                break;
            default:
                break;
        }
        break;
        
    case Driving2: // in the first state, replace this with appropriate state
        switch (ThisEvent.EventType) {
            case BUMP_EVENT:
                nextState = Reversing;
                robot_reverse();
                ES_Timer_InitTimer(MotionTimer, WALL_HUG_FORWARD_TIME);
                ThisEvent.EventType = ES_NO_EVENT;
                makeTransition = TRUE;
                break;
            case MOTION_TIMER_EXP:
                nextState = Driving;
                robot_forward();//straight
                ThisEvent.EventType = ES_NO_EVENT;
                makeTransition = TRUE;
                break;
            default:
                break;
        }
        break;
        
        

        
    case Reversing:
        switch (ThisEvent.EventType) {
            case MOTION_TIMER_EXP:
                nextState = Driving;
                ES_Timer_InitTimer(MotionTimer, WALL_HUG_FORWARD_TIME);
                robot_forward();//straight
                printf("%d\r\n",WALL_HUG_FORWARD_TIME);
                ThisEvent.EventType = ES_NO_EVENT;
                makeTransition = TRUE;
                break;
            default:
                break;
        }
        break;

    default: // all unhandled states fall into here
        break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunWallHug(EXIT_EVENT);
        CurrentState = nextState;
        RunWallHug(ENTRY_EVENT);
    }
    ES_Tail(); // trace call stack end
    return ThisEvent;

}



/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/


uint8_t robot_reverse(void){
    printf("FL hit, reverse a bit\r\n");
    Robot_LeftMtrSpeed(-100);
    Robot_RightMtrSpeed(-5);
    return 0;
}

uint8_t robot_forward(void){
    printf("Robot going forward\r\n");
    Robot_LeftMtrSpeed(80);
    Robot_RightMtrSpeed(80);
    return 0;
}

uint8_t robot_stop(void){
    printf("Robot stopped\r\n");
    Robot_LeftMtrSpeed(0);
    Robot_RightMtrSpeed(0);
    return 0;
}

uint8_t robot_forward_2(void){
    printf("forward2/r/n");
    Robot_LeftMtrSpeed(100);
    Robot_RightMtrSpeed(30);
}

