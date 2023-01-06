#include "gpio.h"

#include <gpiod.h>

#include <iostream>

int Gpio::begin() {
  chip = gpiod_chip_open(name);
  if (!chip) {
    std::cerr << "Error opening gpiod chip\n";
    return -1;
  }
  return 0;
};

int Gpio::write(const vector<pair<unsigned int, bool>> &pins,
                const char *name) {
  struct gpiod_line_bulk bulk[GPIOD_LINE_BULK_MAX_LINES];
  unsigned int offsets[GPIOD_LINE_BULK_MAX_LINES], num_offsets;
  int default_vals[GPIOD_LINE_BULK_MAX_LINES];

  // unpack pins vector
  if ((num_offsets = pins.size()) > GPIOD_LINE_BULK_MAX_LINES) {
    std::cerr << "Too many lines passed\n";
    return -1;
  }

  int i = 0;
  for (auto &p : pins) {
    offsets[i] = p.first;
    default_vals[i] = p.second;
    i++;
  }

  if (gpiod_chip_get_lines(chip, offsets, num_offsets, bulk) < 0) {
    std::cerr << "Failed to get lines\n";
    return -1;
  }

  gpiod_line_release_bulk(bulk);

  if (gpiod_line_request_bulk_output(bulk, name, default_vals) < 0) {
    std::cerr << "Failed to request output on lines\n";
    return -1;
  }

  return 0;
}
