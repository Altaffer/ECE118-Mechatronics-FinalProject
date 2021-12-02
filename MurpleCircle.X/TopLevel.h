/*
 * File: TemplateHSM.h
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
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
 * Created on 23/Oct/2011
 * Updated on 16/Sep/2013
 */

#ifndef Top_Level_H  // <- This should be changed to your own guard on both
#define Top_Level_H  //    of these lines


/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/
#define TIMER_90 500
#define BOT_MIDDLE_TIME 400
#define BUMPER_TIME 100
#define TIMER_360 (TIMER_90 * 4)

#define TW_UPPER_BOUND 600//TW = Track Wire
#define TW_LOWER_BOUND 400

#define FINDHOLE_EXPIRE_TIME 2000//forward too much - go reverse
#define WALL_HUG_FORWARD_TIME 300
#define WALL_HUG_REVERSE_TIME 510
#define WALL_HUG_CORNER_TIME 1000
#define NAV_TOWER_LEAVE_TIME 500
#define CORNER_ALIGN_TIME 100
#define ABRUPT_TURN_TIME 500
#define ALIGN_RIGHT_TIME 500
#define FIND_NEW_CORNER_EXP_TIME 300 //they should use the same time
#define READJUST_SHAKE_TIME 300
#define WALL_HUG_END_TIME 25000

#define SCAN_TURN_TIME (TIMER_360) //360 degrees

#define SCAN_THRESHOLD 20

#define FINDHOLE_TURN_TIME 700 
#define FIND_HOLE_TURN_L 70
#define FIND_HOLE_TURN_R 100

#define FIND_HOLE_BACK_TURN_L -90
#define FIND_HOLE_BACK_TURN_R -90

#define FIND_HOLE_BACK_PIVOT_TIME 600
#define FIND_HOLE_BACK_PIVOT_L 0
#define FIND_HOLE_BACK_PIVOT_R -70

#define FINDHOLE_FORWARD_TIME 1000 
#define FIND_HOLE_FORWARD_L 50
#define FIND_HOLE_FORWARD_R 50



#define FINDHOLE_REVERSE_TIME 2000
#define FIND_HOLE_REVERSE_L -50
#define FIND_HOLE_REVERSE_R -50

/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
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
uint8_t InitTopLevel(uint8_t Priority);


/**
 * @Function PostTemplateHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostTopLevel(ES_Event ThisEvent);




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
ES_Event RunTopLevel(ES_Event ThisEvent);

uint8_t TurnTimerHelper(ES_Event ThisEvent);

uint8_t MotionTimerHelper(ES_Event ThisEvent);

uint8_t TurnTimerHelper(ES_Event ThisEvent);

#endif /* Top_Level_H */

