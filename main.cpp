#include "i2c.h"
#include "mcp23017.h"

int main() {
    Mcp23017 rick = Mcp23017(0, 0x54);
    Mcp23017 morty = Mcp23017(1, 0x45);

    morty.get_state(0);
    rick.set_state(0, 4);
    return 0;
}
