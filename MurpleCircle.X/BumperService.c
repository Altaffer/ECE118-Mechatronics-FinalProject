/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "BOARD.h"
#include "AD.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BumperService.h"
#include "ES_Timers.h"
#include <robot.h>
#include <stdio.h>
#include <TopLevel.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define LEFT 1 // 0b 001
#define RIGHT 2 //0b 010
#define BOTH 3 // 0b 011
#define SERVO 4 //0b 100



static uint8_t MyPriority;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateService(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateService function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitBumperService(uint8_t Priority)
{
    ES_Event ThisEvent;

    MyPriority = Priority;
    printf("bumper init\r\n");
    // in here you write your initialization code
    // this includes all hardware and software initialization
    // that needs to occur.
    ES_Timer_InitTimer(BumperTimer, BUMPER_TIME);
    // post the initial transition event
    ThisEvent.EventType = ES_INIT;
    if (ES_PostToService(MyPriority, ThisEvent) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostBumperService(ES_Event ThisEvent)
{
    //printf("\r\n%d,%d\r\n",ThisEvent.EventParam, ThisEvent.EventType);
    return ES_PostToService(MyPriority, ThisEvent);
    
}

/**
 * @Function RunTemplateService(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the service,
 *        as this is called any time a new event is passed to the event queue. 
 * @note Remember to rename to something appropriate.
 *       Returns ES_NO_EVENT if the event have been "consumed." 
 * @author J. Edward Carryer, 2011.10.23 19:25 */
ES_Event RunBumperService(ES_Event ThisEvent) {
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

    /********************************************
     in here you write your service code
     *******************************************/
    static uint8_t past_val = 0;
    uint8_t curr_val = Robot_ReadBumpers();
    switch (ThisEvent.EventType) {
        case ES_TIMEOUT:
            if (curr_val == past_val) {
                break;
            }
            if (curr_val & SERVO) { //1zz
                ReturnEvent.EventType = BUMPER_SERVO;
                ReturnEvent.EventParam = curr_val;
                PostTopLevel(ReturnEvent);//can be any wrapper function
            }
            if ((curr_val & BOTH) == BOTH) { // z11
                ReturnEvent.EventType = BUMPED_BOTH;
                ReturnEvent.EventParam = curr_val;
                PostTopLevel(ReturnEvent);//can be any wrapper function
            } else if (curr_val & LEFT) { // z01
                ReturnEvent.EventType = BUMPED_LEFT;
                ReturnEvent.EventParam = curr_val;
                PostTopLevel(ReturnEvent);//can be any wrapper function
            } else if (curr_val & RIGHT) { // z10
                ReturnEvent.EventType = BUMPED_RIGHT;
                ReturnEvent.EventParam = curr_val;
                PostTopLevel(ReturnEvent);//can be any wrapper function
            }
            break;
        default:
            break;
    }
    past_val = curr_val;
    
    return ReturnEvent;
}
