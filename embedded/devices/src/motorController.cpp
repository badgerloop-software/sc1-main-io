#include "motorController.h"

#include <linux/can.h>  // for can_frame
#include <semaphore.h>  // for sem_post, sem_wait
#include <stdio.h>      // for fprintf, stderr

#include <queue>  // for queue

#define TORQUE_SCALE_LWR(x) \
  (((x)&0xFF) * 10) /* Converts Nm to the value the MotorController wants */
#define TORQUE_SCALE_UPR(x) (((x) >> 8) * 10)

/* TODO figure out if heartbeat values may just be torque */

MotorController::MotorController(CAN* c) : CANDevice(c) {}

int MotorController::begin() {
  /*	initMotor();*/

  return CANDevice::begin();
}

int MotorController::validMsg(can_frame* can_mesg) {
  if (can_mesg->can_id >= 0xa0 && can_mesg->can_id <= 0xaf) {
    this->messages.push(can_mesg);
    return 0;
  }
  return 1;  // not a valid msg
}

int MotorController::parser(uint32_t id, uint8_t* motorControllerData,
                            uint32_t filter) {
  if (filter != 0 && filter != id) {
    return 1;
  }
  uint16_t val;
  // uint16_t val2;
  int16_t temp;
  switch (id) {
    case (0xa0):  // Temperatures #1
      break;
    case (0xa1):  // Temperatures #2
      break;
    case (0xa2):  // Temperatures #3
      break;
    case (0xa3):  // Analog Inputs Voltages
      break;
    case (0xa4):  // Digital Inputs Voltages
      break;
    case (0xa5):  // Motor Position Information
      break;
    case (0xa6):  // Current Information
      break;
    case (0xa7):  // Voltage Information
      break;
    case (0xa8):  // Flux Information
      break;
    case (0xa9):  // Internal Voltages
      break;
    case (0xaa):  // Internal States
      break;
    case (0xab):  // Fault Codes
      break;
    case (0xac):  // Torque & Timer Information
      break;
    case (0xad):  // Modulation Index & Flux Weaking Output Information
      break;
    case (0xae):  // Firmware Information
      break;
    case (0xaf):  // Diagnostic Data
      break;
    default:
      return 1;
  }
  return 0;
}

/* 1 */
int MotorController::motorControllerEnHeartbeat() {
  uint8_t payload[] = {0x92, 0x0, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0};
  sem_wait(&this->can->canSem);
  int ret = this->can->canSend(COMMAND_MESSAGE_ID, payload, 8);
  sem_post(&this->can->canSem);
  return ret;
}

/* 2 */
int MotorController::motorControllerClrFaults() {
  uint8_t payload[] = {0x14, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0};
  sem_wait(&this->can->canSem);
  int ret = this->can->canSend(MotorController_CLR_FAULTS_ID, payload, 8);
  sem_post(&this->can->canSem);
  return ret;
}

/* 3 */
int MotorController::motorControllerInvDis() {
  uint8_t payload[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  sem_wait(&this->can->canSem);
  int ret = this->can->canSend(COMMAND_MESSAGE_ID, payload, 8);
  sem_post(&this->can->canSem);
  return ret;
}

/* 4 */
int MotorController::motorControllerInvEn() {
  uint8_t payload[] = {
      40 /*TORQUE_SCALE_LWR(1)*/, 0x0, 0x0, 0x0, 0x1, 0x1, 0x0, 0x0};
  sem_wait(&this->can->canSem);
  int ret = this->can->canSend(COMMAND_MESSAGE_ID, payload, 8);
  sem_post(&this->can->canSem);
  return ret;
}

int MotorController::motorControllerInvEnNoTorque() {
  uint8_t payload[] = {0x0, 0x0, 0x0, 0x0, 0x1, 0x1, 0x0, 0x0};
  sem_wait(&this->can->canSem);
  int ret = this->can->canSend(COMMAND_MESSAGE_ID, payload, 8);
  sem_post(&this->can->canSem);
  return ret;
}

/* 5 */
int MotorController::motorControllerInvForward20() {
  uint8_t payload[] = {TORQUE_SCALE_LWR(20), 0x0, 0x0, 0x0, 0x1, 0x1, 0x0, 0x0};
  sem_wait(&this->can->canSem);
  int ret = this->can->canSend(COMMAND_MESSAGE_ID, payload, 8);
  sem_post(&this->can->canSem);
  return ret;
}

/* 6 not even going to bother setting these high ones because I am too scared */
int MotorController::motorControllerInvForward30() {
  uint8_t payload[] = {TORQUE_SCALE_LWR(1), 0x0, 0x0, 0x0, 0x1, 0x1, 0x0, 0x0};
  sem_wait(&this->can->canSem);
  int ret = this->can->canSend(COMMAND_MESSAGE_ID, payload, 8);
  sem_post(&this->can->canSem);
  return ret;
}

/* 7 */
int MotorController::motorControllerCmdNoTorque() {
  uint8_t payload[] = {0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0};
  sem_wait(&this->can->canSem);
  int ret = this->can->canSend(COMMAND_MESSAGE_ID, payload, 8);
  sem_post(&this->can->canSem);
  return ret;
}

/* 8 */
int MotorController::motorControllerDischarge() {
  uint8_t payload[] = {0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0};
  sem_wait(&this->can->canSem);
  int ret = this->can->canSend(COMMAND_MESSAGE_ID, payload, 8);
  sem_post(&this->can->canSem);
  return ret;
}

int MotorController::motorControllerIdleHb() {
  uint8_t payload[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  sem_wait(&this->can->canSem);
  int ret = this->can->canSend(COMMAND_MESSAGE_ID, payload, 8);
  sem_post(&this->can->canSem);
  return ret;
}

int MotorController::motorControllerWriteEeprom(uint16_t addr, uint16_t val) {
  uint8_t payload[] = {addr & 0xff, (addr >> 8), 0x1, 0x0,
                       val & 0xff,  (val >> 8),  0x0, 0x0};
  return this->can->canSend(MotorController_EEPROM_SEND_ID, payload, 8);
}

int MotorController::motorControllerReadEeprom(uint16_t addr) {
  uint8_t payload[] = {addr & 0xff, (addr >> 8), 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  return this->can->canSend(MotorController_EEPROM_SEND_ID, payload, 8);
}

static uint16_t convMotorControllerDataFormat(uint8_t byte1, uint8_t byte2) {
  return byte1 | (byte2 << 8);
}

int MotorController::motorControllerCmdResponseParse(
    uint8_t* motorControllerData, uint16_t filter, bool write) {
  /* Eeprom message */
  /*
      int i = 0;
      printf("Message: 0xC2:");
      for (i = 0; i < 8; i++)
          printf(" %#X", motorControllerData[i]);
      printf("\n");
  */
  uint16_t paramAddr = convMotorControllerDataFormat(motorControllerData[0],
                                                     motorControllerData[1]);
  if (paramAddr == 0) {
    fprintf(stderr, "MotorController did not recognize that message\n");
    return -1;
  }
  if (paramAddr != filter) return -1;

  if (write && !motorControllerData[WR_SUCCESS_BIT]) {
    fprintf(stderr, "Write failed\n");
    return -1;
  } else if (write) {
    return 0;
  }

  return convMotorControllerDataFormat(motorControllerData[4],
                                       motorControllerData[5]);
}
int MotorController::motorControllerSendHbMsg(uint16_t torque) {
  uint8_t payload[] = {TORQUE_SCALE_LWR(torque),
                       TORQUE_SCALE_UPR(torque),
                       0x0,
                       0x0,
                       0x1,
                       0x1,
                       0x0,
                       0x0};

  sem_wait(&this->can->canSem);
  int ret = this->can->canSend(COMMAND_MESSAGE_ID, payload, 8);
  sem_post(&this->can->canSem);
  return ret;
}
