#include "motorController.h"

#define TORQUE_SCALE_LWR(x) \
  (((x)&0xFF) * 10) /* Converts Nm to the value the MotorController wants */
#define TORQUE_SCALE_UPR(x) (((x) >> 8) * 10)

/* The following send functions are a series of cryptic steps
 * that just magically make the MotorController work.
 * If you question them too hard you may burst into flames (along with the motor
 * controller, so dont do it). The important part is that they
 * are sent at the proper time and in the listed order. Timing information
 * will be coming a little later */

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
    case (0xa0):
      //        setRmsIgbtTemp((motorControllerData[0] | (motorControllerData[1]
      //        << 8)) / 10); //Deg C
      //        setRmsGateDriverBoardTemp((motorControllerData[6] |
      //        (motorControllerData[7] << 8)) / 10); //Deg C
      /*
              printf("IGBT: %d\r\n", getRmsIgbtTemp());
              printf("Gate Driver Board Temp: %d\r\n",
         getRmsGateDriverBoardTemp());
      */
      break;
    case (0xa1):
      //        setRmsControlBoardTemp((motorControllerData[0] |
      //        (motorControllerData[1] << 8)) / 10);
      //        // Deg C
      /*
              printf("Control Board Temp: %d\r\n", getRmsControlBoardTemp());
      */
      break;
    case (0xa2):
      val = (motorControllerData[4] | motorControllerData[5] << 8) / 10;
      //        setRmsMotorTemp(val > 300 ? getRmsMotorTemp() : val); //Deg C
      /*
              printf("Motor Temp: %d\r\n", getRmsMotorTemp());
      */
      break;
    case (0xa3):
      break;
    case (0xa4):
      break;
    case (0xa5):
      //        setRmsMotorSpeed((motorControllerData[2] |
      //        (motorControllerData[3] << 8))); //val == 0 ? 0 : 65536 -
      //        abs(val) ;//< -10000 || val > 10000 ? getRmsMotorSpeed(): val;
      //        // RPM setRmsElectricalFreq((motorControllerData[4] |
      //        (motorControllerData[5] << 8)) / 10); //electrical frequency Hz
      /*
              printf("Motor Speed: %d\r\n", getRmsMotorSpeed());
              printf("Elect. Freq: %d\r\n", getRmsElectricalFreq());
      */
      break;
    case (0xa6):
      temp = (motorControllerData[0] | (motorControllerData[1] << 8));

      //         setRmsPhaseACurrent(temp / 10); //> 1000 ?
      //         getRmsPhaseACurrent() : val; // Phase A current
      temp = (motorControllerData[6] | (motorControllerData[7] << 8));
      //         setRmsDcBusCurrent(temp / 10); //< 0 ? getRmsDcBusCurrent() :
      //         val2; //DC Bus current
      /*
              printf("Phase A Current: %d\r\n", getRmsPhaseACurrent());
              printf("DC Bus Current: %d\r\n", getRmsDcBusCurrent());
              printf("Phase B Current: %d\r\n", getRmsPhaseBCurrent()); //FIXME
         This isnt actually being read in?
      */
      break;
    case (0xa7):

      temp = (motorControllerData[0] | (motorControllerData[1] << 8));
      //         setRmsDcBusVoltage(temp / 10.0);

      // setRmsOutputVoltageLn(val2); //Voltage line to netural
      /*
              printf("DC Bus Voltage: %d\r\n", getRmsDcBusVoltage());
              printf("Output Voltage line: %d\r\n", getRmsOutputVoltageLn());
      */
      break;
    case (0xa8):
      break;
    case (0xa9):
      //         setRmsLvVoltage((motorControllerData[6] |
      //         (motorControllerData[7] << 8)) / 100);
      /*
              printf("LV Voltage: %d\r\n", getRmsLvVoltage());
      */
      break;

    case (0xaa):
      //         setRmsCanCode1((motorControllerData[3] << 24) |
      //         (motorControllerData[2] << 16) | (motorControllerData[1] << 8)
      //         | motorControllerData[0]);
      //         setRmsCanCode2((motorControllerData[7] << 24) |
      //         (motorControllerData[6] << 16) | (motorControllerData[5] << 8)
      //         | motorControllerData[4]);
      /*
              printf("CAN Code 1: %lld\r\n", (long long int)getRmsCanCode() 1);
              printf("CAN Code 2: %lld\r\n", (long long int)getRmsCanCode() 2);
      */
      break;
    case (0xab):
      //      setRmsFaultCode1((motorControllerData[3] << 24) |
      //      (motorControllerData[2] << 16) | (motorControllerData[1] << 8) |
      //      motorControllerData[0]);
      //        setRmsFaultCode2((motorControllerData[7] << 24) |
      //        (motorControllerData[6] << 16) | (motorControllerData[5] << 8) |
      //        motorControllerData[4]);
      /*
              printf("Fault Code 1: %lld\r\n", (long long int)getRmsFaultCode()
         1); printf("Fault Code 2: %lld\r\n", (long long int)getRmsFaultCode()
         2);
      */
      break;
    case (0xac):
      //        setRmsCommandedTorque((motorControllerData[0] |
      //        (motorControllerData[1] << 8))); // > 200 ?
      //        getRmsCommandedTorque() : val;
      //        setRmsCommandedTorque(getRmsCommandedTorque() / 10);
      //        setRmsActualTorque((motorControllerData[2] |
      //        (motorControllerData[3] << 8))); // / 10;
      //        setRmsActualTorque(getRmsActualTorque() / 10);
      /*
              printf("Commanded Torque: %d\r\n", getRmsCommandedTorque());
              printf("Actual Torque: %d\r\n", getRmsActualTorque());
      */
      break;
    case (0xad):
      break;
    case (0xae):
      break;
    case (0xaf):
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
  int ret = this->can->canSend(MotorController_HB_ID, payload, 8);
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
  int ret = this->can->canSend(MotorController_INV_DIS_ID, payload, 8);
  sem_post(&this->can->canSem);
  return ret;
}

/* 4 */
int MotorController::motorControllerInvEn() {
  uint8_t payload[] = {
      40 /*TORQUE_SCALE_LWR(1)*/, 0x0, 0x0, 0x0, 0x1, 0x1, 0x0, 0x0};
  sem_wait(&this->can->canSem);
  int ret = this->can->canSend(MotorController_INV_EN_ID, payload, 8);
  sem_post(&this->can->canSem);
  return ret;
}

int MotorController::motorControllerInvEnNoTorque() {
  uint8_t payload[] = {0x0, 0x0, 0x0, 0x0, 0x1, 0x1, 0x0, 0x0};
  sem_wait(&this->can->canSem);
  int ret = this->can->canSend(MotorController_INV_EN_ID, payload, 8);
  sem_post(&this->can->canSem);
  return ret;
}

/* 5 */
int MotorController::motorControllerInvForward20() {
  uint8_t payload[] = {TORQUE_SCALE_LWR(1), 0x0, 0x0, 0x0, 0x1, 0x1, 0x0, 0x0};
  sem_wait(&this->can->canSem);
  int ret = this->can->canSend(MotorController_INV_FW_20_ID, payload, 8);
  sem_post(&this->can->canSem);
  return ret;
}

/* 6 not even going to bother setting these high ones because I am too scared */
int MotorController::motorControllerInvForward30() {
  uint8_t payload[] = {TORQUE_SCALE_LWR(1), 0x0, 0x0, 0x0, 0x1, 0x1, 0x0, 0x0};
  sem_wait(&this->can->canSem);
  int ret = this->can->canSend(MotorController_INV_FW_30_ID, payload, 8);
  sem_post(&this->can->canSem);
  return ret;
}

/* 7 */
int MotorController::motorControllerCmdNoTorque() {
  uint8_t payload[] = {0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0};
  sem_wait(&this->can->canSem);
  int ret = this->can->canSend(MotorController_CMD_0_NM_ID, payload, 8);
  sem_post(&this->can->canSem);
  return ret;
}

/* 8 */
int MotorController::motorControllerDischarge() {
  uint8_t payload[] = {0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0};
  sem_wait(&this->can->canSem);
  int ret = this->can->canSend(MotorController_INV_DISCHARGE_ID, payload, 8);
  sem_post(&this->can->canSem);
  return ret;
}

int MotorController::motorControllerIdleHb() {
  uint8_t payload[] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
  sem_wait(&this->can->canSem);
  int ret = this->can->canSend(MotorController_HB_ID, payload, 8);
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

static uint16_t convRmsDataFormat(uint8_t byte1, uint8_t byte2) {
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
  uint16_t paramAddr =
      convRmsDataFormat(motorControllerData[0], motorControllerData[1]);
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

  return convRmsDataFormat(motorControllerData[4], motorControllerData[5]);
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
  int ret = this->can->canSend(MotorController_INV_EN_ID, payload, 8);
  sem_post(&this->can->canSem);
  return ret;
}
