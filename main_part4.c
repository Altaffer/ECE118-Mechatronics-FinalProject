/*
 * File:   main_part4.c
 * Author: zzhan247
 *
 * Created on October 27, 2021, 6:27 PM
 * bidirectional DC motor
 */


#include <BOARD.h>
#include <stdio.h>
#include <stdlib.h>
#include "IO_Ports.h"
#include "AD.h"

#include "LED.h"
#include "pwm.h"
#include "RC_Servo.h"
#include "serial.h"
#include "timers.h"
#include "xc.h"

#define TW_UPPER_BOUND 450
#define TW_LOWER_BOUND 200
#define TAKE_PREV

uint32_t TrackWireEventChecker(void);

int main(void) {
    BOARD_Init();
    printf("test\r\n");

    AD_Init();
    LED_Init();
    PWM_Init();
    //SERIAL_Init();

    PWM_AddPins(PWM_PORTY10);
    AD_AddPins(AD_PORTV3);

    PWM_SetFrequency(MAX_PWM_FREQ);
    IO_PortsSetPortDirection(PORTZ, 0);
    IO_PortsSetPortInputs(PORTZ, PIN3);
    IO_PortsSetPortOutputs(PORTZ, PIN4);
    IO_PortsSetPortOutputs(PORTZ, PIN5);

    LED_AddBanks(LED_BANK2);
    LED_AddBanks(LED_BANK3);
    LED_AddBanks(LED_BANK1);

    float parts = 0.0;
    int rotate = 0;
    uint8_t b1 = 0;
    uint8_t b2 = 0;
    uint8_t b3 = 0;
    uint8_t swi = 0;

    while (1) {

        swi = IO_PortsReadPort(PORTZ) & PIN3;

        //swi is 1000 when on, so shift 2 left is Pin5. Trying to make the code simple
        IO_PortsWritePort(PORTZ, (swi << 2) | ((swi == 0) << 4));


        parts = (float) AD_ReadADPin(AD_PORTV3) / 1023.0;
        TrackWireEventChecker();
        rotate = (int) (parts * 1000.0);
        parts = parts * 12.0;
        b1 = (parts > 0) | ((parts > 1) << 1) | ((parts > 2) << 2) | ((parts > 3) << 3);
        b2 = (parts > 4) | ((parts > 5) << 1) | ((parts > 6) << 2) | ((parts > 7) << 3);
        b3 = (parts > 8) | ((parts > 9) << 1) | ((parts > 10) << 2) | ((parts > 11) << 3);
        LED_SetBank(LED_BANK1, swi ? b1 : b3);
        LED_SetBank(LED_BANK2, b3);
        LED_SetBank(LED_BANK3, swi ? b2 : b1);

        PWM_SetDutyCycle(PWM_PORTY10, rotate);
        //rotate = IO_PortsReadPort(PORTZ);



        
        //printf("%d\r\n", RC_BASE + AD_ReadADPin(AD_PORTV3));
    }


    return 0;
}

uint32_t TrackWireEventChecker(void) {
    static int lastEvent = 0; 
    // Setting a value because currentEvent would be initialized to some random 
    // value. 
    int currentEvent = lastEvent;
    int thisEvent;
    uint8_t returnVal = FALSE;
    uint32_t TrackWireInput = AD_ReadADPin(AD_PORTV3);
    static uint8_t recording = 0; //this is a flag to indicate if the track wire is detected
        //if it does, then it starts to record the ADC output to find the distance
        //between the track wire and the sensor
        //initial state: es-no-event

    // hysteresis bounds 
    if (TrackWireInput > TW_UPPER_BOUND) {
#ifdef DEBUG_PRINTS
        printf("TrackWire found.\r\n");
#endif
        recording = 1;
    } else if (TrackWireInput < TW_LOWER_BOUND) {
#ifdef DEBUG_PRINTS
        printf("TrackWire lost.\r\n"); 
#endif
        recording = 0; //ES_NO_EVENT
    }
    
    
    // This one does not consider the prev values 
    // pick the one you want by changing the define value in the beginning
    // This will post continuously. Only good for updating distance in real time
#ifndef TAKE_PREV    
    thisEvent.EventType = recording; //either FOUND or NO EVENT
    // alternatively: (if LOST event is needed)
    //thisEvent.EventType = recording? FOUND_TRACK_WIRE:LOST_TRACK_WIRE;//either FOUND or LOST
    thisEvent.EventParam = TrackWireInput;
    PostTopLevel(thisEvent);
    return (TRUE);
#endif    
    
    // This one takes consideration of the prev values 
    currentEvent = recording;//either FOUND or NO EVENT
    // alternatively: (if LOST event is needed)
    //currentEvent = recording? FOUND_TRACK_WIRE:LOST_TRACK_WIRE;//either FOUND or LOST
    if (currentEvent != lastEvent) {
        thisEvent = currentEvent; 
        printf("%d\r\n", TrackWireInput);
        //PostTopLevel(thisEvent);
        lastEvent = currentEvent;
        returnVal = TRUE;
    

#ifndef EVENTCHECKER_TEST           // keep this as is for test harness
        //        PostTemplateHSM(thisEvent);
        //        PostGenericService(thisEvent);
#else
        //SaveEvent(thisEvent);
#endif   
    }
    return (returnVal);
}