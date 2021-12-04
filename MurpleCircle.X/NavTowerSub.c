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
#include "robot.h"
//#include "ParkSub.h"
#include "NavTower_FindHole.h"
#include "WallHugSubHSM.h"
#include "BumperService.h"
#include "TapeService.h"
#include "RC_Servo.h"


#include <stdio.h>
#include <stdlib.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
//States have not been renamed - HZ 11/12

typedef enum {
    InitPSubState,
    WallHug,
    Park,
    FindHole,
    ReleaseBall,
    Leave,
    NoSubService
} SubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "WallHug",
    "Park",
    "FindHole",
    "ReleaseBall",
    "Leave",
    "NoSubService"
};

#define TURN_SPEED 50
#define FRONT_TAPE 0x0008 // 1000 - Change this to the right one
#define SERVO_BUMPER_ON 0b100


/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static SubHSMState_t CurrentState = InitPSubState; // initial state
uint8_t StartNavTower;
extern uint8_t StartWallHug;
//extern uint8_t StartPark;
//extern uint8_t IsParallel;
extern uint8_t StartFindHole;
uint8_t enough_bump;

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
uint8_t InitNavTower(void) {
    ES_Event returnEvent;
    //InitPark();
    InitFindHole();
    InitWallHug();
    CurrentState = InitPSubState;
    returnEvent = RunNavTower(INIT_EVENT);
    StartNavTower = 0;
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
ES_Event RunNavTower(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    SubHSMState_t nextState;


    ES_Tattle(); // trace call stack
    if (StartNavTower) {
        CurrentState = NoSubService;
    }//resets the sub

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
            if (StartNavTower) {//when there is actually an event
                nextState = WallHug;
                makeTransition = TRUE;
                StartNavTower = 0;
                ThisEvent.EventType = ES_NO_EVENT;
                enough_bump = 0;
            }
            break;
        case WallHug:
            if (ThisEvent.EventType == ES_ENTRY) {
                //state entry
                StartWallHug = 1;
                ES_Timer_StopTimer(MotionTimer);
                ES_Timer_StopTimer(TurnTimer);
            }
            ThisEvent = RunWallHug(ThisEvent);
            if (ThisEvent.EventType == FOUND_TRACK_WIRE) {
                nextState = FindHole;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            } else if (ThisEvent.EventType == BOT_BT_CHANGED) {
                nextState = NoSubService;
                makeTransition = TRUE;
                ThisEvent.EventType = FOUND_TAPE;
            } else if (ThisEvent.EventType == FOUND_BOX) {
                nextState = Leave;
                makeTransition = TRUE;
                ES_Timer_StopTimer(TurnTimer);
                ThisEvent.EventType = ES_NO_EVENT;
            }
            if (ThisEvent.EventType == ES_EXIT) {
                ES_Timer_StopTimer(MotionTimer);
                ES_Timer_StopTimer(TurnTimer);
                //state exit
                ;
            }
            break;
            //        case Park:
            //            if (ThisEvent.EventType == ES_ENTRY) {
            //                //state entry
            //                StartPark;
            //            }
            //            ThisEvent = RunPark(ThisEvent);
            //            if (ThisEvent.EventType == IS_PARALLEL) {
            //                nextState = FindHole;
            //                makeTransition = TRUE;
            //                ThisEvent.EventType = ES_NO_EVENT;
            //            }
            //            if (ThisEvent.EventType == ES_EXIT) {
            //                //state exit
            //                ;
            //            }
            //            break;
        case FindHole:
            if (ThisEvent.EventType == ES_ENTRY) {
                //state entry
                //stop();
                StartFindHole = 1;
                ES_Timer_StopTimer(MotionTimer);
                ES_Timer_InitTimer(AnotherTimer,7000);
            }
            ThisEvent = RunFindHole(ThisEvent);
            if (ThisEvent.EventType == FOUND_HOLE) {
                //from the ssm, this is for sure both tape on
                ES_Timer_InitTimer(MotionTimer, 250);
                turnBot(-40, -40);
                ThisEvent.EventType = ES_NO_EVENT;
            }
            if (ThisEvent.EventType == MOTION_TIMER_EXP) {
                //from the ssm, this is for sure both tape on
                nextState = ReleaseBall;
                stop();
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            if (ThisEvent.EventType == ANOTHER_TIMER_EXP) {
                //from the ssm, this is for sure both tape on
                nextState = Leave;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            if (ThisEvent.EventType == ES_EXIT) {
                //state exit
                stop();
                ES_Timer_StopTimer(MotionTimer);
                ES_Timer_StopTimer(TurnTimer);
            }
            break;
        case ReleaseBall:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    //state entry
                    //start the servo, but what value?
                    Robot_StartServo(1525);
                    break;


                case BUMPER_SERVO:
                    //turn off servo, but what value?

                    Robot_StopServo();
                    nextState = Leave;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;

                    break;
                    //
                case ES_EXIT:
                    //state exit
                    break;
            }
            break;
        case Leave:
            if (ThisEvent.EventType == ES_ENTRY) {
                //state entry
                goForward();
                ES_Timer_StopTimer(MotionTimer);
                ES_Timer_InitTimer(MotionTimer, NAV_TOWER_LEAVE_TIME);
            }
            switch (ThisEvent.EventType) {
                case BUMP_EVENT:
                    ThisEvent.EventType = ES_NO_EVENT;
                    //ES_Timer_InitTimer(MotionTimer, NAV_TOWER_LEAVE_TIME);
                    //turnBot(-80, -80);
                    break;
                case MOTION_TIMER_EXP:
                    nextState = NoSubService;
                    makeTransition = TRUE;
                    ThisEvent.EventType = TOWER_DONE;
                    break;
                default:
                    break;
            }
            //do we really need this state?
            if (ThisEvent.EventType == ES_EXIT) {
                //state exit
                ;
            }
            break;

        default: // all unhandled events fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunNavTower(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunNavTower(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}



/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/


