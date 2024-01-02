
/*
 * This is an auto-generated file which is automatically generated whenever the
 * target is built
 */

#ifndef __uartApp__h__
#define __uartApp__h__

#include "mbed.h"
//#include "uart.h"
#pragma pack(push, 1)

#define TOTAL_BYTES 431

typedef struct {
  float speed;
  bool driver_eStop;
  bool external_eStop;
  bool crash;
  bool door;
  bool door_lim_out;
  bool mcu_check;
  bool mcu_stat_fdbk;
  bool mcu_hv_en;
  bool imd_status;
  bool mcu_latch;
  char state;
  bool fr_telem;
  bool fr_out;
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
  bool bl_turn_led_en;
  bool br_turn_led_en;
  bool bc_brake_led_en;
  bool bc_bps_led_en;
  bool headlights_led_en;
  bool fl_turn_led_en;
  bool fr_turn_led_en;
  bool left_turn;
  bool right_turn;
  bool hazards;
  bool headlights;
  bool horn_status;
  bool crz_pwr_mode;
  bool crz_spd_mode;
  float crz_pwr_setpt;
  float crz_spd_setpt;
  uint8_t crz_state;
  bool eco;
  bool main_telem;
  bool brake_status;
  bool mech_brake_status;
  bool parking_brake;
  float accelerator;
  float accelerator_out;
  float motor_current;
  float motor_power;
  uint8_t mc_status;
  bool mppt_can_heartbeat;
  bool mcc_can_heartbeat;
  bool bms_can_heartbeat;
  bool mainIO_heartbeat;
  float main_5V_bus;
  float main_12V_bus;
  float main_vbus;
  float main_vbus_current;
  float driver_5V_bus;
  float driver_12V_bus;
  float driver_vbus;
  float driver_vbus_current;
  bool main_power_critical;
  bool main_power_warning;
  bool main_power_tc;
  bool main_power_valid;
  bool driver_power_critical;
  bool driver_power_warning;
  bool driver_power_tc;
  bool driver_power_valid;
  uint16_t tstamp_ms;
  uint8_t tstamp_sc;
  uint8_t tstamp_mn;
  uint8_t tstamp_hr;
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
  float string1_V_in;
  float string2_V_in;
  float string3_V_in;
  float string1_I_in;
  float string2_I_in;
  float string3_I_in;
  float pack_temp;
  float pack_internal_temp;
  float pack_current;
  float pack_voltage;
  float pack_power;
  float supplemental_voltage;
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
  float cell_group31_voltage;
  uint16_t populated_cells;
  float soc;
  float est_supplemental_soc;
  float soh;
  float pack_capacity;
  float adaptive_total_capacity;
  bool bps_fault;
  bool fan_enable;
  uint8_t fan_speed;
  bool voltage_failsafe;
  bool current_failsafe;
  bool relay_failsafe;
  bool cell_balancing_active;
  bool charge_interlock_failsafe;
  bool thermistor_b_value_table_invalid;
  bool input_power_supply_failsafe;
  bool discharge_limit_enforcement_fault;
  bool charger_safety_relay_fault;
  bool internal_hardware_fault;
  bool internal_heatsink_fault;
  bool internal_software_fault;
  bool highest_cell_voltage_too_high_fault;
  bool lowest_cell_voltage_too_low_fault;
  bool pack_too_hot_fault;
  bool internal_communication_fault;
  bool cell_balancing_stuck_off_fault;
  bool weak_cell_fault;
  bool low_cell_voltage_fault;
  bool open_wiring_fault;
  bool current_sensor_fault;
  bool highest_cell_voltage_over_5V_fault;
  bool cell_asic_fault;
  bool weak_pack_fault;
  bool fan_monitor_fault;
  bool thermistor_fault;
  bool external_communication_fault;
  bool redundant_power_supply_fault;
  bool high_voltage_isolation_fault;
  bool input_power_supply_fault;
  bool charge_limit_enforcement_fault;
  float pack_resistance;
  float bms_input_voltage;
  bool charge_enable;
  bool discharge_enable;
} data_format;

float get_speed();
void set_speed(float val);

bool get_driver_eStop();
void set_driver_eStop(bool val);

bool get_external_eStop();
void set_external_eStop(bool val);

bool get_crash();
void set_crash(bool val);

bool get_door();
void set_door(bool val);

bool get_door_lim_out();
void set_door_lim_out(bool val);

bool get_mcu_check();
void set_mcu_check(bool val);

bool get_mcu_stat_fdbk();
void set_mcu_stat_fdbk(bool val);

bool get_mcu_hv_en();
void set_mcu_hv_en(bool val);

bool get_imd_status();
void set_imd_status(bool val);

bool get_mcu_latch();
void set_mcu_latch(bool val);

char get_state();
void set_state(char val);

bool get_fr_telem();
void set_fr_telem(bool val);

bool get_fr_out();
void set_fr_out(bool val);

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

bool get_bl_turn_led_en();
void set_bl_turn_led_en(bool val);

bool get_br_turn_led_en();
void set_br_turn_led_en(bool val);

bool get_bc_brake_led_en();
void set_bc_brake_led_en(bool val);

bool get_bc_bps_led_en();
void set_bc_bps_led_en(bool val);

bool get_headlights_led_en();
void set_headlights_led_en(bool val);

bool get_fl_turn_led_en();
void set_fl_turn_led_en(bool val);

bool get_fr_turn_led_en();
void set_fr_turn_led_en(bool val);

bool get_left_turn();
void set_left_turn(bool val);

bool get_right_turn();
void set_right_turn(bool val);

bool get_hazards();
void set_hazards(bool val);

bool get_headlights();
void set_headlights(bool val);

bool get_horn_status();
void set_horn_status(bool val);

bool get_crz_pwr_mode();
void set_crz_pwr_mode(bool val);

bool get_crz_spd_mode();
void set_crz_spd_mode(bool val);

float get_crz_pwr_setpt();
void set_crz_pwr_setpt(float val);

float get_crz_spd_setpt();
void set_crz_spd_setpt(float val);

uint8_t get_crz_state();
void set_crz_state(uint8_t val);

bool get_eco();
void set_eco(bool val);

bool get_main_telem();
void set_main_telem(bool val);

bool get_brake_status();
void set_brake_status(bool val);

bool get_mech_brake_status();
void set_mech_brake_status(bool val);

bool get_parking_brake();
void set_parking_brake(bool val);

float get_accelerator();
void set_accelerator(float val);

float get_accelerator_out();
void set_accelerator_out(float val);

float get_motor_current();
void set_motor_current(float val);

float get_motor_power();
void set_motor_power(float val);

uint8_t get_mc_status();
void set_mc_status(uint8_t val);

bool get_mppt_can_heartbeat();
void set_mppt_can_heartbeat(bool val);

bool get_mcc_can_heartbeat();
void set_mcc_can_heartbeat(bool val);

bool get_bms_can_heartbeat();
void set_bms_can_heartbeat(bool val);

bool get_mainIO_heartbeat();
void set_mainIO_heartbeat(bool val);

float get_main_5V_bus();
void set_main_5V_bus(float val);

float get_main_12V_bus();
void set_main_12V_bus(float val);

float get_main_vbus();
void set_main_vbus(float val);

float get_main_vbus_current();
void set_main_vbus_current(float val);

float get_driver_5V_bus();
void set_driver_5V_bus(float val);

float get_driver_12V_bus();
void set_driver_12V_bus(float val);

float get_driver_vbus();
void set_driver_vbus(float val);

float get_driver_vbus_current();
void set_driver_vbus_current(float val);

bool get_main_power_critical();
void set_main_power_critical(bool val);

bool get_main_power_warning();
void set_main_power_warning(bool val);

bool get_main_power_tc();
void set_main_power_tc(bool val);

bool get_main_power_valid();
void set_main_power_valid(bool val);

bool get_driver_power_critical();
void set_driver_power_critical(bool val);

bool get_driver_power_warning();
void set_driver_power_warning(bool val);

bool get_driver_power_tc();
void set_driver_power_tc(bool val);

bool get_driver_power_valid();
void set_driver_power_valid(bool val);

uint16_t get_tstamp_ms();
void set_tstamp_ms(uint16_t val);

uint8_t get_tstamp_sc();
void set_tstamp_sc(uint8_t val);

uint8_t get_tstamp_mn();
void set_tstamp_mn(uint8_t val);

uint8_t get_tstamp_hr();
void set_tstamp_hr(uint8_t val);

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

float get_string1_V_in();
void set_string1_V_in(float val);

float get_string2_V_in();
void set_string2_V_in(float val);

float get_string3_V_in();
void set_string3_V_in(float val);

float get_string1_I_in();
void set_string1_I_in(float val);

float get_string2_I_in();
void set_string2_I_in(float val);

float get_string3_I_in();
void set_string3_I_in(float val);

float get_pack_temp();
void set_pack_temp(float val);

float get_pack_internal_temp();
void set_pack_internal_temp(float val);

float get_pack_current();
void set_pack_current(float val);

float get_pack_voltage();
void set_pack_voltage(float val);

float get_pack_power();
void set_pack_power(float val);

float get_supplemental_voltage();
void set_supplemental_voltage(float val);

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

float get_cell_group31_voltage();
void set_cell_group31_voltage(float val);

uint16_t get_populated_cells();
void set_populated_cells(uint16_t val);

float get_soc();
void set_soc(float val);

float get_est_supplemental_soc();
void set_est_supplemental_soc(float val);

float get_soh();
void set_soh(float val);

float get_pack_capacity();
void set_pack_capacity(float val);

float get_adaptive_total_capacity();
void set_adaptive_total_capacity(float val);

bool get_bps_fault();
void set_bps_fault(bool val);

bool get_fan_enable();
void set_fan_enable(bool val);

uint8_t get_fan_speed();
void set_fan_speed(uint8_t val);

bool get_voltage_failsafe();
void set_voltage_failsafe(bool val);

bool get_current_failsafe();
void set_current_failsafe(bool val);

bool get_relay_failsafe();
void set_relay_failsafe(bool val);

bool get_cell_balancing_active();
void set_cell_balancing_active(bool val);

bool get_charge_interlock_failsafe();
void set_charge_interlock_failsafe(bool val);

bool get_thermistor_b_value_table_invalid();
void set_thermistor_b_value_table_invalid(bool val);

bool get_input_power_supply_failsafe();
void set_input_power_supply_failsafe(bool val);

bool get_discharge_limit_enforcement_fault();
void set_discharge_limit_enforcement_fault(bool val);

bool get_charger_safety_relay_fault();
void set_charger_safety_relay_fault(bool val);

bool get_internal_hardware_fault();
void set_internal_hardware_fault(bool val);

bool get_internal_heatsink_fault();
void set_internal_heatsink_fault(bool val);

bool get_internal_software_fault();
void set_internal_software_fault(bool val);

bool get_highest_cell_voltage_too_high_fault();
void set_highest_cell_voltage_too_high_fault(bool val);

bool get_lowest_cell_voltage_too_low_fault();
void set_lowest_cell_voltage_too_low_fault(bool val);

bool get_pack_too_hot_fault();
void set_pack_too_hot_fault(bool val);

bool get_internal_communication_fault();
void set_internal_communication_fault(bool val);

bool get_cell_balancing_stuck_off_fault();
void set_cell_balancing_stuck_off_fault(bool val);

bool get_weak_cell_fault();
void set_weak_cell_fault(bool val);

bool get_low_cell_voltage_fault();
void set_low_cell_voltage_fault(bool val);

bool get_open_wiring_fault();
void set_open_wiring_fault(bool val);

bool get_current_sensor_fault();
void set_current_sensor_fault(bool val);

bool get_highest_cell_voltage_over_5V_fault();
void set_highest_cell_voltage_over_5V_fault(bool val);

bool get_cell_asic_fault();
void set_cell_asic_fault(bool val);

bool get_weak_pack_fault();
void set_weak_pack_fault(bool val);

bool get_fan_monitor_fault();
void set_fan_monitor_fault(bool val);

bool get_thermistor_fault();
void set_thermistor_fault(bool val);

bool get_external_communication_fault();
void set_external_communication_fault(bool val);

bool get_redundant_power_supply_fault();
void set_redundant_power_supply_fault(bool val);

bool get_high_voltage_isolation_fault();
void set_high_voltage_isolation_fault(bool val);

bool get_input_power_supply_fault();
void set_input_power_supply_fault(bool val);

bool get_charge_limit_enforcement_fault();
void set_charge_limit_enforcement_fault(bool val);

float get_pack_resistance();
void set_pack_resistance(float val);

float get_bms_input_voltage();
void set_bms_input_voltage(float val);

bool get_charge_enable();
void set_charge_enable(bool val);

bool get_discharge_enable();
void set_discharge_enable(bool val);
/* Autogenerated Code Ends */

bool get_restart_enable();

void cleardfdata();

int runUart();

#pragma pack(pop)
#endif
