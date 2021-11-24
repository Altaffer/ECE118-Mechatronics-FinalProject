/******************************************************************************/
/* Bot Helper Functions - Motions
 * 
 * Helper functions that control the motion of the bot
 *  
 * UCSC ECE118 Final Project -  Fall 2021
 * Horace & Emma & Luca - 11/14
 ******************************************************************************/

#include "ES_Configure.h"
#include "ES_Framework.h"
#include <ES_Timers.h>

#include "TopLevel.h"
#include <BOARD.h>
#include "robot.h"

#include <stdio.h>
#include <stdlib.h>


/*******************************************************************************
 * FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
// speed and direction
#define FWD_speed 90    // Straight
#define STOP_speed 0    // stopping
#define REV_speed -90    // Straight


#define LTANK_L -60     // tank turns
#define LTANK_R 60
#define RTANK_L 60
#define RTANK_R -60

#define LPIVOT_L 0      // pivot turns
#define LPIVOT_R 60
#define RPIVOT_L 60
#define RPIVOT_R 0

#define LGRAD_L 20      // gradual turn
#define LGRAD_R 60
#define RGRAD_R 20
#define RGRAD_L 60

uint8_t goForward(void);

uint8_t Reverse(void);

uint8_t CWTank(void);

uint8_t CCWTank(void)

uint8_t spin(void);

uint8_t spiral(void);

uint8_t stop(void);

/*******************************************************************************
 * FUNCTIONS                                                           *
 ******************************************************************************/
// Borrowed from what Luca had on 11/13 - HZ 11/14
uint8_t goForward(void) {
    //something here to make the bot go forward at full speed
    Robot_LeftMtrSpeed(FWD_speed);
    Robot_RightMtrSpeed(FWD_speed);

    return 0; //this could be used to indicated true or false. Not necessary tho. 
}

uint8_t Reverse(void) {
    //reverse bot
    Robot_LeftMtrSpeed(REV_speed);
    Robot_RightMtrSpeed(REV_speed);

    return 0; //this could be used to indicated true or false. Not necessary tho. 
}

uint8_t CWTank(void) {
    //clockwise tank turn
    Robot_LeftMtrSpeed(LTANK_R);
    Robot_RightMtrSpeed(RTANK_R);
}

uint8_t CCWTank(void) {
    //counter clockwise tank turn
    Robot_LeftMtrSpeed(LTANK_L);
    Robot_RightMtrSpeed(RTANK_L);
}

uint8_t spin(void) {
    //turn bot
    Robot_LeftMtrSpeed(LPIVOT_L);
    Robot_RightMtrSpeed(LPIVOT_R);
    return 0;
}

uint8_t spiral(void) {
    //turn bot
    Robot_LeftMtrSpeed(LGRAD_L);
    Robot_RightMtrSpeed(LGRAD_R);
    return 0;
}

uint8_t stop(void) { //one concern - if the gearhead is too powerful we may need to slow down first
    //stop the bot
    Robot_LeftMtrSpeed(STOP_speed);
    Robot_RightMtrSpeed(STOP_speed);


    return 0;
}


