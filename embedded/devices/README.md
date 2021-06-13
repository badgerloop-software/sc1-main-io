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