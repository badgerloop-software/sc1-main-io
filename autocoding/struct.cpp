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

data_format dfwrite;
data_format dfread;
data_format emptyStruct;