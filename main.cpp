#include <iostream>
#include "i2c.h"
#include "mcp23017.h"

int main() {
    Mcp23017 rick = Mcp23017(2, 0x20);
    rick.begin(rick_directions);

    rick.set_state(1, 0);
    std::cout << (int)rick.get_state(1) << std::endl;
    rick.set_state(1, 1);
    std::cout << (int)rick.get_state(1) << std::endl;

    rick.set_state(8, 0);
    std::cout << (int)rick.get_state(8) << std::endl;
    rick.set_state(8, 1);
    std::cout << (int)rick.get_state(8) << std::endl;

    /* Set some more pin states or something idk */

    return 0;
}
