#include "can.h"
#include <linux/can.h>

typedef enum { MaxOutputCurrent = 0xA, Test = 0x69 } messages;

class Mppt : private CanDevice { // Mppt = Maximum Power Point Tracking. MPPT
                                 // optimizes voltage
                                 // conversion between solar array and battery
                                 // to minimize power loss.
public:
  Mppt(Can &c);
  int parse(struct can_frame &msg);
  int sendMaxOutputCurrent(float moc);
};
