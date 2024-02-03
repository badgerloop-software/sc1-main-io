#ifndef __dataFormat__h__
#define __dataFormat__h__

#include "mbed.h"
#pragma pack(push, 1)

/*!!AUTO-GENERATE HERE!!*/

bool get_restart_enable();

void cleardfdata();

// starts the threads for reading and writing
int runDataFormat();

#pragma pack(pop)
#endif
