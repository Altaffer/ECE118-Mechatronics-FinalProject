/*
 * File:   roach.h
 * Author: mdunne
 *
 * Created on January 6, 2012, 10:59 AM
 * Modified by: Max Dunne on 2015.09.18 to implement LED functions and remap 
 * pins for NEW_ROACH functionality. 
 *
 * Implements basic functionality for Robot robot for sensors and actuators
 *
 * If using a new roach, create a NEW_ROACH macro at the project level
 *              in MPLAB-X using the global preprocessor directives.
 */




#ifndef ROBOT_H
#define ROBOT_H

#include <BOARD.h>


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/
// speed and direction
#define FWD_speed 75    // Straight
#define BCKWD_speed -75 
#define STOP_speed 0    // stopping
#define RIGHT_WHEEL_OFFSET 18

#define LTANK_L -80     // tank turns
#define LTANK_R 80
#define RTANK_L 80
#define RTANK_R -80
#define LTANK_L_SLOW -70     // tank turns
#define LTANK_R_SLOW 70

#define LPIVOT_L 0      // pivot turns
#define LPIVOT_R 80
#define RPIVOT_L 80
#define RPIVOT_R 0

#define LGRAD_L 40      // gradual turn
#define LGRAD_R 80
#define RGRAD_R 40
#define RGRAD_L 80

// bumper events
#define BUMPER_TRIPPED 1
#define BUMPER_NOT_TRIPPED 0

// maximums
#define ROBOT_MAX_SPEED 100 

/**
 * @Function Robot_Init(void)
 * @param None.
 * @return None.
 * @brief  Performs all the initialization necessary for the roach. this includes initializing
 * the PWM module, the A/D converter, the data directions on some pins, and
 * setting the initial motor directions.
 * @note  None.
 * @author Max Dunne, 2012.01.06 */
void Robot_Init(void);


/**
 * @Function Robot_LeftMtrSpeed(char newSpeed)
 * @param newSpeed - A value between -100 and 100 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @author Max Dunne, 2012.01.06 */
char Robot_LeftMtrSpeed(char newSpeed);

/**
 * @Function Robot_RightMtrSpeed(char newSpeed)
 * @param newSpeed - A value between -100 and 100 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @author Max Dunne, 2012.01.06 */
char Robot_RightMtrSpeed(char newSpeed);

/**
 * @Function Robot_LightLevel(void)
 * @param None.
 * @return a 10-bit value corresponding to the amount of light received.
 * @brief  Returns the current light level. A higher value means less light is detected.
 * @author Max Dunne, 2012.01.06 */
unsigned int Robot_LightLevel(void);

/**
 * @Function Robot_BatteryVoltage(void)
 * @param None.
 * @return a 10-bit value corresponding to the current voltage of the roach
 * @brief  returns a 10:1 scaled value of the roach battery level
 * @author Max Dunne, 2013.07.12 */
unsigned int Robot_BatteryVoltage(void);

/**
 * @Function Robot_ReadFrontLeftBumper(void)
 * @param None.
 * @return BUMPER_TRIPPED or BUMPER_NOT_TRIPPED
 * @brief  Returns the state of the front left bumper
 * @author Max Dunne, 2012.01.06 */
unsigned char Robot_ReadFrontLeftBumper(void);


/**
 * @Function Robot_ReadFrontRightBumper(void)
 * @param None.
 * @return BUMPER_TRIPPED or BUMPER_NOT_TRIPPED
 * @brief  Returns the state of the front right bumper
 * @author Max Dunne, 2012.01.06 */
unsigned char Robot_ReadFrontRightBumper(void);

/**
 * @Function Robot_ReadRearLeftBumper(void)
 * @param None.
 * @return BUMPER_TRIPPED or BUMPER_NOT_TRIPPED
 * @brief  Returns the state of the rear left bumper
 * @author Max Dunne, 2012.01.06 */
unsigned char Robot_ReadRearLeftBumper(void);

/**
 * @Function Robot_ReadRearRightBumper(void)
 * @param None.
 * @return BUMPER_TRIPPED or BUMPER_NOT_TRIPPED
 * @brief  Returns the state of the rear right bumper
 * @author Max Dunne, 2012.01.06 */
unsigned char Robot_ReadRearRightBumper(void);

/**
 * @Function Robot_ReadBumpers(void)
 * @param None.
 * @return 4-bit value representing all four bumpers in following order: front left,front right, rear left, rear right
 * @brief  Returns the state of all 4 bumpers
 * @author Max Dunne, 2012.01.06 */
unsigned char Robot_ReadBumpers(void);



/**
 * @Function Robot_LEDSSet( unsigned char pattern)
 * @param pattern - sets LEDs on (1) or off (0) as in the pattern.
 * @return SUCCESS or ERROR
 * @brief  Forces the LEDs in (bank) to on (1) or off (0) to match the pattern.
 * @author Gabriel Hugh Elkaim, 2011.12.25 01:16 Max Dunne 2015.09.18 */
char Robot_LEDSSet(uint16_t pattern);

/**
 * @Function Robot_LEDSGet(void)
 * @return uint16_t: ERROR or state of BANK
 * @author Max Dunne, 203.10.21 01:16 2015.09.18 */
uint16_t Robot_LEDSGet(void);

/**
 * @Function Robot_BarGraph(uint8_t Number)
 * @param Number - value to light between 0 and 12 leds
 * @return SUCCESS or ERROR
 * @brief  allows all leds to be used as a bar graph
 * @author  Max Dunne 2015.09.18 */
char Robot_BarGraph(uint8_t Number);

uint8_t goForward(void);

uint8_t spin(void);

uint8_t turnBot(char leftSpeed, char rightSpeed);

uint8_t stop(void);

unsigned char Robot_ReadTapeSensors(void);

uint32_t Robot_ReadTrackWire(void);

uint8_t Robot_ReadBeaconSensor(void);

uint8_t Robot_ReadPingSensor(void); 

uint8_t Robot_ReadPingTrigger(void); 

uint8_t Robot_TrigPingSensor(uint8_t trig);

int Robot_SetServoSpeed(unsigned short int pulseTime);

#endif
