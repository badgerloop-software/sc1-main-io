#ifndef __CAN_H__
#define __CAN_H__

#include <linux/can.h>
#include <semaphore.h>
#include <thread>
#include <net/if.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

#ifdef USE_VCAN
#define CAN_INTF "vcan0"
#else
#define CAN_INTF "can0"
#endif

static const struct itimerval new_val = {
    { 0, 10000 },
    { 0, 10000 }
};

class CAN {
    private:
        static struct sockaddr_can addr;
        static struct ifreq ifr;
        static int socket;
        std::thread canThread;

    public:
        sem_t canSem;
        CAN();
        void canLoop();
        int begin();
        int canRead(struct can_frame* can_mesg);
        int canSend(uint32_t id, uint8_t* data, uint8_t size);
};

#endif
