/*
 * File:   robot.c
 * Author: mdunne, elkaim
 *
 * Created on December 15, 2011, 12:59 PM
 * Modified to remove PLIB on June 29, 2021
 */

#include "xc.h"
#include "BOARD.h"
#include "LED.h"
#include "robot.h"
#include <stdio.h>
#include <stdlib.h>
#include "timers.h"
#include "ES_Configure.h"

#include <pwm.h>
#include <serial.h>
#include <AD.h>
#include "IO_Ports.h"
#include "RC_Servo.h"

/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
#define INPUT 1
#define OUTPUT 0

#define LEFT_DIR LATBbits.LATB3 // V04
#define LEFT_DIR_INV LATBbits.LATB2 // V03
#define RIGHT_DIR LATEbits.LATE5 // Y11
#define RIGHT_DIR_INV LATEbits.LATE6 // Y09

#define TAPE_SENSOR_1 PORTX03_BIT
#define TAPE_SENSOR_2 PORTX04_BIT
#define TAPE_SENSOR_3 PORTX05_BIT
#define TAPE_SENSOR_4 PORTX06_BIT
#define TAPE_SENSOR_5 PORTX07_BIT
#define TAPE_SENSOR_6 PORTX08_BIT

#define PING_PIN PORTW03_BIT 
#define PING_TRIG PORTW07_BIT

#define BEACON_PIN PORTX10_BIT
#define BEACON_TRIS PORTX10_TRIS
#define TRACK_WIRE_PIN AD_PORTV6
#define SHOOTER_SERVO RC_PORTY07

#define TAPE_SENSOR_1_TRIS PORTX03_TRIS
#define TAPE_SENSOR_2_TRIS PORTX04_TRIS
#define TAPE_SENSOR_3_TRIS PORTX05_TRIS
#define TAPE_SENSOR_4_TRIS PORTX06_TRIS
#define TAPE_SENSOR_5_TRIS PORTX07_TRIS
#define TAPE_SENSOR_6_TRIS PORTX08_TRIS

#define HALL_FRONT_LEFT _RB8 // V07
//#define HALL_FRONT_RIGHT _RD9 // V08 I don't think this pin works so I moved
// to _RD8 (Z08)
#define HALL_FRONT_RIGHT _RD8 // <- this is the new front right bump pin (Z08))
#define HALL_REAR_LEFT _RB10 // W04 used for ball shooter switch
#define BACK_BUMPER PORTZ03_BIT

#define LEFT_DIR_TRIS _TRISB3
#define LEFT_DIR_INV_TRIS _TRISB2
#define RIGHT_DIR_TRIS _TRISE5
#define RIGHT_DIR_INV_TRIS _TRISE6

#define HALL_FRONT_LEFT_TRIS _TRISB8
#define HALL_FRONT_RIGHT_TRIS _TRISD9
#define HALL_REAR_RIGHT_TRIS _TRISD8
#define HALL_REAR_LEFT_TRIS _TRISB10
#define BACK_BUMPER_TRIS PORTZ03_TRIS

#define LEFT_PWM PWM_PORTY10
#define RIGHT_PWM PWM_PORTY12

//#define LIGHT_SENSOR ROACH_LIGHT_SENSOR
//#define ROBOT_BAT_VOLTAGE BAT_VOLTAGE



/*******************************************************************************
 * PRIVATE VARIABLES                                                           *
 ******************************************************************************/

//typedef union {
//
//    struct {
//        unsigned bit0 : 1;
//        unsigned bit1 : 1;
//        unsigned bit2 : 1;
//        unsigned bit3 : 1;
//        unsigned bit4 : 1;
//        unsigned bit5 : 1;
//        unsigned bit6 : 1;
//        unsigned bit7 : 1;
//        unsigned bit8 : 1;
//        unsigned bit9 : 1;
//        unsigned bit10 : 1;
//        unsigned bit11 : 1;
//        unsigned : 4;
//    };
//    uint16_t c;
//} LEDBank_t;


//static volatile unsigned int * const LED_TRISCLR[] = {&TRISECLR, &TRISDCLR, &TRISDCLR, &TRISDCLR,
//    &TRISDCLR, &TRISDCLR, &TRISDCLR, &TRISFCLR, &TRISFCLR, &TRISGCLR, &TRISFCLR, &TRISFCLR};
//
//static volatile unsigned int * const LED_TRISSET[] = {&TRISESET, &TRISDSET, &TRISDSET, &TRISDSET,
//    &TRISDSET, &TRISDSET, &TRISDSET, &TRISFSET, &TRISFSET, &TRISGSET, &TRISFSET, &TRISFSET};
//
//static volatile unsigned int * const LED_LATCLR[] = {&LATECLR, &LATDCLR, &LATDCLR, &LATDCLR,
//    &LATDCLR, &LATDCLR, &LATDCLR, &LATFCLR, &LATFCLR, &LATGCLR, &LATFCLR, &LATFCLR};
//
//static volatile unsigned int * const LED_LATSET[] = {&LATESET, &LATDSET, &LATDSET, &LATDSET,
//    &LATDSET, &LATDSET, &LATDSET, &LATFSET, &LATFSET, &LATGSET, &LATFSET, &LATFSET};
//
//static volatile unsigned int * const LED_LAT[] = {&LATE, &LATD, &LATD, &LATD,
//    &LATD, &LATD, &LATD, &LATF, &LATF, &LATG, &LATF, &LATF};
//
//static unsigned short int LED_bitsMap[] = {BIT_7, BIT_5, BIT_10, BIT_11, BIT_3, BIT_6, BIT_7, BIT_6, BIT_4, BIT_6, BIT_5, BIT_1};
//
////static unsigned short int LED_ShiftAmount[] = {7, 5, 10, 11, 3, 6, 7, 6, 4, 6, 5, 1};


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                           *
 ******************************************************************************/

/**
 * @Function Robot_Init(void)
 * @param None.
 * @return None.
 * @brief  Performs all the initialization necessary for the roach. this includes initializing 
 * the PWM module, the A/D converter, the data directions on some pins, and 
 * setting the initial motor directions.
 * @note  None.
 * @author Max Dunne, 2012.01.06 */
void Robot_Init(void) {

    // set up tape sensors
    TAPE_SENSOR_1_TRIS = INPUT;
    TAPE_SENSOR_2_TRIS = INPUT;
    TAPE_SENSOR_3_TRIS = INPUT;
    TAPE_SENSOR_4_TRIS = INPUT;
    TAPE_SENSOR_5_TRIS = INPUT;
    TAPE_SENSOR_6_TRIS = INPUT;
    
    BEACON_TRIS = INPUT;
    
    TAPE_SENSOR_1 = 0;
    TAPE_SENSOR_2 = 0;
    TAPE_SENSOR_3 = 0;
    TAPE_SENSOR_4 = 0;
    TAPE_SENSOR_5 = 0;
    TAPE_SENSOR_6 = 0;

    //set the control pins for the motors
    PWM_Init();
    PWM_SetFrequency(1000);
    PWM_AddPins(LEFT_PWM | RIGHT_PWM);


    IO_PortsSetPortOutputs(PORTW, PIN5);

    LEFT_DIR_TRIS = 0;
    LEFT_DIR_INV_TRIS = 0;
    RIGHT_DIR_TRIS = 0;
    RIGHT_DIR_INV_TRIS = 0;
    LEFT_DIR = 0;
    LEFT_DIR_INV = ~LEFT_DIR;
    RIGHT_DIR = 0;
    RIGHT_DIR_INV = ~RIGHT_DIR;

    //set up the hall effect sensors
    HALL_FRONT_LEFT_TRIS = 1;
    HALL_FRONT_RIGHT_TRIS = 1;
    HALL_REAR_RIGHT_TRIS = 1;
    HALL_REAR_LEFT_TRIS = 1;
    BACK_BUMPER_TRIS = 1;


    //set up the light bank

    //    uint8_t CurPin;
    //    for (CurPin = 0; CurPin < NUMLEDS; CurPin++) {
    //        LED_SetPinOutput(CurPin);
    //        LED_Off(CurPin);
    //    }

    //while (1);

    //Initialize the light sensor
    AD_AddPins(AD_PORTV6);
    AD_Init();
    //    printf("Current pins: %d\n",AD_ActivePins());
    //    printf("Add Result: %d\n",AD_AddPins(LIGHT_SENSOR));
    //    while(1);
    //    AD_AddPins(LIGHT_SENSOR);

    //enable interrupts


}

/**
 * @Function Robot_LeftMtrSpeed(char newSpeed)
 * @param newSpeed - A value between -100 and 100 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @author Max Dunne, 2012.01.06 */
char Robot_LeftMtrSpeed(char newSpeed) {
    if ((newSpeed < -ROBOT_MAX_SPEED) || (newSpeed > ROBOT_MAX_SPEED)) {
        return (ERROR);
    }
    newSpeed = -newSpeed;

    if (newSpeed < 0) {
        LEFT_DIR = 0;
        newSpeed = newSpeed * (-1); // set speed to a positive value
    } else {
        LEFT_DIR = 1;
    }
    LEFT_DIR_INV = ~(LEFT_DIR);
    if (PWM_SetDutyCycle(LEFT_PWM, newSpeed * (MAX_PWM / ROBOT_MAX_SPEED)) == ERROR) {
        //printf("ERROR: setting channel 1 speed!\n");
        return (ERROR);
    }
    return (SUCCESS);
}

/**
 * @Function Robot_RightMtrSpeed(char newSpeed)
 * @param newSpeed - A value between -100 and 100 which is the new speed
 * @param of the motor. 0 stops the motor. A negative value is reverse.
 * @return SUCCESS or ERROR
 * @brief  This function is used to set the speed and direction of the left motor.
 * @author Max Dunne, 2012.01.06 */
char Robot_RightMtrSpeed(char newSpeed) {
    if ((newSpeed < -ROBOT_MAX_SPEED) || (newSpeed > ROBOT_MAX_SPEED)) {
        return (ERROR);
    }
    if (newSpeed < 0) {
        RIGHT_DIR = 0;
        newSpeed = newSpeed * (-1); // set speed to a positive value
    } else {
        RIGHT_DIR = 1;
    }
    RIGHT_DIR_INV = ~(RIGHT_DIR);
    if (PWM_SetDutyCycle(RIGHT_PWM, newSpeed * (MAX_PWM / ROBOT_MAX_SPEED)) == ERROR) {
        //puts("\aERROR: setting channel 1 speed!\n");
        return (ERROR);
    }
    return (SUCCESS);
}

/**
 * @Function Robot_LightLevel(void)
 * @param None.
 * @return a 10-bit value corresponding to the amount of light received.
 * @brief  Returns the current light level. A higher value means less light is detected.
 * @author Max Dunne, 2012.01.06 */
//unsigned int Robot_LightLevel(void) {
//    return AD_ReadADPin(LIGHT_SENSOR);
//}

/**
 * @Function Robot_BatteryVoltage(void)
 * @param None.
 * @return a 10-bit value corresponding to the current voltage of the roach
 * @brief  returns a 10:1 scaled value of the roach battery level
 * @author Max Dunne, 2013.07.12 */
//unsigned int Robot_BatteryVoltage(void) {
//    return AD_ReadADPin(ROBOT_BAT_VOLTAGE);
//}

/**
 * @Function Robot_ReadFrontLeftBumper(void)
 * @param None.
 * @return BUMPER_TRIPPED or BUMPER_NOT_TRIPPED
 * @brief  Returns the state of the front left bumper
 * @author Max Dunne, 2012.01.06 */
unsigned char Robot_ReadFrontLeftBumper(void) {
    return !HALL_FRONT_LEFT;
}

/**
 * @Function Robot_ReadFrontRightBumper(void)
 * @param None.
 * @return BUMPER_TRIPPED or BUMPER_NOT_TRIPPED
 * @brief  Returns the state of the front right bumper
 * @author Max Dunne, 2012.01.06 */
unsigned char Robot_ReadFrontRightBumper(void) {
    return !HALL_FRONT_RIGHT;
}

/**
 * @Function Robot_ReadRearLeftBumper(void)
 * @param None.
 * @return BUMPER_TRIPPED or BUMPER_NOT_TRIPPED
 * @brief  Returns the state of the rear left bumper
 * @author Max Dunne, 2012.01.06 */
unsigned char Robot_ReadRearLeftBumper(void) {
    return !HALL_REAR_LEFT;
}

/**
 * @Function Robot_ReadRearRightBumper(void)
 * @param None.
 * @return BUMPER_TRIPPED or BUMPER_NOT_TRIPPED
 * @brief  Returns the state of the rear right bumper
 * @author Max Dunne, 2012.01.06 */
//unsigned char Robot_ReadRearRightBumper(void) {
//    return !HALL_REAR_RIGHT;
//}

/**
 * @Function Robot_ReadBumpers(void)
 * @param None.
 * @return 4-bit value representing all four bumpers in following order: front left,front right, rear left, rear right
 * @brief  Returns the state of all 4 bumpers
 * @author Max Dunne, 2012.01.06 */
unsigned char Robot_ReadBumpers(void) {
    //unsigned char bump_state;
    //bump_state = (!HALL_FRONT_LEFT + ((!HALL_FRONT_RIGHT) << 1)+((!HALL_REAR_LEFT) << 2)+((!HALL_REAR_RIGHT) << 3));
       // return (!HALL_FRONT_LEFT + ((!HALL_FRONT_RIGHT) << 1)+((!HALL_REAR_LEFT) << 2)+((!HALL_REAR_RIGHT) << 3));
    return (!HALL_FRONT_LEFT + ((!HALL_FRONT_RIGHT) << 1) + ((!HALL_REAR_LEFT) << 2) + ((!BACK_BUMPER) << 3));
}

/**
 * @Function Robot_LEDSSet( unsigned char pattern)
 * @param pattern - sets LEDs on (1) or off (0) as in the pattern.
 * @return SUCCESS or ERROR
 * @brief  Forces the LEDs in (bank) to on (1) or off (0) to match the pattern.
 * @author Gabriel Hugh Elkaim, 2011.12.25 01:16 Max Dunne 2015.09.18 */
//char Robot_LEDSSet(uint16_t pattern) {
//    char i;
//    for (i = 0; i < NUMLEDS; i++) {
//        if (pattern & (1 << i)) {
//            LED_On(i);
//        } else {
//            LED_Off(i);
//        }
//    }
//    return SUCCESS;
//}

/**
 * @Function Robot_LEDSGet(void)
 * @return uint16_t: ERROR or state of BANK
 * @author Max Dunne, 203.10.21 01:16 2015.09.18 */
//uint16_t Robot_LEDSGet(void) {
//    uint16_t LEDStatus = 0;
//    int8_t i;
//    for (i = (NUMLEDS - 1); i >= 0; i--) {
//        LEDStatus |= !LED_Get(i);
//        LEDStatus <<= 1;
//        //        printf("%d\t",i);
//    }
//    LEDStatus >>= 1;
//    return LEDStatus;
//    return 0;
//}

/**
 * @Function Robot_BarGraph(uint8_t Number)
 * @param Number - value to light between 0 and 12 leds
 * @return SUCCESS or ERROR
 * @brief  allows all leds to be used as a bar graph
 * @author  Max Dunne 2015.09.18 */


//char Robot_BarGraph(uint8_t Number) {
//    if (Number > NUMLEDS) {
//        return ERROR;
//    }
//    uint16_t Pattern = 0;
//    uint8_t iterations;
//
//    for (iterations = 0; iterations < Number; iterations++) {
//        Pattern <<= 1;
//        Pattern |= 1;
//    }
//    Robot_LEDSSet(Pattern);
//    return SUCCESS;
//}

uint8_t goForward(void) {
    //something here to make the bot go forward at full speed
    Robot_LeftMtrSpeed(FWD_speed);
    Robot_RightMtrSpeed(FWD_speed-RIGHT_WHEEL_OFFSET);

    return 0; //this could be used to indicated true or false. Not necessary tho. 
}


uint8_t turnBot(char leftSpeed, char rightSpeed) {
    //turn bot
    Robot_LeftMtrSpeed(leftSpeed);
    Robot_RightMtrSpeed(rightSpeed-RIGHT_WHEEL_OFFSET);
    return 0;
}

uint8_t stop(void) { //one concern - if the gearhead is too powerful we may need to slow down first
    //stop the bot
    Robot_LeftMtrSpeed(STOP_speed);
    Robot_RightMtrSpeed(STOP_speed);


    return 0;
}

unsigned char Robot_ReadTapeSensors(void) {
    //unsigned char bump_state;
    //bump_state = (!HALL_FRONT_LEFT + ((!HALL_FRONT_RIGHT) << 1)+((!HALL_REAR_LEFT) << 2)+((!HALL_REAR_RIGHT) << 3));
//    return (TAPE_SENSOR_1 + ((TAPE_SENSOR_2) << 1)+((TAPE_SENSOR_3) << 2)
//            +((TAPE_SENSOR_4) << 3)+((TAPE_SENSOR_5) << 4)+((TAPE_SENSOR_6) << 5));
    return (TAPE_SENSOR_1 + ((TAPE_SENSOR_2) << 1)+((TAPE_SENSOR_3) << 2)
            +((TAPE_SENSOR_4) << 3));
}

//#define ROBOT_TEST
//#ifdef ROBOT_TEST

uint32_t Robot_ReadTrackWire(void) {
    //according to our design, this should return a value from the ADC to indicate the distance
    return AD_ReadADPin(TRACK_WIRE_PIN);
}

uint8_t Robot_ReadBeaconSensor(void) {
    //Assuming that this should return a value from the ADC to indicate the distance
    //return AD_ReadADPin(BEACON_PIN);
    //HZ 11/19 - now we use the IO ports
    return BEACON_PIN;
}

uint8_t Robot_ReadPingSensor(void) {
    return PING_PIN;
}

uint8_t Robot_ReadPingTrigger(void) {
    return PING_TRIG;
}

uint8_t Robot_TrigPingSensor(uint8_t trig) {
    IO_PortsWritePort(PORTW, PIN5 * trig); //PIN4
    return 0;
}

int Robot_SetServoSpeed(unsigned short int pulseTime){
    RC_SetPulseTime(SHOOTER_SERVO, pulseTime);
    return 0;
}

//#define ROBOT_TEST
#ifdef ROBOT_TEST
#pragma config FPLLIDIV 	= DIV_2		//PLL Input Divider
#pragma config FPLLMUL 		= MUL_20	//PLL Multiplier
#pragma config FPLLODIV 	= DIV_1 	//System PLL Output Clock Divid
#pragma config FNOSC 		= PRIPLL	//Oscillator Selection Bits
#pragma config FSOSCEN 		= OFF		//Secondary Oscillator Enable
#pragma config IESO 		= OFF		//Internal/External Switch O
#pragma config POSCMOD 		= XT		//Primary Oscillator Configuration
#pragma config OSCIOFNC 	= OFF		//CLKO Output Signal Active on the OSCO Pin
#pragma config FPBDIV 		= DIV_2		//Peripheral Clock Divisor
#pragma config FCKSM 		= CSECMD	//Clock Switching and Monitor Selection
#pragma config WDTPS 		= PS1		//Watchdog Timer Postscaler
#pragma config FWDTEN		= OFF		//Watchdog Timer Enable
#pragma config ICESEL		= ICS_PGx2	//ICE/ICD Comm Channel Select
#pragma config PWP 			= OFF		//Program Flash Write Protect
#pragma config BWP 			= OFF		//Boot Flash Write Protect bit
#pragma config CP 			= OFF		//Code Protect

#include <stdio.h>

//#define WANDER_MODE
#define WANDER_SAMPLE_RATE 100

#define FLEFT_BUMP_MASK (1)
#define FRIGHT_BUMP_MASK (1<<1)
#define RLEFT_BUMP_MASK (1<<2)
#define RRIGHT_BUMP_MASK (1<<3)

#define DELAY(x)    for (wait = 0; wait <= x; wait++) {asm("nop");}
#define A_BIT       18300
#define A_BIT_MORE  36600
#define YET_A_BIT_LONGER (A_BIT_MORE<<2)
#define A_LOT       183000
#define NUM_TIMES_REPEAT_LED 5
#define MOTOR_TIME (A_LOT<<2)

#define LOW_BAT 263
#define HIGH_BAT 310



#include <roach.h>

void FlashLEDBar(uint8_t numtimes);

int main(void) {
    BOARD_Init();
    Robot_Init();

    unsigned int wait;
    unsigned int i, j;
    unsigned int scaledValue;
    int motorSpeed;
    printf("\r\nWelcome the the ECE118 Robot Test Harness");
    printf("\r\nThis code will allow someone to confirm operational hardware and software of a Robot");
    //  TEST THE LEDS
    for (i = 0; i < NUM_TIMES_REPEAT_LED; i++) {
        for (j = 0; j < NUMLEDS; j++) {
            Robot_LEDSSet(1 << j);
            DELAY(A_BIT_MORE);
        }
        Robot_LEDSSet(0);
        DELAY(A_BIT_MORE);
    }
    Robot_LEDSSet(0x555);
    DELAY(YET_A_BIT_LONGER);
    for (i = 0; i < NUM_TIMES_REPEAT_LED; i++) {
        Robot_LEDSSet(Robot_LEDSGet()^0xFFF); // toggle bits on LED
        DELAY(YET_A_BIT_LONGER);
    }
    Robot_LEDSSet(0);
    printf("\r\nTo test a roach, click a bumper.  Each bumper runs a specific test.");
    printf("\r\n\tFront Left: display the current battery voltage");
    printf("\r\n\tFront Right: Display the Light level live");
    printf("\r\n\tRear Left: Test left motor");
    printf("\r\n\tRear Right: Test right motor");
    while (1) {
        // wait for bumper press
        switch (Robot_ReadBumpers()) {

            case FLEFT_BUMP_MASK: // Battery Voltage live output
                FlashLEDBar(1);
                DELAY(A_LOT);
                scaledValue = Robot_BatteryVoltage();
                printf("\r\nBattery voltage is %d", scaledValue);
                scaledValue -= LOW_BAT;
                scaledValue *= 12;
                scaledValue /= (HIGH_BAT - LOW_BAT);
                Robot_BarGraph(scaledValue);
                DELAY(A_LOT << 2);
                Robot_LEDSSet(0);
                printf("\r\nBattery Level Test Complete");
                DELAY(A_BIT);
                FlashLEDBar(1);
                break;

            case FRIGHT_BUMP_MASK: // Light Sensor live output
                FlashLEDBar(2);
                DELAY(A_LOT);
                for (i = 0; i < A_LOT >> 2; i++) {
                    scaledValue = Robot_LightLevel();
                    if (i % 10000 == 0) {
                        printf("\r\nCurrent Light Level: %d", scaledValue);
                    }
                    scaledValue *= 12;
                    scaledValue /= 1023;
                    Robot_BarGraph(scaledValue);
                }
                printf("\r\nLight Level Test Complete");
                DELAY(A_LOT);
                FlashLEDBar(2);
                break;

            case RLEFT_BUMP_MASK: // Left motor progression
                FlashLEDBar(3);
                motorSpeed = 100;
                DELAY(A_LOT);
                printf("\r\nLeft Motor at %d", motorSpeed);
                Robot_LeftMtrSpeed(motorSpeed);
                Robot_LEDSSet(0b111100000000);
                DELAY(MOTOR_TIME);
                motorSpeed -= 20;
                printf("\r\nLeft Motor at %d", motorSpeed);
                Robot_LeftMtrSpeed(motorSpeed);
                Robot_LEDSSet(0b011100000000);
                DELAY(MOTOR_TIME);
                motorSpeed -= 20;
                printf("\r\nLeft Motor at %d", motorSpeed);
                Robot_LeftMtrSpeed(motorSpeed);
                Robot_LEDSSet(0b001100000000);
                DELAY(MOTOR_TIME);
                motorSpeed -= 20;
                printf("\r\nLeft Motor at %d", motorSpeed);
                Robot_LeftMtrSpeed(motorSpeed);
                Robot_LEDSSet(0b000100000000);
                DELAY(MOTOR_TIME);
                motorSpeed = 0;
                printf("\r\nLeft Motor at %d", motorSpeed);
                Robot_LeftMtrSpeed(motorSpeed);
                Robot_LEDSSet(0);
                DELAY(MOTOR_TIME);
                motorSpeed = -100;
                printf("\r\nLeft Motor at %d", motorSpeed);
                Robot_LeftMtrSpeed(motorSpeed);
                Robot_LEDSSet(0b1111);
                DELAY(MOTOR_TIME);
                motorSpeed += 20;
                printf("\r\nLeft Motor at %d", motorSpeed);
                Robot_LeftMtrSpeed(motorSpeed);
                Robot_LEDSSet(0b0111);
                DELAY(MOTOR_TIME);
                motorSpeed += 20;
                printf("\r\nLeft Motor at %d", motorSpeed);
                Robot_LeftMtrSpeed(motorSpeed);
                Robot_LEDSSet(0b0011);
                DELAY(MOTOR_TIME);
                motorSpeed += 20;
                printf("\r\nLeft Motor at %d", motorSpeed);
                Robot_LeftMtrSpeed(motorSpeed);
                Robot_LEDSSet(0b0001);
                DELAY(MOTOR_TIME);
                motorSpeed = 0;
                printf("\r\nLeft Motor at %d", motorSpeed);
                Robot_LeftMtrSpeed(motorSpeed);
                Robot_LEDSSet(0);
                DELAY(A_LOT);
                printf("\r\nLeft Motor Test Complete");
                FlashLEDBar(3);
                break;

            case RRIGHT_BUMP_MASK:
                FlashLEDBar(4);
                DELAY(A_LOT);
                motorSpeed = 100;
                printf("\r\nRight Motor at %d", motorSpeed);
                Robot_RightMtrSpeed(motorSpeed);
                Robot_LEDSSet(0b111100000000);
                DELAY(MOTOR_TIME);
                motorSpeed -= 20;
                printf("\r\nRight Motor at %d", motorSpeed);
                Robot_RightMtrSpeed(motorSpeed);
                Robot_LEDSSet(0b011100000000);
                DELAY(MOTOR_TIME);
                motorSpeed -= 20;
                printf("\r\nRight Motor at %d", motorSpeed);
                Robot_RightMtrSpeed(motorSpeed);
                Robot_LEDSSet(0b001100000000);
                DELAY(MOTOR_TIME);
                motorSpeed -= 20;
                printf("\r\nRight Motor at %d", motorSpeed);
                Robot_RightMtrSpeed(motorSpeed);
                Robot_LEDSSet(0b000100000000);
                DELAY(MOTOR_TIME);
                motorSpeed = 0;
                printf("\r\nRight Motor at %d", motorSpeed);
                Robot_RightMtrSpeed(motorSpeed);
                Robot_LEDSSet(0);
                DELAY(MOTOR_TIME);
                motorSpeed = -100;
                printf("\r\nRight Motor at %d", motorSpeed);
                Robot_RightMtrSpeed(-100);
                Robot_LEDSSet(0b1111);
                DELAY(MOTOR_TIME);
                motorSpeed += 20;
                printf("\r\nRight Motor at %d", motorSpeed);
                Robot_RightMtrSpeed(motorSpeed);
                Robot_LEDSSet(0b0111);
                DELAY(MOTOR_TIME);
                motorSpeed += 20;
                printf("\r\nRight Motor at %d", motorSpeed);
                Robot_RightMtrSpeed(motorSpeed);
                Robot_LEDSSet(0b0011);
                DELAY(MOTOR_TIME);
                motorSpeed += 20;
                printf("\r\nRight Motor at %d", motorSpeed);
                Robot_RightMtrSpeed(motorSpeed);
                Robot_LEDSSet(0b0001);
                DELAY(MOTOR_TIME);
                motorSpeed = 0;
                printf("\r\nRight Motor at %d", motorSpeed);
                Robot_RightMtrSpeed(motorSpeed);
                Robot_LEDSSet(0);
                DELAY(A_LOT);
                printf("\r\nRight Motor Test Complete");
                FlashLEDBar(4);
                break;
        }
        // Left motor progression
        // right motor progression


    }
    while (1);
}

void FlashLEDBar(uint8_t numtimes) {
    unsigned int wait, i;
    Robot_LEDSSet(0);
    for (i = 0; i < numtimes; i++) {
        Robot_LEDSSet(0xFFF);
        DELAY(YET_A_BIT_LONGER);
        Robot_LEDSSet(0x000);
        DELAY(YET_A_BIT_LONGER);
    }
}
#endif