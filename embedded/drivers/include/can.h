#ifndef _CAN_H__
#define _CAN_H__

#include <linux/can.h>
#include <semaphore.h>
#include <thread>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <cstring>
#include <vector>

#define NO_FILTER 0

#ifdef USE_VCAN
#define CAN_INTF "vcan0"
#else
#define CAN_INTF "can0"
#endif

static const struct itimerval new_val = {
    { 0, 10000 },
    { 0, 10000 }
};

class CAN;
class CANDevice;



class CAN {
    private:
        std::vector<std::reference_wrapper<CANDevice>> devices;
        static struct sockaddr_can addr;
        static struct ifreq ifr;
        static int socket;
        std::thread canThread;
        void canLoop();

    public:
        sem_t canSem;
        CAN();
        void addDevice(CANDevice& d);
        int begin();
        int canRead(struct can_frame* can_mesg);
        int canSend(uint32_t id, uint8_t* data, uint8_t size);
};

class CANDevice {
    public:
        virtual int parser(uint32_t id, uint8_t* data, uint32_t filter);
        virtual int parser(struct can_frame* can_mesg);
        virtual int begin();

        CAN& can;
        CANDevice(CAN& c);
};

#endif
