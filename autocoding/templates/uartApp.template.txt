#include "uartApp.h"
#include "rtos.h"
#include <iostream>

Thread thread1;
Thread thread2;

data_format dfwrite;
data_format dfdata;
data_format emptyStruct;

bool restart_enable;

void clearDataFormatRead() { dfdata = emptyStruct; }

void send_message_thread() {
    while(true) {
        uart_buffer.lock();
        writeUart(&dfwrite, totalBytes);
        uart_buffer.unlock();
        wait_us(1000000);
    }
}

// TODO fix this method to how we want to read commands from DriverIO
void read_command_thread() {
    while(true) {
        uart_buffer.lock();
        restart_enable = 0;
        readUart(&restart_enable, numCommandBytes);
        uart_buffer.unlock();
        wait_us(1000000);
    }
}

int runUart() {
    initUart();
    thread1.start(read_command_thread);
    thread2.start(send_message_thread);
    return 0;
}

Mutex restart_enable_mutex;

bool get_restart_enable() {
    restart_enable_mutex.lock();
    bool val = restart_enable;
    restart_enable_mutex.unlock();
    return val;
}

/*!!AUTO-GENERATE HERE!!*/
