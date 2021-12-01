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
    MoveForward,
    TankTurn,
    AlignRight,
    AlignLeft,
    CornerTurn,
    Sweep,
} SubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "NoSubService",
    "MoveForward",
    "TankTurn",
    "AlignRight",
    "AlignLeft",
    "CornerTurn",
    "Sweep",
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
#define TIMER_1_TICKS 250
#define JIG_TIMER_TICKS 5000
#define F_CENTER_TAPE 0b000001
#define F_LEFT_TAPE 0b000010
#define F_RIGHT_TAPE 0b000100
#define B_CENTER_TAPE 0b001000
uint8_t StartFindNewCorner;
uint8_t TankTurnFlag;
uint8_t TwoCornersCounter;

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
    TankTurnFlag = 0;
    TwoCornersCounter = 0;
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
    if (StartFindNewCorner) {
        CurrentState = 1;
    }

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
                nextState = MoveForward;
                makeTransition = TRUE;
                StartFindNewCorner = 0;
                TwoCornersCounter = 0;
            }
            break;
        case TankTurn:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    turnBot(LTANK_L_SLOW, LTANK_R_SLOW);

                    //ES_Timer_InitTimer(MotionTimer, TIMER_90);//time based, not used
                    break;
                case BOT_BT_CHANGED:
                    if ((ThisEvent.EventParam & F_CENTER_TAPE)) {
                        nextState = MoveForward;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        goForward();
                    }
                    break;
                case ES_EXIT:
                    ES_Timer_StopTimer(MotionTimer);
                    stop();
                    break;
            }
            break;
        case MoveForward:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    goForward();
                    break;
                case MOTION_TIMER_EXP:
                    if (TankTurnFlag == 0) {
                        nextState = TankTurn;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        TankTurnFlag = 1;
                    }
                    break;
                case BOT_BT_CHANGED:
                    if ((TankTurnFlag == 0) &&
                            (ThisEvent.EventParam & F_CENTER_TAPE)) {
                        ES_Timer_InitTimer(MotionTimer, BOT_MIDDLE_TIME);
                        break;
                    } else if ((TankTurnFlag == 1) && ThisEvent.EventParam & F_CENTER_TAPE) {
                        goForward();
                        break;
                    } else if ((TankTurnFlag == 1)) {
                        switch (ThisEvent.EventParam) {
                            case (F_RIGHT_TAPE | B_CENTER_TAPE):
                            case (F_RIGHT_TAPE):
                                nextState = AlignRight;
                                makeTransition = TRUE;
                                ThisEvent.EventType = ES_NO_EVENT;
                                break;
                            case (F_LEFT_TAPE | B_CENTER_TAPE):
                            case (F_LEFT_TAPE):
                                nextState = AlignLeft;
                                makeTransition = TRUE;
                                ThisEvent.EventType = ES_NO_EVENT;
                                break;
                            default:
                                if (ThisEvent.EventType & F_LEFT_TAPE && ThisEvent.EventType & !F_CENTER_TAPE) {
                                    nextState = AlignLeft;
                                    makeTransition = TRUE;
                                    ThisEvent.EventType = ES_NO_EVENT;
                                }
                                if (ThisEvent.EventType & F_RIGHT_TAPE && ThisEvent.EventType & !F_CENTER_TAPE) {
                                    nextState = AlignRight;
                                    makeTransition = TRUE;
                                    ThisEvent.EventType = ES_NO_EVENT;
                                }
                                break;
                        }
                    }

                    break;
                case ES_EXIT:
                    ES_Timer_StopTimer(MotionTimer);
                    stop();
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case AlignLeft:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    turnBot(LGRAD_L, LGRAD_R);
                    ES_Timer_InitTimer(MotionTimer, ABRUPT_TURN_TIME);
                    break;
                case MOTION_TIMER_EXP:
                    turnBot(-10, LPIVOT_R);
                    ES_Timer_InitTimer(TurnTimer, FIND_NEW_CORNER_EXP_TIME);
                    break;
                case TURN_TIMER_EXP:
                    if (TwoCornersCounter++ > 0){
                        TwoCornersCounter = 0;
                        ThisEvent.EventType = FOUND_NEW_CORNER;
                    } 
                    break;
                case BOT_BT_CHANGED:
                    if (ThisEvent.EventParam & (F_CENTER_TAPE)) {
                        nextState = MoveForward;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        ES_Timer_StopTimer(MotionTimer);
                        stop();
                    }
                    break;
                case ES_EXIT:
                    ES_Timer_StopTimer(TurnTimer);
                    ES_Timer_StopTimer(MotionTimer);
                    stop();
                    break;
            }
            break;
        case AlignRight:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    turnBot(RGRAD_L, RGRAD_R);
                    ES_Timer_InitTimer(MotionTimer, ALIGN_RIGHT_TIME);
                    // if you cannot find the tape in a few seconds
                    // you are in the middle
                    break;
                case BOT_BT_CHANGED:
                    if (ThisEvent.EventParam & (F_CENTER_TAPE)) {
                        nextState = MoveForward;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case MOTION_TIMER_EXP:
                    goForward(); //go away from the center
                    nextState = MoveForward;
                    TankTurnFlag = 0;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;

                    break;
                case ES_EXIT:
                    ES_Timer_StopTimer(MotionTimer);
                    stop();
                    break;
            }
            break;
            /* In the CornerTurn:
             * 1. Go forward a bit until the center of the bot is at the corner
             * 2. Tank turn ccw 90 degrees
             * 3. Go back to go forward
             */
            //        case Find1: // Finds the first corner in the rotation
            //            if (ThisEvent.EventType == ES_ENTRY) {
            //                // Go Forward
            //                goForward();
            //            }
            //            // If left and middle BT sensors detected 
            //            if (Robot_ReadTapeSensors() == (0b0001 + 0b0010 + 0b1000)) {
            //                nextState = Turn;
            //                makeTransition = TRUE;
            //                ThisEvent.EventType = ES_NO_EVENT;
            //            }
            //            if (ThisEvent.EventType == ES_EXIT) {
            //                // Stop the Robot
            //                stop();
            //            }
            //            break;
            //
            //        case Turn: // Turn 90 deg 
            //            if (ThisEvent.EventType == ES_ENTRY) {
            //                // Spins 90 until timer ends
            //                ES_Timer_InitTimer(MotionTimer, TIMER_90);
            //                turnBot(LPIVOT_L, LPIVOT_R);
            //            }
            //
            //            if (ThisEvent.EventType == ES_TIMEOUT) {
            //                // timer end transition to find2
            //                if (ThisEvent.EventParam == MotionTimer) {
            //                    nextState = Find2;
            //                    makeTransition = TRUE;
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                }
            //            }
            //
            //            if (ThisEvent.EventType == ES_EXIT) {
            //                // stops the robot before exit
            //                stop();
            //            }
            //
            //            break;
            //
            //        case Find2: // Finds the second corner in the rotation
            //            if (ThisEvent.EventType == ES_ENTRY) {
            //                // Go Forward
            //                goForward();
            //
            //            }
            //            if (Robot_ReadTapeSensors() == (0b0001 + 0b0010 + 0b1000)) {
            //                nextState = Turn;
            //                makeTransition = TRUE;
            //                ThisEvent.EventType = ES_NO_EVENT;
            //            }
            //            if (ThisEvent.EventType == ES_EXIT) {
            //                // Stop the Robot
            //                stop();
            //                ThisEvent.EventType = FOUND_NEW_CORNER;
            //                ThisEvent.EventParam = 1;
            //                PostTopLevel(ThisEvent);
            //            }
            //            break;

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
