#include <BOARD.h>
#include <xc.h>
#include <stdio.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "ES_Timers.h"

#include <stdlib.h>
#include "IO_Ports.h"
#include "AD.h"
#include "LED.h"
#include "pwm.h"
#include "RC_Servo.h"
#include "serial.h"
#include "timers.h"
#include "robot.h"
#include "RC_Servo.h"

// define
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

//define this if using the test harnesses - ES_run will not be called

#define TEST_HARNESSES

#ifdef TEST_HARNESSES
#include "PingService.h"

#define RIGHT 10
#define LEFT 01
#define BOTH 11
#define NONE 0
#define PRIORITY 5 //dummy

#endif

uint8_t test_motors(void);
uint8_t test_servo(void);
uint8_t test_something(void);
uint8_t test_tapeSensors(void);

void main(void) {
    ES_Return_t ErrorType;

    BOARD_Init();




    printf("Test Main Started\r\n");


    // Your hardware initialization function calls go here
    AD_Init();
    LED_Init();
    PWM_Init();
    SERIAL_Init();
    Robot_Init();
    ES_Timer_Init();
    TIMERS_Init();
    RC_Init();

    //RC_AddPins(SERVO_PIN);
#ifdef TEST_HARNESSES
    // Test harnesses
    InitPingService(PRIORITY);
    uint8_t bumpers;
    while (1) {
        DELAY(DELAY_LOOP_TIME);
        bumpers = Robot_ReadBumpers();

        switch (bumpers) {
                /* run LED sequence once*/
            case BOTH:
                test_motors();
                break;

            case RIGHT:
                test_servo();
                break;

            case LEFT:
                test_something();
                DELAY(DELAY_LOOP_TIME);
                test_tapeSensors();
                //press for a while
                //this will:
                // print something from the Ping Sensor
                break;
            default:
                break;
        }


    }
#endif
    // The following code is used to test the es framework
    // now initialize the Events and Services Framework and start it running
    ErrorType = ES_Initialize();
    if (ErrorType == Success) {
        ErrorType = ES_Run();
    }
    //if we got to here, there was an error
    switch (ErrorType) {
        case FailedPointer:
            printf("Failed on NULL pointer");
            break;
        case FailedInit:
            printf("Failed Initialization");
            break;
        default:
            printf("Other Failure: %d", ErrorType);
            break;
    }
    for (;;)
        ;

};

uint8_t test_motors(void) {
    Robot_LeftMtrSpeed(100);
    Robot_RightMtrSpeed(100);
    printf("both max speed\r\n");
    DELAY(DELAY_MULTIPLIER);
    Robot_RightMtrSpeed(20);
    DELAY(DELAY_MULTIPLIER);
    Robot_LeftMtrSpeed(20);
    printf("both 20 speed\r\n");
    DELAY(DELAY_MULTIPLIER);
    Robot_LeftMtrSpeed(0);
    Robot_RightMtrSpeed(0);
    printf("stop\r\n");
    DELAY(DELAY_MULTIPLIER);
    Robot_LeftMtrSpeed(-100);
    Robot_RightMtrSpeed(-100);
    printf("both -max speed\r\n");
    DELAY(DELAY_MULTIPLIER);
    Robot_RightMtrSpeed(-20);
    DELAY(DELAY_MULTIPLIER);
    Robot_LeftMtrSpeed(-20);
    printf("both -20 speed\r\n");
    DELAY(DELAY_MULTIPLIER);
    Robot_LeftMtrSpeed(0);
    Robot_RightMtrSpeed(0);
    return 0;
}

uint8_t test_servo(void) {
    uint8_t currentSwitchValue = 0;
    RC_SetPulseTime(SERVO_PIN, 1525);
    currentSwitchValue = Robot_ReadRearLeftBumper();
    printf("\nShooter Switch Value = %d \n\r", currentSwitchValue);
    ;
}

uint8_t test_something(void) {

    //This part reassembles ping service and ping event checker
    Robot_TrigPingSensor(1); //W05
    DELAY(1);
    Robot_TrigPingSensor(0); //a manual pulse
    uint32_t start_time = 0;
    uint16_t elapse_time = 0;
    while (!Robot_ReadPingSensor()); //wait for it to go high
    start_time = TIMERS_GetTime();
    while (Robot_ReadPingSensor()); //wait for it to go low
    elapse_time = (TIMERS_GetTime() - start_time)*100;
    printf("Ping Sensor: %d us\r\n", elapse_time);
    return 0;

}

uint8_t test_tapeSensors(void) {
    uint8_t currentTapeValue = 0;
    currentTapeValue = Robot_ReadTapeSensors();
    printf("\nTape Sensors Param Value = %d \n\r", currentTapeValue);
    return 0;
}
/*------------------------------- Footnotes -------------------------------*/
/*------------------------------ End of file ------------------------------*/
