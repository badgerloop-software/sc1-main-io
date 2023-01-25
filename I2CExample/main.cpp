#include "mbed.h"
#include "include/ina3221.h"
#include <array>

// Instantiate I2C for test
I2C i2cBus(PB_9, PB_8);

void printDisplay(std::array<float, 3> voltages, std::array<float, 3> currents) {
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

    printf("Channel\t\tVoltage\t\tCurrent\n");
    printf("1\t\t\t\t%f\t\t\t\t%f\n", voltages[0], currents[0]);
    printf("2\t\t\t\t%f\t\t\t\t%f\n", voltages[1], currents[1]);
    printf("3\t\t\t\t%f\t\t\t\t%f\n", voltages[2], currents[2]);
}

// main() runs in its own thread in the OS
int main()
{
    // Instantiate instance
    Ina3221 testDevice(0x40 << 1, 0.005, 0.005, 0.005, i2cBus);
    printf("Starting device\n");
    while (1) {
        if (!testDevice.begin()) {
            break;
        }
        printf("Failed to start, trying again\n");
        wait_us(1000000);
    }

    std::array<float, 3> voltages;
    std::array<float, 3> currents;
    voltages.fill(0);
    currents.fill(0);

    while (true) {
        for (int i = 0; i < 3; i++) {
            voltages[i] = testDevice.readVoltage(i);
            voltages[i] = testDevice.readCurrent(i);
        }
        printDisplay(voltages, currents);
        wait_us(1000000);
    }
}

