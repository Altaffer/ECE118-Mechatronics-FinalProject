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



#define DELAY_MULTIPLIER 1000
#define DELAY(x)    for (wait = 0; wait <= (DELAY_MULTIPLIER * x); wait++) {asm("nop");}
#define DELAY_LOOP_TIME 10 // ms


//#define FREQ_TEST
// </editor-fold>


/*
 * 
 */

uint8_t goForward(void) {
    //something here to make the bot go forward at full speed
    Robot_LeftMtrSpeed(FWD_speed);
    Robot_RightMtrSpeed(FWD_speed);
    
}
int main(void) {
    BOARD_Init();
    SERIAL_Init();
    Robot_Init();
    PWM_Init();
    int currentTapeValue = 0;
    
    PORTX03_TRIS = INPUT;
    while(1){
        goForward();
    }
    
    
}