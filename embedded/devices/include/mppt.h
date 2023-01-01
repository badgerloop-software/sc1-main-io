#ifndef __MPPT_H__
#define __MPPT_H__

#include <linux/can.h>

#include "can.h"

typedef enum { MaxOutputCurrent = 0xA } ids;

class Mppt : public CanDevice {  // Mppt = Maximum Power Point Tracking. MPPT
                                 // optimizes voltage
                                 // conversion between solar array and battery
                                 // to minimize power loss.

 public:
  Mppt(Can &c) : CanDevice(c, {}) {}
  int sendMaxOutputCurrent(float moc);
};

#endif
