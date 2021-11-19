/* 
 * File:   TestingMain.c
 * Author: eappleto
 *
 * Created on November 12, 2021, 7:29 PM
 */


#include "xc.h"
#include "BOARD.h"
#include "AD.h"
#include "LED.h"
#include "serial.h"
#include "robot.h"
#include "pwm.h"
#include "RC_Servo.h"
#include <stdio.h>
#include <stdlib.h>
#include "IO_Ports.h"


// <editor-fold defaultstate="collapsed" desc="#DEFINES"> 
#define INPUT  1
#define OUTPUT 0
#define HIGH   1
#define LOW    0
#define POT_PIN AD_PORTV8         // use V-08 for pot
#define TAPE_SENSOR_1 PORTX03_BIT
#define BEACON_PIN PORTX10_BIT
#define SERVO_PIN RC_PORTW08


#define DELAY_MULTIPLIER 1000
#define DELAY(x)    for (int wait = 0; wait <= (DELAY_MULTIPLIER * x); wait++) {asm("nop");}
#define DELAY_LOOP_TIME 1000 // ms

// TEST DEFINES
#define MOTOR_TEST
//#define BUMPER_TEST
//#define TAPE_SENSOR_TEST
//#define BEACON_TEST
//#define SERVO_TEST

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
    RC_Init();
    RC_AddPins(SERVO_PIN);
    int currentTapeValue = 0;
    int currentBumperValue = 0;
    int currentBeaconValue = 0;

    PORTX03_TRIS = INPUT;
    PORTX10_TRIS = INPUT;
    PORTV06_LAT = HIGH;  // enable for DC motor

    while (1) {
#ifdef TAPE_SENSOR_TEST
        currentTapeValue = TAPE_SENSOR_1;
        printf("\nTape Sensor Value = %d \n\r", currentTapeValue);
#endif
#ifdef MOTOR_TEST
        goForward();
#endif
#ifdef BUMPER_TEST
        currentBumperValue = Robot_ReadFrontLeftBumper();
        printf("\nBumper Value = %d \n\r", currentBumperValue);
#endif
#ifdef BEACON_TEST
        currentBeaconValue = BEACON_PIN;
        printf("\nBeacon Detector Value = %d \n\r", currentBeaconValue);
#endif
#ifdef SERVO_TEST
        RC_SetPulseTime(SERVO_PIN, 1550);
#endif
    }

}