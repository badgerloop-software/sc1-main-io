
/*
 * This is an auto-generated file which is automatically generated whenever the
 * target is built
 */

// TODO: add mbed import statements here

#define totalBytes 298

typedef struct {
  float speed;
  bool driver_eStop;
  bool external_eStop;
  bool battery_eStop;
  bool crash;
  bool door;
  bool mcu_check;
  bool imd_status;
  char state;
  float linear_accel_x;
  float linear_accel_y;
  float linear_accel_z;
  float angular_rate_pitch;
  float angular_rate_roll;
  float angular_rate_yaw;
  float motor_temp;
  float motor_controller_temp;
  float dcdc_temp;
  float driverIO_temp;
  float mainIO_temp;
  float cabin_temp;
  float road_temp;
  float brake_temp;
  float air_temp;
  bool cruise;
  bool left_turn;
  bool right_turn;
  bool hazards;
  bool headlights;
  bool mainIO_heartbeat;
  float accelerator;
  float bus_5V;
  float bus_12V;
  float mainIO_current_in;
  float driverIO_current_in;
  bool power_critical;
  bool power_warning;
  bool power_tc;
  uint16_t tstamp_ms;
  uint8_t tstamp_sc;
  uint8_t tstamp_mn;
  uint8_t tstamp_hr;
  bool mps_enable;
  bool mppt_contactor;
  bool motor_controller_contactor;
  bool low_contactor;
  bool dcdc_valid;
  bool supplemental_valid;
  bool mppt_mode;
  float mppt_current_out;
  float string1_temp;
  float string2_temp;
  float string3_temp;
  float pack_temp;
  float pack_current;
  float pack_voltage;
  float cell_group1_voltage;
  float cell_group2_voltage;
  float cell_group3_voltage;
  float cell_group4_voltage;
  float cell_group5_voltage;
  float cell_group6_voltage;
  float cell_group7_voltage;
  float cell_group8_voltage;
  float cell_group9_voltage;
  float cell_group10_voltage;
  float cell_group11_voltage;
  float cell_group12_voltage;
  float cell_group13_voltage;
  float cell_group14_voltage;
  float cell_group15_voltage;
  float cell_group16_voltage;
  float cell_group17_voltage;
  float cell_group18_voltage;
  float cell_group19_voltage;
  float cell_group20_voltage;
  float cell_group21_voltage;
  float cell_group22_voltage;
  float cell_group23_voltage;
  float cell_group24_voltage;
  float cell_group25_voltage;
  float cell_group26_voltage;
  float cell_group27_voltage;
  float cell_group28_voltage;
  float cell_group29_voltage;
  float cell_group30_voltage;
  float soc;
  float soh;
  float pack_capacity;
  float adaptive_total_capacity;
  bool bps_fault;
  uint8_t fan_speed;
  bool voltage_failsafe;
  bool current_failsafe;
  bool supply_power_failsafe;
  bool memory_failsafe;
  bool relay_failsafe;
  bool bms_canbus_failure;
  float pack_resistance;
  float avg_cell_resistance;
  float bms_input_voltage;
  bool keep_alive;
} data_format;

float get_speed();
void set_speed(float val);

bool get_driver_eStop();
void set_driver_eStop(bool val);

bool get_external_eStop();
void set_external_eStop(bool val);

bool get_battery_eStop();
void set_battery_eStop(bool val);

bool get_crash();
void set_crash(bool val);

bool get_door();
void set_door(bool val);

bool get_mcu_check();
void set_mcu_check(bool val);

bool get_imd_status();
void set_imd_status(bool val);

char get_state();
void set_state(char val);

float get_linear_accel_x();
void set_linear_accel_x(float val);

float get_linear_accel_y();
void set_linear_accel_y(float val);

float get_linear_accel_z();
void set_linear_accel_z(float val);

float get_angular_rate_pitch();
void set_angular_rate_pitch(float val);

float get_angular_rate_roll();
void set_angular_rate_roll(float val);

float get_angular_rate_yaw();
void set_angular_rate_yaw(float val);

float get_motor_temp();
void set_motor_temp(float val);

float get_motor_controller_temp();
void set_motor_controller_temp(float val);

float get_dcdc_temp();
void set_dcdc_temp(float val);

float get_driverIO_temp();
void set_driverIO_temp(float val);

float get_mainIO_temp();
void set_mainIO_temp(float val);

float get_cabin_temp();
void set_cabin_temp(float val);

float get_road_temp();
void set_road_temp(float val);

float get_brake_temp();
void set_brake_temp(float val);

float get_air_temp();
void set_air_temp(float val);

bool get_cruise();
void set_cruise(bool val);

bool get_left_turn();
void set_left_turn(bool val);

bool get_right_turn();
void set_right_turn(bool val);

bool get_hazards();
void set_hazards(bool val);

bool get_headlights();
void set_headlights(bool val);

bool get_mainIO_heartbeat();
void set_mainIO_heartbeat(bool val);

float get_accelerator();
void set_accelerator(float val);

float get_bus_5V();
void set_bus_5V(float val);

float get_bus_12V();
void set_bus_12V(float val);

float get_mainIO_current_in();
void set_mainIO_current_in(float val);

float get_driverIO_current_in();
void set_driverIO_current_in(float val);

bool get_power_critical();
void set_power_critical(bool val);

bool get_power_warning();
void set_power_warning(bool val);

bool get_power_tc();
void set_power_tc(bool val);

uint16_t get_tstamp_ms();
void set_tstamp_ms(uint16_t val);

uint8_t get_tstamp_sc();
void set_tstamp_sc(uint8_t val);

uint8_t get_tstamp_mn();
void set_tstamp_mn(uint8_t val);

uint8_t get_tstamp_hr();
void set_tstamp_hr(uint8_t val);

bool get_mps_enable();
void set_mps_enable(bool val);

bool get_mppt_contactor();
void set_mppt_contactor(bool val);

bool get_motor_controller_contactor();
void set_motor_controller_contactor(bool val);

bool get_low_contactor();
void set_low_contactor(bool val);

bool get_dcdc_valid();
void set_dcdc_valid(bool val);

bool get_supplemental_valid();
void set_supplemental_valid(bool val);

bool get_mppt_mode();
void set_mppt_mode(bool val);

float get_mppt_current_out();
void set_mppt_current_out(float val);

float get_string1_temp();
void set_string1_temp(float val);

float get_string2_temp();
void set_string2_temp(float val);

float get_string3_temp();
void set_string3_temp(float val);

float get_pack_temp();
void set_pack_temp(float val);

float get_pack_current();
void set_pack_current(float val);

float get_pack_voltage();
void set_pack_voltage(float val);

float get_cell_group1_voltage();
void set_cell_group1_voltage(float val);

float get_cell_group2_voltage();
void set_cell_group2_voltage(float val);

float get_cell_group3_voltage();
void set_cell_group3_voltage(float val);

float get_cell_group4_voltage();
void set_cell_group4_voltage(float val);

float get_cell_group5_voltage();
void set_cell_group5_voltage(float val);

float get_cell_group6_voltage();
void set_cell_group6_voltage(float val);

float get_cell_group7_voltage();
void set_cell_group7_voltage(float val);

float get_cell_group8_voltage();
void set_cell_group8_voltage(float val);

float get_cell_group9_voltage();
void set_cell_group9_voltage(float val);

float get_cell_group10_voltage();
void set_cell_group10_voltage(float val);

float get_cell_group11_voltage();
void set_cell_group11_voltage(float val);

float get_cell_group12_voltage();
void set_cell_group12_voltage(float val);

float get_cell_group13_voltage();
void set_cell_group13_voltage(float val);

float get_cell_group14_voltage();
void set_cell_group14_voltage(float val);

float get_cell_group15_voltage();
void set_cell_group15_voltage(float val);

float get_cell_group16_voltage();
void set_cell_group16_voltage(float val);

float get_cell_group17_voltage();
void set_cell_group17_voltage(float val);

float get_cell_group18_voltage();
void set_cell_group18_voltage(float val);

float get_cell_group19_voltage();
void set_cell_group19_voltage(float val);

float get_cell_group20_voltage();
void set_cell_group20_voltage(float val);

float get_cell_group21_voltage();
void set_cell_group21_voltage(float val);

float get_cell_group22_voltage();
void set_cell_group22_voltage(float val);

float get_cell_group23_voltage();
void set_cell_group23_voltage(float val);

float get_cell_group24_voltage();
void set_cell_group24_voltage(float val);

float get_cell_group25_voltage();
void set_cell_group25_voltage(float val);

float get_cell_group26_voltage();
void set_cell_group26_voltage(float val);

float get_cell_group27_voltage();
void set_cell_group27_voltage(float val);

float get_cell_group28_voltage();
void set_cell_group28_voltage(float val);

float get_cell_group29_voltage();
void set_cell_group29_voltage(float val);

float get_cell_group30_voltage();
void set_cell_group30_voltage(float val);

float get_soc();
void set_soc(float val);

float get_soh();
void set_soh(float val);

float get_pack_capacity();
void set_pack_capacity(float val);

float get_adaptive_total_capacity();
void set_adaptive_total_capacity(float val);

bool get_bps_fault();
void set_bps_fault(bool val);

uint8_t get_fan_speed();
void set_fan_speed(uint8_t val);

bool get_voltage_failsafe();
void set_voltage_failsafe(bool val);

bool get_current_failsafe();
void set_current_failsafe(bool val);

bool get_supply_power_failsafe();
void set_supply_power_failsafe(bool val);

bool get_memory_failsafe();
void set_memory_failsafe(bool val);

bool get_relay_failsafe();
void set_relay_failsafe(bool val);

bool get_bms_canbus_failure();
void set_bms_canbus_failure(bool val);

float get_pack_resistance();
void set_pack_resistance(float val);

float get_avg_cell_resistance();
void set_avg_cell_resistance(float val);

float get_bms_input_voltage();
void set_bms_input_voltage(float val);

bool get_keep_alive();
/* Autogenerated Code Ends */

data_format dfwrite;
data_format dfdata;
data_format emptyStruct;

void clearDataFormatRead() { dfread = emptyStruct; }

int runUart();
