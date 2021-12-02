/****************************************************************************
 Module
     ES_Configure.h
 Description
     This file contains macro definitions that are edited by the user to
     adapt the Events and Services framework to a particular application.
 Notes
     
 History
 When           Who     What/Why
 -------------- ---     --------
 01/15/12 10:03 jec      started coding
 *****************************************************************************/

#ifndef CONFIGURE_H
#define CONFIGURE_H

//#include "TopLevel.h"

//defines for keyboard input
//#define USE_KEYBOARD_INPUT
//What State machine are we testing
//#define POSTFUNCTION_FOR_KEYBOARD_INPUT PostTopLevel

//define for TattleTale
//#define USE_TATTLETALE

//uncomment to supress the entry and exit events
//#define SUPPRESS_EXIT_ENTRY_IN_TATTLE

/****************************************************************************/
// Name/define the events of interest
// Universal events occupy the lowest entries, followed by user-defined events


#define TurnTimer 1
#define ForwardTimer 2
#define ReverseTimer 3
#define PingTriggerTimer 4
#define BumperTimer 5
//#define SpinTimer 6
#define MotionTimer 15

#define TIMER_90 500
#define BOT_MIDDLE_TIME 400
#define BUMPER_TIME 100
#define TIMER_360 (TIMER_90 * 4)

#define TW_UPPER_BOUND 640//TW = Track Wire
#define TW_LOWER_BOUND 400

#define FINDHOLE_EXPIRE_TIME 2000//forward too much - go reverse
#define WALL_HUG_FORWARD_TIME 300
#define WALL_HUG_REVERSE_TIME 310
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

#define FINDHOLE_TURN_TIME 800 
#define FIND_HOLE_TURN_L 70
#define FIND_HOLE_TURN_R 100

#define FIND_HOLE_BACK_TURN_L -90
#define FIND_HOLE_BACK_TURN_R -80

#define FIND_HOLE_BACK_PIVOT_TIME 600
#define FIND_HOLE_BACK_PIVOT_L 0
#define FIND_HOLE_BACK_PIVOT_R -70

#define FINDHOLE_FORWARD_TIME 2000 
#define FIND_HOLE_FORWARD_L -80
#define FIND_HOLE_FORWARD_R -50

#define FINDHOLE_REVERSE_TIME 4000 


#define USE_TAPE_SERVICE //this option disables the working one in the event checkers
#define TapeTimer 6

/****************************************************************************/
typedef enum {
    ES_NO_EVENT, ES_ERROR, /* used to indicate an error from the service */
    ES_INIT, /* used to transition from initial pseudo-state */
    ES_ENTRY, /* used to enter a state*/
    ES_EXIT, /* used to exit a state*/
    ES_KEYINPUT, /* used to signify a key has been pressed*/
    ES_LISTEVENTS, /* used to list events in keyboard input, does not get posted to fsm*/
    ES_TIMEOUT, /* signals that the timer has expired */
    ES_TIMERACTIVE, /* signals that a timer has become active */
    ES_TIMERSTOPPED, /* signals that a timer has stopped*/
    /* User-defined events start here */

    //bumper events
    BUMP_EVENT,
    BUMPER_SERVO,
    BUMP_BACK,

    //black tape sensors on the bottom
    BOT_BT_CHANGED, // event #15


    //Black tape sensors on the shooter
    SHOOTER_BT_CHANGED,
    BT_FOUND_SHOOTER_1, //we don't need these four
    BT_LOST_SHOOTER_1,
    BT_FOUND_SHOOTER_2,
    BT_LOST_SHOOTER_2,

    //Timer events
    TURN_TIMER_EXP,
    FORWARD_TIMER_EXP,
    REVERSE_TIMER_EXP,
    MOTION_TIMER_EXP, // event #24

    //Tower events
    BALLSHOT,
    LOADED,
    FOUND_BEACON,
    LOST_BEACON,
    FOUND_TRACK_WIRE,
    LOST_TRACK_WIRE, //just in case
    FOUND_TOWER,
    TOWER_DONE,
    FOUND_HOLE,
    IS_PARALLEL,

    //Bot Events
    BOT_ORIENTED,
    NO_SIGNAL,
    FOUND_NEW_CORNER,
    FOUND_BOX,
    FOUND_TAPE,



    FOUND_PING,

    NUMBEROFEVENTS,




} ES_EventTyp_t;

static const char *EventNames[] = {
    "ES_NO_EVENT",
    "ES_ERROR",
    "ES_INIT",
    "ES_ENTRY",
    "ES_EXIT",
    "ES_KEYINPUT",
    "ES_LISTEVENTS",
    "ES_TIMEOUT",
    "ES_TIMERACTIVE",
    "ES_TIMERSTOPPED",

    //bumper events
    "BUMP_EVENT",
    "BUMPER_SERVO",
    "BUMP_BACK",

    //black tape sensors on the bottom
    "BOT_BT_CHANGED",

    //Black tape sensors on the shooter
    "SHOOTER_BT_CHANGED",
    "BT_FOUND_SHOOTER_1",
    "BT_LOST_SHOOTER_1",
    "BT_FOUND_SHOOTER_2",
    "BT_LOST_SHOOTER_2",

    //Timer events
    "TURN_TIMER_EXP",
    "FORWARD_TIMER_EXP",
    "REVERSE_TIMER_EXP",
    "MOTION_TIMER_EXP",

    //Tower events
    "BALLSHOT",
    "LOADED",
    "FOUND_BEACON",
    "LOST_BEACON",
    "FOUND_TRACK_WIRE",
    "LOST_TRACK_WIRE", //just in case
    "FOUND_TOWER",
    "TOWER_DONE",
    "FOUND_HOLE",
    "IS_PARALLEL",

    //Bot Events
    "BOT_ORIENTED",
    "NO_SIGNAL",
    "FOUND_NEW_CORNER",
    "FOUND_BOX",
    "FOUND_TAPE",



    "FOUND_PING",
    "NUMBEROFEVENTS",

};




/****************************************************************************/
// This are the name of the Event checking function header file.
#define EVENT_CHECK_HEADER "EventCheckers.h"

/****************************************************************************/
// This is the list of event checking functions
#define EVENT_CHECK_LIST  PingEventChecker, TapeSensorEventChecker, BeaconEventChecker, TrackWireEventChecker

/****************************************************************************/
// These are the definitions for the post functions to be executed when the
// corresponding timer expires. All 16 must be defined. If you are not using
// a timers, then you can use TIMER_UNUSED
#define TIMER_UNUSED ((pPostFunc)0)
#define TIMER0_RESP_FUNC TIMER_UNUSED
#define TIMER1_RESP_FUNC TurnTimerHelper
#define TIMER2_RESP_FUNC TIMER_UNUSED
#define TIMER3_RESP_FUNC TIMER_UNUSED
#define TIMER4_RESP_FUNC PostPingService
#define TIMER5_RESP_FUNC PostBumperService
#ifdef USE_TAPE_SERVICE
#define TIMER6_RESP_FUNC PostTapeService
#else
#define TIMER6_RESP_FUNC TIMER_UNUSED
#endif
#define TIMER7_RESP_FUNC TIMER_UNUSED
#define TIMER8_RESP_FUNC TIMER_UNUSED
#define TIMER9_RESP_FUNC TIMER_UNUSED
#define TIMER10_RESP_FUNC TIMER_UNUSED
#define TIMER11_RESP_FUNC TIMER_UNUSED
#define TIMER12_RESP_FUNC TIMER_UNUSED
#define TIMER13_RESP_FUNC TIMER_UNUSED
#define TIMER14_RESP_FUNC TIMER_UNUSED
#define TIMER15_RESP_FUNC MotionTimerHelper
//#define TIMER15_RESP_FUNC TIMER_UNUSED // for when we are using TestTopLevel.c


/****************************************************************************/
// Give the timer numbers symbolc names to make it easier to move them
// to different timers if the need arises. Keep these definitons close to the
// definitions for the response functions to make it easire to check that
// the timer number matches where the timer event will be routed

#define GENERIC_NAMED_TIMER 0 /*make sure this is enabled above and posting to the correct state machine*/


/****************************************************************************/
// The maximum number of services sets an upper bound on the number of 
// services that the framework will handle. Reasonable values are 8 and 16
// HOWEVER: at this time only a value of 8 is supported.
#define MAX_NUM_SERVICES 8

/****************************************************************************/
// This macro determines that number of services that are *actually* used in
// a particular application. It will vary in value from 1 to MAX_NUM_SERVICES
#define NUM_SERVICES 5//when we decide to use the tape service, change it to 
//at least 5

///****************************************************************************/
//// These are the definitions for Service 0, the lowest priority service
//// every Events and Services application must have a Service 0. Further 
//// services are added in numeric sequence (1,2,3,...) with increasing 
//// priorities
//// the header file with the public function prototypes
//#define SERV_0_HEADER "TopLevel.h"
//// the name of the Init function
//#define SERV_0_INIT InitTopLevel
//// the name of the run function
//#define SERV_0_RUN RunTopLevel
//// How big should this service's Queue be?
//#define SERV_0_QUEUE_SIZE 9

/****************************************************************************/
// These are the definitions for Service 0, the lowest priority service
// every Events and Services application must have a Service 0. Further 
// services are added in numeric sequence (1,2,3,...) with increasing 
// priorities
// the header file with the public fuction prototypes
#define SERV_0_HEADER "ES_KeyboardInput.h"
// the name of the Init function
#define SERV_0_INIT InitKeyboardInput
// the name of the run function
#define SERV_0_RUN RunKeyboardInput
// How big should this service's Queue be?
#define SERV_0_QUEUE_SIZE 9

/****************************************************************************/
// These are the definitions for Service 1
#if NUM_SERVICES > 1
// the header file with the public fuction prototypes
#define SERV_1_HEADER "TestTopLevel.h"
// the name of the Init function
#define SERV_1_INIT InitTopLevel
// the name of the run function
#define SERV_1_RUN RunTopLevel
// How big should this services Queue be?
#define SERV_1_QUEUE_SIZE 9
#endif

/****************************************************************************/
// These are the definitions for Service 2
#if NUM_SERVICES > 2
// the header file with the public fuction prototypes
#define SERV_2_HEADER "PingService.h"
// the name of the Init function
#define SERV_2_INIT InitPingService
// the name of the run function
#define SERV_2_RUN RunPingService
// How big should this services Queue be?
#define SERV_2_QUEUE_SIZE 9
#endif



/****************************************************************************/
// These are the definitions for Service 3
#if NUM_SERVICES > 3
// the header file with the public fuction prototypes
#define SERV_3_HEADER "BumperService.h"
// the name of the Init function
#define SERV_3_INIT InitBumperService
// the name of the run function
#define SERV_3_RUN RunBumperService
// How big should this services Queue be?
#define SERV_3_QUEUE_SIZE 9
#endif

/****************************************************************************/
// These are the definitions for Service 4
#if NUM_SERVICES > 4
// the header file with the public fuction prototypes
#define SERV_4_HEADER "TapeService.h"
// the name of the Init function
#define SERV_4_INIT InitTapeService
// the name of the run function
#define SERV_4_RUN RunTapeService
// How big should this services Queue be?
#define SERV_4_QUEUE_SIZE 9
#endif

/****************************************************************************/
// These are the definitions for Service 5
#if NUM_SERVICES > 5
// the header file with the public fuction prototypes
#define SERV_5_HEADER "NavigateTowerSub.h"
// the name of the Init function
#define SERV_5_INIT InitNavigateTower
// the name of the run function
#define SERV_5_RUN RunNavigateTower
// How big should this services Queue be?
#define SERV_5_QUEUE_SIZE 9
#endif

/****************************************************************************/
// These are the definitions for Service 6
#if NUM_SERVICES > 6
// the header file with the public fuction prototypes
#define SERV_6_HEADER "MoveToBeaconSub.h"
// the name of the Init function
#define SERV_6_INIT InitMoveToBeacon
// the name of the run function
#define SERV_6_RUN RunMoveToBeacon
// How big should this services Queue be?
#define SERV_6_QUEUE_SIZE 9
#endif

/****************************************************************************/
// These are the definitions for Service 7
#if NUM_SERVICES > 7
// the header file with the public fuction prototypes
#define SERV_7_HEADER "ParkSub.h"
// the name of the Init function
#define SERV_7_INIT InitPark
// the name of the run function
#define SERV_7_RUN RunPark
// How big should this services Queue be?
#define SERV_7_QUEUE_SIZE 9
#endif

/****************************************************************************/
// the name of the posting function that you want executed when a new 
// keystroke is detected.
// The default initialization distributes keystrokes to all state machines
#define POST_KEY_FUNC ES_PostAll



/****************************************************************************/
// These are the definitions for the Distribution lists. Each definition
// should be a comma seperated list of post functions to indicate which
// services are on that distribution list.
#define NUM_DIST_LISTS 0 

//Horace added 11/12:
// for now I will only put posttoplevel.
// This wrapper function only returns True or False depending on the Queue status
// We probably don't need it at all
//Luca added 11/12:
// Hoarce my guy. What is this?

#if NUM_DIST_LISTS > 0 
#define DIST_LIST0 PostTopLevel
#endif
#if NUM_DIST_LISTS > 1 
#define DIST_LIST1 PostTemplateFSM
#endif
#if NUM_DIST_LISTS > 2 
#define DIST_LIST2 PostTemplateFSM
#endif
#if NUM_DIST_LISTS > 3 
#define DIST_LIST3 PostTemplateFSM
#endif
#if NUM_DIST_LISTS > 4 
#define DIST_LIST4 PostTemplateFSM
#endif
#if NUM_DIST_LISTS > 5 
#define DIST_LIST5 PostTemplateFSM
#endif
#if NUM_DIST_LISTS > 6 
#define DIST_LIST6 PostTemplateFSM
#endif
#if NUM_DIST_LISTS > 7 
#define DIST_LIST7 PostTemplateFSM
#endif



#endif /* CONFIGURE_H */