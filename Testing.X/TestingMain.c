/* 
 * File:   TestingMain.c
 * Author: eappleto
 *
 * Created on November 12, 2021, 7:29 PM
 */


#include "xc.h"
#include "BOARD.h"
#include "AD.h"
#include "serial.h"
#include "robot.h"
#include "pwm.h"
#include "RC_Servo.h"
#include <stdio.h>
#include <stdlib.h>
#include "IO_Ports.h"
#include "timers.h"


// <editor-fold defaultstate="collapsed" desc="#DEFINES"> 
#define INPUT  1
#define OUTPUT 0
#define HIGH   1
#define LOW    0
#define POT_PIN AD_PORTV8         // use V-08 for pot
//#define TAPE_SENSOR_1 PORTX03_BIT;
//#define TAPE_SENSOR_2 PORTX05_BIT
#define BEACON_PIN PORTX10_BIT
#define PING_PIN PORTX9_BIT
#define SERVO_PIN RC_PORTW08


#define DELAY_MULTIPLIER 1000
#define DELAY(x)    for (int wait = 0; wait <= (DELAY_MULTIPLIER * x); wait++) {asm("nop");}
#define DELAY_LOOP_TIME 2000 // ms

// TEST DEFINES
//#define MOTOR_TEST
//#define BUMPER_TEST
//#define BUMPER_TEST
#define TAPE_SENSOR_TEST
//#define BEACON_TEST
//#define SERVO_TEST
//#define SERVO_TEST
//#define PING_SENSOR_TEST


//#define FREQ_TEST
// </editor-fold>

/*
 * 
 */
uint8_t goForward(void) {
    //something here to make the bot go forward at full speed
    Robot_LeftMtrSpeed(FWD_speed);
    Robot_RightMtrSpeed(FWD_speed);
    //    DELAY(DELAY_LOOP_TIME);
    //    Robot_LeftMtrSpeed(0);
    //    DELAY(DELAY_LOOP_TIME);
    //    Robot_RightMtrSpeed(FWD_speed);
}

int main(void) {


    BOARD_Init();
    SERIAL_Init();
    Robot_Init();
    PWM_Init();
    TIMERS_Init();
    RC_Init();
    RC_AddPins(SERVO_PIN);
    int currentTapeValue1 = 0;
    int currentTapeValue2 = 0;
    uint8_t tapeSensorParam = 0;
    uint8_t currentBumperValue = 0;
    int currentBeaconValue = 0;

    //HZ 11/19 - testing code for beacon detector - IO ports X10
    IO_PortsSetPortInputs(PORTX, PIN10);
    //    PORTX03_TRIS = INPUT;
    //    PORTX05_TRIS = INPUT;
    PORTX10_TRIS = INPUT;
    PORTV06_LAT = HIGH; // enable for DC motor

    while (1) {
#ifdef TAPE_SENSOR_TEST
        //        currentTapeValue1 = TAPE_SENSOR_1;
        //        currentTapeValue2 = TAPE_SENSOR_2;
        //        printf("\nTape Sensor Value 1 = %d \n\r", currentTapeValue1);
        //        printf("\nTape Sensor Value 2 = %d \n\r", currentTapeValue2);
        tapeSensorParam = Robot_ReadTapeSensors();
        printf("\nTape Sensor Param = %d \n\r", tapeSensorParam);

#endif
#ifdef MOTOR_TEST
        goForward();
#endif
#ifdef BUMPER_TEST
        currentBumperValue = Robot_ReadBumpers();
        printf("\nBumper Value = %d \n\r", currentBumperValue);
        if (currentBumperValue == 1) {
            Robot_LeftMtrSpeed(FWD_speed);
            DELAY(DELAY_LOOP_TIME);
            Robot_LeftMtrSpeed(0);
        } else if (currentBumperValue == 2) {
            Robot_RightMtrSpeed(FWD_speed);
            DELAY(DELAY_LOOP_TIME);
            Robot_RightMtrSpeed(0);
        } else if (currentBumperValue == 3) {
            Robot_LeftMtrSpeed(FWD_speed);
            Robot_RightMtrSpeed(FWD_speed);
            DELAY(DELAY_LOOP_TIME);
            Robot_LeftMtrSpeed(BCKWD_speed);
            Robot_RightMtrSpeed(BCKWD_speed);
            DELAY(DELAY_LOOP_TIME);
            Robot_LeftMtrSpeed(0);
            Robot_RightMtrSpeed(0);
        }
#endif
#ifdef BEACON_TEST
        currentBeaconValue = BEACON_PIN;
        //printf("\nBeacon Detector Value = %d \n\r", currentBeaconValue);
        printf("\nBeacon %d \n\r", currentBeaconValue); //BEACON working -HZ 11/19
#endif
#ifdef SERVO_TEST
        RC_SetPulseTime(SERVO_PIN, 1550);
        currentBumperValue = Robot_ReadRearLeftBumper();
        printf("\nSwitch Value = %d \n\r", currentBumperValue);
#endif
    }

}