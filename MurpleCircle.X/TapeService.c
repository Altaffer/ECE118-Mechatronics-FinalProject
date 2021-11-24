/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include "BOARD.h"
#include "AD.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "TapeService.h"
#include "ES_Timers.h"
#include <robot.h>
#include <stdio.h>
#include <TopLevel.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define TAPE_TICKS 100//test
#define TIMER_HIGH_TICKS 1
//define PING_PIN PORTW03_BIT // defined in the config file

#define SHOOTER_1 16 //0b 01 0000
#define SHOOTER_2 32 //0b 10 0000
#define SHOOTER 48 //0b 11 0000
#define BOTTOM 15 //0b 00 1111

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
uint8_t InitTapeService(uint8_t Priority)
{
    ES_Event ThisEvent;

    MyPriority = Priority;
    printf("tape init\r\n");
    // in here you write your initialization code
    // this includes all hardware and software initialization
    // that needs to occur.
    ES_Timer_InitTimer(TapeTimer, TAPE_TICKS);
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
uint8_t PostTapeService(ES_Event ThisEvent)
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
ES_Event RunTapeService(ES_Event ThisEvent) {
    ES_Event ReturnEvent;
    ReturnEvent.EventType = ES_NO_EVENT; // assume no errors

    /********************************************
     in here you write your service code
     *******************************************/
    static uint8_t past_status = 0;
    uint8_t curr_status = Robot_ReadTapeSensors();
    uint8_t changed_bits = curr_status ^ past_status;
    switch (ThisEvent.EventType) {
        case ES_TIMEOUT:
            if (curr_status == past_status) {
                break;
            }
            if (changed_bits & SHOOTER) {
                ReturnEvent.EventType = SHOOTER_BT_CHANGED;
                ReturnEvent.EventParam = curr_status;
                PostTopLevel(ReturnEvent);//can be any wrapper function
            }
            
            if (changed_bits & BOTTOM) {
                ReturnEvent.EventType = BOT_BT_CHANGED;
                ReturnEvent.EventParam = curr_status;
                PostTopLevel(ReturnEvent);//can be any wrapper function
            }
            
            break;
        default:
            break;
    }
    past_status = curr_status;
    
    return ReturnEvent;
}
