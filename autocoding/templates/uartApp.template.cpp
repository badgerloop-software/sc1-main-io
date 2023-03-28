#include <iostream>

#include "rtos.h"
#include "uartApp.h"
#define NUM_COMMAND_BYTES 1
#define T_MESSAGE_US 70000  // around 1/15 of a second
#define HEARTBEAT 2         // error state if this # messages that aren't read

Thread thread1;
Thread thread2;
Mutex uart_buffer;

data_format dfwrite;
data_format dfdata;
data_format emptyStruct;

bool restart_enable;

void clearDataFormatRead() { dfdata = emptyStruct; }

void send_message_thread() {
  while (true) {
    check_shutdown_errors();  // check if mcu_hv_en needs to be set to 0
    copyDataStructToWriteStruct();
    uart_buffer.lock();
    writeUart(&dfwrite, TOTAL_BYTES);
    uart_buffer.unlock();
    wait_us(T_MESSAGE_US);
  }
}

void read_command_thread() {
  int messages_not_received =
      0;  // number of consecutive messages DriverIO fails to send
  bool restart_enable_error = 0;  // check if restart_enable has been 1
  while (true) {
    uart_buffer.lock();
    restart_enable = 0;
    // set mcu_hv_en to 0 (error state) if HEARTBEAT consecutive messages aren't
    // read
    if (readUart(&restart_enable, NUM_COMMAND_BYTES) == 0) {
      if (++messages_not_received == HEARTBEAT) {
        set_mcu_hv_en(0);
      }
    } else {  // a message was read
      messages_not_received = 0;
      // check that we've received at least one restart_enable == 1 before we
      // set mcu_hv_en high again
      if (restart_enable) {
        restart_enable_error = true;
      }
      if (restart_enable == 0 && get_mcu_hv_en() == 0 && restart_enable_error) {
        set_mcu_hv_en(1);
        restart_enable_error = false;
      }
    }
    uart_buffer.unlock();
    wait_us(T_MESSAGE_US);
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
