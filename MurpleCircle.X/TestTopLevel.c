//THIS FILE HAS STUFF TO STATE MACHINE DO

/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"

#include "TestTopLevel.h"
#include "stdio.h"
#include "stdlib.h"

#include "AlignSubHSM.h"
#include "WallHugSubHSM.h"
//#include all sub state machines called
/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
//Include any defines you need to do

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

typedef enum
{
    InitPState,
    Align,
    WallHug,
} TemplateHSMState_t;

static const char *StateNames[] = {
    "InitPState",
    "Align",
    "WallHug",
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

static TemplateHSMState_t CurrentState = InitPState; // <- change enum name to match ENUM
static uint8_t MyPriority;

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
uint8_t InitTopLevel(uint8_t Priority)
{
    MyPriority = Priority;
    // put us into the Initial PseudoState
    CurrentState = InitPState;
    InitWallHug();
    InitAlignSubHSM();
    // post the initial transition event
    if (ES_PostToService(MyPriority, INIT_EVENT) == TRUE)
    {
        return TRUE;
    }
    else
    {
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
uint8_t PostTopLevel(ES_Event ThisEvent)
{
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
ES_Event RunTopLevel(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE; // use to flag transition
    TemplateHSMState_t nextState;   // <- change type to correct enum
    static uint8_t Tower_Found = 0;

    ES_Tattle(); // trace call stack

    switch (CurrentState)
    {
    case InitPState:                        // If current state is initial Pseudo State
        if (ThisEvent.EventType == ES_INIT) // only respond to ES_Init
        {
            // this is where you would put any actions associated with the
            // transition from the initial pseudo-state into the actual
            // initial state
            // Initialize all sub-state machines
//            InitTemplateSubHSM();
            // now put the machine into the actual initial state
            nextState = Align;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
            ;
        }
        break;

    case Align: //
    {
        if (ThisEvent.EventType == ES_ENTRY) {
            //StartAlign = 1;
            ;
        }
        ThisEvent = RunAlignSubHSM(ThisEvent);
        switch (ThisEvent.EventType)
        {
        case BUMP_EVENT:
                nextState = WallHug;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            
            break;            
        case ES_NO_EVENT:
        default:
            break;
        }
    }
    break;
    case WallHug: 
    {
        if (ThisEvent.EventType == ES_ENTRY) {
            StartWallHug = 1;
        }
        ThisEvent = RunWallHug(ThisEvent);
        switch (ThisEvent.EventType)
        {
        case BOT_BT_CHANGED:
            nextState = Align;
            makeTransition = TRUE;
            ThisEvent.EventType = ES_NO_EVENT;
            break;
        case ES_NO_EVENT:
        default:
            break;
        }
    }
        break;
    default:
        break;
        
    }
    if (makeTransition == TRUE)
        { // making a state transition, send EXIT and ENTRY
            // recursively call the current state with an exit event
            RunTopLevel(EXIT_EVENT); // <- rename to your own Run function
            CurrentState = nextState;
            RunTopLevel(ENTRY_EVENT); // <- rename to your own Run function
        }

        ES_Tail(); // trace call stack end
        return ThisEvent;
}


uint8_t MotionTimerHelper(ES_Event ThisEvent){
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
        PostTopLevel(posting);//then send the event to the toplevel
        printf("ExampleTimerEXP, %d\r\n", posting.EventType); // debug use.
        ES_Timer_StopTimer(MotionTimer);
        break;
    default:
        break;
    }
    return 0;
}
    /*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
