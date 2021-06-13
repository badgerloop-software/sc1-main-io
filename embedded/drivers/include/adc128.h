#ifndef __adc__h__
#define __adc__h__

#include "i2c.h"


typedef enum AdcAddr {
    U2 = 0x2D,
    U4 = 0x1D,
} AdcAddr;

typedef enum AdcChan {
    CHAN_0 = 0x20,
    CHAN_1 = 0x21,
    CHAN_2 = 0x22,
    CHAN_3 = 0x23,
    CHAN_4 = 0x24,
    CHAN_5 = 0x25,
    CHAN_6 = 0x26,
    CHAN_7 = 0x27,
} AdcChan;

class Adc: private I2c {
    private:
        bool isInit;
    public:
        Adc(int bus, AdcAddr adc);
        int init(void);
        uint16_t readChannel(AdcChan chan);
        int isBusy(void);
        int debug(void);
};

#endif
