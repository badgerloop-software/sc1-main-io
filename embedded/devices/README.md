# Badgerloop Device Drivers

# IO Expanders

The purpose of an IO Expander is to utilize a serial communication protocol to expand the number of
GPIO pins on a system.

## MCP23017

[Datasheet](https://ww1.microchip.com/downloads/en/devicedoc/20001952c.pdf)

### Setup

Create a new MCP23017 by creating a new object. Then "begin" the device.

```c++
uint8_t directions[] = {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1};
Mcp23017 iox = Mcp23017(<bus>,<addr>);
iox.begin(directions);
```

### Usage

Get/Set pin values by utilizing these functions

```c++
uint8_t get_state(int pin); // Returns the state of the pin (0 or 1)
int set_state(int pin, uint8_t value) // Sets a specific pin a value (0 or 1)
```

### Corresponding Tests and Examples

TODO...

## MPPT
MPPT = Maximum Power Point Tracking

MPPT optimizes voltage conversion between solar array and battery to minimize power loss.

[Definition](https://www.solar-electric.com/learning-center/mppt-solar-charge-controllers.html/)

[Datasheet](https://www.prohelion.com/wp-content/uploads/2021/02/Elmar_Solar_MPPT_Race_2021.pdf)

### Setup
create a new MPPT by creating a new object. This creates a Can object that accesses the CAN Bus.
### Usage
Functions:

getters (tell you what the value currently is)

setters (change the values)

send functions (send values to the device through the CAN Bus)

```c++
    int Mppt::MpptParseMsg(); //parses the message and decides which values to change.
```
