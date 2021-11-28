/*
 * File: AlignSubHSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Template file to set up a Heirarchical State Machine to work with the Events and
 * Services Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the names
 * will have to be changed to match your code.
 *
 * There is for a substate machine. Make sure it has a unique name
 *
 * This is provided as an example and a good place to start.
 *
 * History
 * When           Who     What/Why
 * -------------- ---     --------
 * 09/13/13 15:17 ghe      added tattletail functionality and recursive calls
 * 01/15/12 11:12 jec      revisions for Gen2 framework
 * 11/07/11 11:26 jec      made the queue static
 * 10/30/11 17:59 jec      fixed references to CurrentEvent in RunTemplateSM()
 * 10/23/11 18:20 jec      began conversion from SMTemplate.c (02/20/07 rev)
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"
#include "AlignSubHSM.h"
#include "robot.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
typedef enum {
    InitPSubState,
    MoveForward,
    TankTurn,
    AlignRight,
    AlignLeft,
    CornerTurn,
} AlignSubHSMState_t;

static const char *StateNames[] = {
    "InitPSubState",
    "MoveForward",
    "TankTurn",
    "AlignRight",
    "AlignLeft",
    "CornerTurn",
};

#define TIMER_1_TICKS 250
#define JIG_TIMER_TICKS 5000
#define F_CENTER_TAPE 0b000001
#define F_LEFT_TAPE 0b000010
#define F_RIGHT_TAPE 0b000100
#define B_CENTER_TAPE 0b001000
//#define NO_BUMPER_PRESSED 0b0000
//#define F_LEFT_MASK 0b0001
//#define F_RIGHT_MASK 0b0010
//#define B_LEFT_MASK 0b0100
//#define B_RIGHT_MASK 0b1000
//#define BOTH_B_MASK 0b1100
//#define BOTH_F_MASK 0b0011



/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static AlignSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;
static char LeftMotorSpeed;
static char RightMotorSpeed;
static int StartFlag;
static int TankTurnFlag;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitAlignSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitAlignSubHSM(void) {
    ES_Event returnEvent;
    CurrentState = InitPSubState;
    returnEvent = RunAlignSubHSM(INIT_EVENT);
    StartFlag = 0;
    TankTurnFlag = 0;
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunAlignSubHSM(ES_Event ThisEvent)
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
ES_Event RunAlignSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    AlignSubHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state

                if (StartFlag == 0) {
                    nextState = MoveForward;
                } else if (StartFlag == 1) {
                    //                    nextState = ;
                }
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;
        case TankTurn:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    turnBot(LTANK_L_SLOW, LTANK_R_SLOW);
                    break;
                case BOT_BT_CHANGED:
                    if ((ThisEvent.EventParam & F_CENTER_TAPE)) {
                        nextState = MoveForward;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case ES_EXIT:
                    stop();
                    break;
            }
            break;
            //        case Spin:
            //            switch (ThisEvent.EventType) {
            //                case ES_ENTRY:
            //                    turnBot(LPIVOT_L, LPIVOT_R);
            //                    break;
            //                case BOT_BT_CHANGED:
            //                    if (ThisEvent.EventParam & F_LEFT_TAPE) {
            //                        LF_1st = 1;
            //                    } else if ((ThisEvent.EventParam & F_RIGHT_TAPE) && LF_1st) {
            //                        LF_1st = 0;
            //                    } else if (ThisEvent.EventParam & F_RIGHT_TAPE) {
            //                        nextState = SlightLeft;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    } else if (ThisEvent.EventParam == F_CENTER_TAPE
            //                            & B_CENTER_TAPE) {
            //                        nextState = MoveForward;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //                case ES_EXIT:
            //                    break;
            //                default:
            //                    break;
            //            }
            //            break;
            //        case SlightLeft: // in the first state, replace this with appropriate state
            //            switch (ThisEvent.EventType) {
            //                case ES_ENTRY:
            //                    turnBot(LGRAD_L, LGRAD_R);
            //                    break;
            //                case BOT_BT_CHANGED:
            //                    if (ThisEvent.EventParam == F_CENTER_TAPE | B_CENTER_TAPE) {
            //                        nextState = MoveForward;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //                case ES_EXIT:
            //                    stop();
            //                    break;
            //            }
            //            break;
        case MoveForward: // in the first state, replace this with correct names
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
                    } else {
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
                            case (F_CENTER_TAPE)://test only. delete this line
                            case (F_CENTER_TAPE | F_LEFT_TAPE | B_CENTER_TAPE):
                                nextState = CornerTurn;
                                makeTransition = TRUE;
                                ThisEvent.EventType = ES_NO_EVENT;
                                break;
                            default:
                                break;
                        }
                    }
                    break;
                case ES_EXIT:
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
                    break;
                case BOT_BT_CHANGED:
                    if (ThisEvent.EventParam == F_CENTER_TAPE | B_CENTER_TAPE) {
                        nextState = MoveForward;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case ES_EXIT:
                    stop();
                    break;
            }
            break;
        case AlignRight:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    turnBot(RGRAD_L, RGRAD_R);
                    break;
                case BOT_BT_CHANGED:
                    if (ThisEvent.EventParam == F_CENTER_TAPE | B_CENTER_TAPE) {
                        nextState = MoveForward;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case ES_EXIT:
                    stop();
                    break;
            }
            break;
        /* In the CornerTurn:
         * 1. Go forward a bit until the center of the bot is at the corner
         * 2. Tank turn ccw 90 degrees
         * 3. Go back to go forward
         */
        case CornerTurn:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    // step 1. forward a little
                    ES_Timer_InitTimer(MotionTimer, BOT_MIDDLE_TIME);
                    ES_Timer_StopTimer(TurnTimer); //just to be safe
                    goForward();
                    break;
                case MOTION_TIMER_EXP:
                    // step 2. tank turn 90 degrees
                    // Using a different timer to avoid conflicts
                    turnBot(LTANK_L_SLOW, LTANK_R_SLOW);//tank turn
                    ES_Timer_InitTimer(TurnTimer, TIMER_360);
                    break;
                case TURN_TIMER_EXP:
                    // step 3. go forward
                    nextState = MoveForward;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_EXIT:
                    break;
            }
            break;

        default: // all unhandled states fall into here
            break;

    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunAlignSubHSM(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunAlignSubHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/


