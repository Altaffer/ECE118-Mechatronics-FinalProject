/*
 * File: TemplateSubHSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel Elkaim and Soja-Marie Morgens
 *
 * Template file to set up a Heirarchical State Machine to work with the Events and
 * Services Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the names
 * will have to be changed to match your code.
 *
 * There is another template file for the SubHSM's that is slightly differet, and
 * should be used for all of the subordinate state machines (flat or heirarchical)
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

#include "TopLevel.h"
#include "stdio.h"
#include "stdlib.h"
#include "robot.h"


#include "OrientBotSub.h"
#include "ScanForBeaconSub.h"
#include "FindNewCornerSub.h"
#include "ToBeaconSub.h"
#include "NavTowerSub.h"
#include "NavFieldsub.h"//#include all sub state machines called
#include "AlignSubHSM.h"
/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
//Include any defines you need to do

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

typedef enum {
    InitPState,
    OrientBot,
    ScanForBeacon,
    FindNewCorner,
    ReAdjustBot,
    ToBeacon,
    NavTower,
    NavField,
            AlignCenter,
} TemplateHSMState_t;

static const char *StateNames[] = {
    "InitPState",
    "OrientBot",
    "ScanForBeacon",
    "FindNewCorner",
    "ReAdjustBot",
    "ToBeacon",
    "NavTower",
    "NavField",
    "AlignCenter",
};

/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine
   Example: char RunAway(uint_8 seconds);*/
/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */
#define F_CENTER_TAPE 0b000001
static TemplateHSMState_t CurrentState = InitPState; // <- change enum name to match ENUM
static uint8_t MyPriority;
extern uint8_t StartScan;
extern uint8_t StartWallHug;
extern uint8_t StartNavTower;
extern uint8_t StartAlign_boarder;
extern uint8_t StartAlign_center;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitTopLevel(uint8_t Priority) {
    MyPriority = Priority;
    // put us into the Initial PseudoState
    CurrentState = InitPState;
    // post the initial transition event
    if (ES_PostToService(MyPriority, INIT_EVENT) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostTemplateHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostTopLevel(ES_Event ThisEvent) {
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunTemplateHSM(ES_Event ThisEvent)
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
ES_Event RunTopLevel(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    TemplateHSMState_t nextState; // <- change type to correct enum
    static uint8_t Tower_Found = 0;

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPState: // If current state is initial Pseudo State
            if (ThisEvent.EventType == ES_INIT) // only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state
                // Initialize all sub-state machines
                //            InitTemplateSubHSM();
                // now put the machine into the actual initial state
                nextState = ScanForBeacon;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
                ;
            }
            break;

            // we may not need this state
//        case OrientBot: // Find the bot's initial position on the field by locating first corner
//        {
//            // Spins to the left to find Black Tape. Once tape is found follow the tap in a CCW orientation to find a corner
//            // Enter Orientation sub state machine
//            ThisEvent = RunOrientBot(ThisEvent);
//            switch (ThisEvent.EventType) {
//                case BOT_ORIENTED:
//                    // make transition to scan for beacon state
//                    nextState = ScanForBeacon;
//                    makeTransition = TRUE;
//                    ThisEvent.EventType = ES_NO_EVENT;
//                    break;
//                case ES_NO_EVENT:
//                default:
//                    break;
//            }
//        }
//            break;

            //we can just start here, because we know we are at a corner
        case ScanForBeacon: //
        {
            // Completes two 180 deg sweeps to find the closest beacon
            // Enter scan for beacon sub state machine
            if (ThisEvent.EventType == ES_ENTRY) {
                StartScan = 1;
            }
            ThisEvent = RunScanForBeacon(ThisEvent);
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    //Entry state
                    break;
                case NO_SIGNAL:
                    // make transition to find a new corner
                    if (Tower_Found == 0) {
                        // case before tower is found to initially find a tower from a corner
                        nextState = FindNewCorner;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else if (Tower_Found > 0) {
                        // case before tower is found to initially find a tower from a corner
                        nextState = NavField;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case FOUND_BEACON:
                    // make transition to move toward the beacon
                    nextState = ToBeacon;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                case ES_NO_EVENT:
                default:
                    break;
            }
        }
            break;
        case FindNewCorner: // Locate the next corner going in a counter clock wise (CCW) orientation
        {
            // As a case to get a new perspective, this state should change position to the nreturn to Scan for Beacon
            // Enter Find new corner sub state machine
            ThisEvent = RunFindNewCorner(ThisEvent);
            switch (ThisEvent.EventType) {
                case FOUND_NEW_CORNER:
                    // make transition to scan for beacon state
                    nextState = ScanForBeacon;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                default:
                    break;
            }
        }
            break;

        case ReAdjustBot: // Re-adjust the bot in case the bot veers off course
            //this state to be changed - HZ 11/15
            //do we really need it tho
        {
            // Stops the bot mid way to the beacon to complete another partial sweep to find it again
            // Enter re-adjust bot sub state machine
            //ThisEvent = RunReAdjustBotSubHSM(ThisEvent);
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                case TURN_TIMER_EXP:
                    turnBot(LTANK_L, LTANK_R);
                    ES_Timer_InitTimer(MotionTimer, READJUST_SHAKE_TIME);
                    ES_Timer_StopTimer(TurnTimer);
                    break;
                case FOUND_BEACON:
                    // make transition to scan for beacon state
                    nextState = ToBeacon;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case MOTION_TIMER_EXP:
                    turnBot(RTANK_L, RTANK_R);
                    ES_Timer_InitTimer(TurnTimer, READJUST_SHAKE_TIME);
                    break;
                case ES_EXIT:
                    ES_Timer_StopTimer(TurnTimer);
                    ES_Timer_StopTimer(MotionTimer);
                    break;
                default:
                    break;
            }
        }
            break;
        case ToBeacon: // Moves the bot to the beacon
        {
            // Once the clsoes beacon is located, moves the bot immediately straight
            // Enter re-adjust bot sub state machine
            //ThisEvent = RunToBeacon(ThisEvent);
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    //Entry state
                    goForward();
                    break;
                case LOST_BEACON:
                    // make transition to re-adjust the bot
                    nextState = ReAdjustBot;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BUMP_EVENT:
                    // make tranisiton to navigate the tower
                    nextState = NavTower;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BOT_BT_CHANGED:
                    if (ThisEvent.EventType == F_CENTER_TAPE) {
                        nextState = AlignCenter;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    }
                case ES_EXIT:
                default:
                    break;
            }
        }
            break;
        case AlignCenter:
            if (ThisEvent.EventType == ES_ENTRY) {
                StartAlign_center = 1;
            }
            ThisEvent = RunAlignSubHSM(ThisEvent);
            switch (ThisEvent.EventType) {
                case FOUND_BEACON:
                    // make transition to move toward the beacon
                    nextState = ToBeacon;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                case ES_EXIT:
                    stop();
                default:
                    break;
            }
        case NavTower: // navigates around the tower and looks for the track wire
        {
            // Wall follows the tower. Once the track wire is detected, the bot then aligns
            // itself with the wall and looks for tape
            // Enter Navigate tower sub state machine
            //ThisEvent = RunNavTower(ThisEvent);
            if (ThisEvent.EventType == ES_ENTRY) {
                StartNavTower = 1;
            }
            ThisEvent = RunNavTower(ThisEvent);
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    //Entry state
                    break;
                case TOWER_DONE:
                    // make transition to scan for beacon state
                    nextState = ScanForBeacon;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_EXIT:
                    Tower_Found++;
                default:
                    break;
            }
        }
            break;
        case NavField: // Find black tape to look for beacon
        {
            // If a new beacon isn't found after ball release, this state locates a new corner to scan again
            // EnterNavigate Field sub state machine
            //ThisEvent = RunNavField(ThisEvent); 
            switch (ThisEvent.EventType) {
                case FOUND_NEW_CORNER:
                    // make transition to Scan for Beacon state
                    nextState = ScanForBeacon;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BUMP_EVENT:
                    // make tranisiton to Navigate Tower
                    nextState = NavTower;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                default:
                    break;
            }
        }
            break;


    }
    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunTopLevel(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunTopLevel(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

uint8_t TurnTimerHelper(ES_Event ThisEvent) {
    ES_Event posting;

    switch (ThisEvent.EventType) {
        case ES_INIT: //do nothing (initializing)
            break;

            /* do nothng */
        case ES_TIMERACTIVE:
        case ES_TIMERSTOPPED:
            break; // We don't use these events

            /* run internal event checkers */
        case ES_TIMEOUT:
            posting.EventParam = 1;
            posting.EventType = TURN_TIMER_EXP; //When the timer expires, it generates this event
            PostTopLevel(posting); //then send the event to the toplevel
            //printf("ExampleTimerEXP, %d\r\n", posting.EventType); // debug use.
            break;
        default:
            break;
    }
    return 0;
}

uint8_t MotionTimerHelper(ES_Event ThisEvent) {
    ES_Event posting;

    switch (ThisEvent.EventType) {
        case ES_INIT: //do nothing (initializing)
            break;

            /* do nothng */
        case ES_TIMERACTIVE:
        case ES_TIMERSTOPPED:
            break; // We don't use these events

            /* run internal event checkers */
        case ES_TIMEOUT:
            posting.EventParam = 1;
            posting.EventType = MOTION_TIMER_EXP; //When the timer expires, it generates this event
            PostTopLevel(posting); //then send the event to the toplevel
            //printf("ExampleTimerEXP, %d\r\n", posting.EventType); // debug use.
            ES_Timer_StopTimer(MotionTimer);
            break;
        default:
            break;
    }
    return 0;
}

