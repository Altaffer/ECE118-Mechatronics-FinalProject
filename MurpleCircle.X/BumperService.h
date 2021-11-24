#ifndef BUMPER_SERVICE_H  // <- This should be changed to your own guard on both
#define BUMPER_SERVICE_H  //    of these lines

#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT
 
uint8_t InitBumperService(uint8_t Priority);
uint8_t PostBumperService(ES_Event ThisEvent);
ES_Event RunBumperService(ES_Event ThisEvent);

#endif 
