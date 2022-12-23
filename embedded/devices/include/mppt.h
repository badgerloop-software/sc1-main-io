#include <linux/can.h>
#include "can.h"

typedef enum { MaxOutputCurrent = 0xA, Test = 0x69 } ids;

class Mppt : public CanDevice { // Mppt = Maximum Power Point Tracking. MPPT
                                // optimizes voltage
                                // conversion between solar array and battery
                                // to minimize power loss.
public:
  Mppt(Can &c);
  int parse(struct can_frame &msg);
  int sendMaxOutputCurrent(float moc);
};
