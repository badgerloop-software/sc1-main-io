#include "rms.h"

#define TORQUE_SCALE_LWR(x) (((x)&0xFF) * 10) /* Converts Nm to the value the RMS wants */
#define TORQUE_SCALE_UPR(x) (((x) >> 8) * 10)

/* The following send functions are a series of cryptic steps
 * that just magically make the RMS (Motor Controller) work. 
 * If you question them too hard you may burst into flames (along with the motor
 * controller, so dont do it). The important part is that they 
 * are sent at the proper time and in the listed order. Timing information
 * will be coming a little later */

/* TODO figure out if heartbeat values may just be torque */


RMS::RMS(CAN& c) : CANDevice(c) {}


int RMS::begin() {
    /*	initMotor();*/

    // create CAN thread for this device
    return 0;
}

void RMS::rx_recv(struct can_frame* can_mesg)
{

    if (!this->can->canRead(can_mesg)) { // Checks for a CAN message
        //	printf("ID: %#X || ", (unsigned int) can_mesg->can_id);
        //	printf("Data: [%#X.%#X.%#X.%#X.%#X.%#X.%#X.%#X]\n\r", can_mesg->data[0], can_mesg->data[1], can_mesg->data[2], can_mesg->data[3], can_mesg->data[4], can_mesg->data[5], can_mesg->data[6], can_mesg->data[7]);
        if (parser(can_mesg->can_id, can_mesg->data, NO_FILTER)) {
            // printf("didn't receive rms data\n");
        }
    }
}

// int RMS::parser(uint32_t id, uint8_t* rmsData, uint32_t filter) {
//     if (filter != 0 && filter != id) {
//         return 1;
//     }
//     uint16_t val;
//     //uint16_t val2;
//     int16_t temp;
//     switch (id) {
//     case (0xa0):
//         setRmsIgbtTemp((rmsData[0] | (rmsData[1] << 8)) / 10); //Deg C
//         setRmsGateDriverBoardTemp((rmsData[6] | (rmsData[7] << 8)) / 10); //Deg C
// /*
//         printf("IGBT: %d\r\n", getRmsIgbtTemp());
//         printf("Gate Driver Board Temp: %d\r\n", getRmsGateDriverBoardTemp());
// */
//         break;
//     case (0xa1):
//         setRmsControlBoardTemp((rmsData[0] | (rmsData[1] << 8)) / 10); // Deg C
// /*
//         printf("Control Board Temp: %d\r\n", getRmsControlBoardTemp());
// */
//         break;
//     case (0xa2):
//         val = (rmsData[4] | rmsData[5] << 8) / 10;
//         setRmsMotorTemp(val > 300 ? getRmsMotorTemp() : val); //Deg C
// /*
//         printf("Motor Temp: %d\r\n", getRmsMotorTemp());
// */
//         break;
//     case (0xa3):
//         break;
//     case (0xa4):
//         break;
//     case (0xa5):
//         setRmsMotorSpeed((rmsData[2] | (rmsData[3] << 8))); //val == 0 ? 0 : 65536 - abs(val) ;//< -10000 || val > 10000 ? getRmsMotorSpeed(): val; // RPM
//         setRmsElectricalFreq((rmsData[4] | (rmsData[5] << 8)) / 10); //electrical frequency Hz
// /*
//         printf("Motor Speed: %d\r\n", getRmsMotorSpeed());
//         printf("Elect. Freq: %d\r\n", getRmsElectricalFreq());
// */
//         break;
//     case (0xa6):
//         temp = (rmsData[0] | (rmsData[1] << 8));
// 
//         setRmsPhaseACurrent(temp / 10); //> 1000 ? getRmsPhaseACurrent() : val; // Phase A current
//         temp = (rmsData[6] | (rmsData[7] << 8));
//         setRmsDcBusCurrent(temp / 10); //< 0 ? getRmsDcBusCurrent() : val2; //DC Bus current
// /*
//         printf("Phase A Current: %d\r\n", getRmsPhaseACurrent());
//         printf("DC Bus Current: %d\r\n", getRmsDcBusCurrent());
//         printf("Phase B Current: %d\r\n", getRmsPhaseBCurrent()); //FIXME This isnt actually being read in?
// */
//         break;
//     case (0xa7):
// 
//         temp = (rmsData[0] | (rmsData[1] << 8));
//         setRmsDcBusVoltage(temp / 10.0);
// 
//         // setRmsOutputVoltageLn(val2); //Voltage line to netural
// /*
//         printf("DC Bus Voltage: %d\r\n", getRmsDcBusVoltage());
//         printf("Output Voltage line: %d\r\n", getRmsOutputVoltageLn());
// */
//         break;
//     case (0xa8):
//         break;
//     case (0xa9):
//         setRmsLvVoltage((rmsData[6] | (rmsData[7] << 8)) / 100);
// /*
//         printf("LV Voltage: %d\r\n", getRmsLvVoltage());
// */
//         break;
// 
//     case (0xaa):
//         setRmsCanCode1((rmsData[3] << 24) | (rmsData[2] << 16) | (rmsData[1] << 8) | rmsData[0]);
//         setRmsCanCode2((rmsData[7] << 24) | (rmsData[6] << 16) | (rmsData[5] << 8) | rmsData[4]);
// /*
//         printf("CAN Code 1: %lld\r\n", (long long int)getRmsCanCode() 1);
//         printf("CAN Code 2: %lld\r\n", (long long int)getRmsCanCode() 2);
// */
//         break;
//     case (0xab):
//         setRmsFaultCode1((rmsData[3] << 24) | (rmsData[2] << 16) | (rmsData[1] << 8) | rmsData[0]);
//         setRmsFaultCode2((rmsData[7] << 24) | (rmsData[6] << 16) | (rmsData[5] << 8) | rmsData[4]);
// /*
//         printf("Fault Code 1: %lld\r\n", (long long int)getRmsFaultCode() 1);
//         printf("Fault Code 2: %lld\r\n", (long long int)getRmsFaultCode() 2);
// */
//         break;
//     case (0xac):
//         setRmsCommandedTorque((rmsData[0] | (rmsData[1] << 8))); // > 200 ? getRmsCommandedTorque() : val;
//         setRmsCommandedTorque(getRmsCommandedTorque() / 10);
//         setRmsActualTorque((rmsData[2] | (rmsData[3] << 8))); // / 10;
//         setRmsActualTorque(getRmsActualTorque() / 10);
// /*
//         printf("Commanded Torque: %d\r\n", getRmsCommandedTorque());
//         printf("Actual Torque: %d\r\n", getRmsActualTorque());
// */
//         break;
//     case (0xad):
//         break;
//     case (0xae):
//         break;
//     case (0xaf):
//         break;
//     default:
//         return 1;
//     }
//     return 0;
// }

/* 1 */
int RMS::rmsEnHeartbeat()
{
    uint8_t payload[] = { 0x92, 0x0, 0x1, 0x0, 0x1, 0x0, 0x0, 0x0 };
    sem_wait(&this->can->canSem);
    int ret = this->can->canSend(RMS_HB_ID, payload, 8);
    sem_post(&this->can->canSem);
    return ret;
}

/* 2 */
int RMS::rmsClrFaults()
{
    uint8_t payload[] = { 0x14, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0 };
    sem_wait(&this->can->canSem);
    int ret = this->can->canSend(RMS_CLR_FAULTS_ID, payload, 8);
    sem_post(&this->can->canSem);
    return ret;
}

/* 3 */
int RMS::rmsInvDis()
{
    uint8_t payload[] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
    sem_wait(&this->can->canSem);
    int ret = this->can->canSend(RMS_INV_DIS_ID, payload, 8);
    sem_post(&this->can->canSem);
    return ret;
}

/* 4 */
int RMS::rmsInvEn()
{
    uint8_t payload[] = { 40 /*TORQUE_SCALE_LWR(1)*/, 0x0, 0x0, 0x0, 0x1, 0x1, 0x0, 0x0 };
    sem_wait(&this->can->canSem);
    int ret = this->can->canSend(RMS_INV_EN_ID, payload, 8);
    sem_post(&this->can->canSem);
    return ret;
}

int RMS::rmsInvEnNoTorque()
{
    uint8_t payload[] = { 0x0, 0x0, 0x0, 0x0, 0x1, 0x1, 0x0, 0x0 };
    sem_wait(&this->can->canSem);
    int ret = this->can->canSend(RMS_INV_EN_ID, payload, 8);
    sem_post(&this->can->canSem);
    return ret;
}

/* 5 */
int RMS::rmsInvForward20()
{
    uint8_t payload[] = { TORQUE_SCALE_LWR(1), 0x0, 0x0, 0x0, 0x1, 0x1, 0x0, 0x0 };
    sem_wait(&this->can->canSem);
    int ret = this->can->canSend(RMS_INV_FW_20_ID, payload, 8);
    sem_post(&this->can->canSem);
    return ret;
}

/* 6 not even going to bother setting these high ones because I am too scared */
int RMS::rmsInvForward30()
{
    uint8_t payload[] = { TORQUE_SCALE_LWR(1), 0x0, 0x0, 0x0, 0x1, 0x1, 0x0, 0x0 };
    sem_wait(&this->can->canSem);
    int ret = this->can->canSend(RMS_INV_FW_30_ID, payload, 8);
    sem_post(&this->can->canSem);
    return ret;
}

/* 7 */
int RMS::rmsCmdNoTorque()
{
    uint8_t payload[] = { 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0 };
    sem_wait(&this->can->canSem);
    int ret = this->can->canSend(RMS_CMD_0_NM_ID, payload, 8);
    sem_post(&this->can->canSem);
    return ret;
}

/* 8 */
int RMS::rmsDischarge()
{
    uint8_t payload[] = { 0x0, 0x0, 0x0, 0x0, 0x1, 0x2, 0x0, 0x0 };
    sem_wait(&this->can->canSem);
    int ret = this->can->canSend(RMS_INV_DISCHARGE_ID, payload, 8);
    sem_post(&this->can->canSem);
    return ret;
}

int RMS::rmsIdleHb()
{
    uint8_t payload[] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
    sem_wait(&this->can->canSem);
    int ret = this->can->canSend(RMS_HB_ID, payload, 8);
    sem_post(&this->can->canSem);
    return ret;
}

int RMS::rmsWriteEeprom(uint16_t addr, uint16_t val)
{
    uint8_t payload[] = { addr & 0xff, (addr >> 8), 0x1, 0x0,
        val & 0xff, (val >> 8), 0x0, 0x0 };
    return this->can->canSend(RMS_EEPROM_SEND_ID, payload, 8);
}

int RMS::rmsReadEeprom(uint16_t addr)
{
    uint8_t payload[] = { addr & 0xff, (addr >> 8), 0x0, 0x0,
        0x0, 0x0, 0x0, 0x0 };
    return this->can->canSend(RMS_EEPROM_SEND_ID, payload, 8);
}

static uint16_t convRmsDataFormat(uint8_t byte1, uint8_t byte2)
{
    return byte1 | (byte2 << 8);
}

int RMS::rmsCmdResponseParse(uint8_t* rmsData, uint16_t filter, bool write)
{
    /* Eeprom message */
/*
    int i = 0;
    printf("Message: 0xC2:");
    for (i = 0; i < 8; i++)
        printf(" %#X", rmsData[i]);
    printf("\n");
*/
    uint16_t paramAddr = convRmsDataFormat(rmsData[0], rmsData[1]);
    if (paramAddr == 0) {
        fprintf(stderr, "RMS did not recognize that message\n");
        return -1;
    }
    if (paramAddr != filter)
        return -1;

    if (write && !rmsData[WR_SUCCESS_BIT]) {
        fprintf(stderr, "Write failed\n");
        return -1;
    } else if (write) {
        return 0;
    }

    return convRmsDataFormat(rmsData[4], rmsData[5]);
}
int RMS::rmsSendHbMsg(uint16_t torque)
{

    uint8_t payload[] = { TORQUE_SCALE_LWR(torque), TORQUE_SCALE_UPR(torque), 0x0, 0x0,
        0x1, 0x1, 0x0, 0x0 };

    sem_wait(&this->can->canSem);
    int ret = this->can->canSend(RMS_INV_EN_ID, payload, 8);
    sem_post(&this->can->canSem);
    return ret;
}

