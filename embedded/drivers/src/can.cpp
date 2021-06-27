#include "can.h"
#include <linux/can.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>
//#include <linux/interrupt.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CAN::CAN(int *s) {
    this->socket = *s;
}

int CAN::begin() {
    strcpy(this->ifr.ifr_name, CAN_INTF);

    if (ioctl(this->socket, SIOCGIFINDEX, &this->ifr) == -1) {
        printf("Failed to find bus\n\r");
        return 1;
    }

    this->addr.can_family = AF_CAN;
    this->addr.can_ifindex = ifr.ifr_ifindex;

    bind(this->socket, (struct sockaddr*)&this->addr, sizeof(this->addr));

    struct sigaction action;
    action.sa_handler = updateNewMessage;
    sigaction(SIGALRM, &action, NULL);
    setitimer(ITIMER_REAL, &new_val, NULL);
    return 0;
}

int CAN::canRead(struct can_frame* recvd_msg) {
    int nBytes = recv(this->socket, recvd_msg, sizeof(struct can_frame), MSG_DONTWAIT);
    /* This is actually ok if it fails here, it just means no new info */
    if (nBytes < 0) {
        return 1;
    }
    return 0;
}

int CAN::canSend(uint32_t id, uint8_t* data, uint8_t size) {
    struct can_frame tx_msg;

    tx_msg.can_dlc = size;
    tx_msg.can_id = id; // Should actually be 11 bits max
    int i;
    for (i = 0; i < size; i++) {
        tx_msg.data[i] = data[i];
    }
    send(this->socket, &tx_msg, sizeof(struct can_frame), MSG_DONTWAIT);

    return 0; // Not much we do with error codes here
}
