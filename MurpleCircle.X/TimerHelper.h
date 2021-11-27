#ifndef TIMER_HELPER_H  // <- This should be changed to your own guard on both
#define TIMER_HELPER_H  //    of these lines

#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT
 
uint8_t TurnTimerHelper(ES_Event ThisEvent);

uint8_t MotionTimerHelper(ES_Event ThisEvent);


#endif 
