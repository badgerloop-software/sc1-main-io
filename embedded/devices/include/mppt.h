#include <linux/can.h>
#include <pthread.h>

#include "can.h"

class Mppt : private CanDevice {  // Mppt = Maximum Power Point Tracking. MPPT
                                  // optimizes voltage
  // conversion between solar array and battery to minimize power
  // loss.
 private:
  mutex MpptMutex;

 public:
  Mppt(Can &);
  int sendMaxOutputCurrent(float);
};
