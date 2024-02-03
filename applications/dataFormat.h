
/*
 * This is an auto-generated file which is automatically generated whenever the
 * target is built
 */

#ifndef __dataFormat__h__
#define __dataFormat__h__

#include "mbed.h"
#pragma pack(push, 1)

#define TOTAL_BYTES 404

typedef struct {
  float accelerator_pedal;
  float speed;
  uint8_t mcc_state;
  bool fr_telem;
  bool crz_pwr_mode;
  bool crz_spd_mode;
  float crz_pwr_setpt;
  float crz_spd_setpt;
  bool eco;
  bool main_telem;
  bool foot_brake;
  float regen_brake;
  float motor_current;
  float motor_power;
  uint8_t mc_status;
  bool driver_eStop;
  bool external_eStop;
  bool crash;
  bool discharge_enable;
  bool discharge_enabled;
  bool charge_enable;
  bool charge_enabled;
  bool isolation;
  bool mcu_hv_en;
  bool mcu_stat_fdbk;
  bool mppt_contactor;
  bool motor_controller_contactor;
  bool low_contactor;
  float dcdc_current;
  bool dcdc_deg;
  bool use_dcdc;
  float supplemental_current;
  float supplemental_voltage;
  bool supplemental_deg;
  bool use_supp;
  float est_supplemental_soc;
  bool bms_mpio1;
  bool park_brake;
  float air_temp;
  float brake_temp;
  float dcdc_temp;
  float mainIO_temp;
  float motor_controller_temp;
  float motor_temp;
  float road_temp;
  bool l_turn_led_en;
  bool r_turn_led_en;
  bool brake_led_en;
  bool headlights_led_en;
  bool hazards;
  float main_5V_bus;
  float main_12V_bus;
  float main_24V_bus;
  float main_5V_current;
  float main_12V_current;
  float main_24V_current;
  bool bms_can_heartbeat;
  bool mainIO_heartbeat;
  bool mcc_can_heartbeat;
  bool mppt_can_heartbeat;
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
  uint16_t populated_cells;
  float soc;
  float soh;
  float pack_amphours;
  float adaptive_total_capacity;
  uint8_t fan_speed;
  float pack_resistance;
  float bms_input_voltage;
  bool bps_fault;
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
  bool high_voltage_interlock_signal_fault;
  bool precharge_circuit_malfunction;
  bool abnormal_state_of_charge_behavior;
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
  uint16_t tstamp_ms;
  uint8_t tstamp_sc;
  uint8_t tstamp_mn;
  uint8_t tstamp_hr;
  uint64_t tstamp_unix;
  float lat;
  float lon;
  float elev;
} data_format;

float get_accelerator_pedal();
void set_accelerator_pedal(float val);

float get_speed();
void set_speed(float val);

uint8_t get_mcc_state();
void set_mcc_state(uint8_t val);

bool get_fr_telem();
void set_fr_telem(bool val);

bool get_crz_pwr_mode();
void set_crz_pwr_mode(bool val);

bool get_crz_spd_mode();
void set_crz_spd_mode(bool val);

float get_crz_pwr_setpt();
void set_crz_pwr_setpt(float val);

float get_crz_spd_setpt();
void set_crz_spd_setpt(float val);

bool get_eco();
void set_eco(bool val);

bool get_main_telem();
void set_main_telem(bool val);

bool get_foot_brake();
void set_foot_brake(bool val);

float get_regen_brake();
void set_regen_brake(float val);

float get_motor_current();
void set_motor_current(float val);

float get_motor_power();
void set_motor_power(float val);

uint8_t get_mc_status();
void set_mc_status(uint8_t val);

bool get_driver_eStop();
void set_driver_eStop(bool val);

bool get_external_eStop();
void set_external_eStop(bool val);

bool get_crash();
void set_crash(bool val);

bool get_discharge_enable();
void set_discharge_enable(bool val);

bool get_discharge_enabled();
void set_discharge_enabled(bool val);

bool get_charge_enable();
void set_charge_enable(bool val);

bool get_charge_enabled();
void set_charge_enabled(bool val);

bool get_isolation();
void set_isolation(bool val);

bool get_mcu_hv_en();
void set_mcu_hv_en(bool val);

bool get_mcu_stat_fdbk();
void set_mcu_stat_fdbk(bool val);

bool get_mppt_contactor();
void set_mppt_contactor(bool val);

bool get_motor_controller_contactor();
void set_motor_controller_contactor(bool val);

bool get_low_contactor();
void set_low_contactor(bool val);

float get_dcdc_current();
void set_dcdc_current(float val);

bool get_dcdc_deg();
void set_dcdc_deg(bool val);

bool get_use_dcdc();
void set_use_dcdc(bool val);

float get_supplemental_current();
void set_supplemental_current(float val);

float get_supplemental_voltage();
void set_supplemental_voltage(float val);

bool get_supplemental_deg();
void set_supplemental_deg(bool val);

bool get_use_supp();
void set_use_supp(bool val);

float get_est_supplemental_soc();
void set_est_supplemental_soc(float val);

bool get_bms_mpio1();
void set_bms_mpio1(bool val);

bool get_park_brake();
void set_park_brake(bool val);

float get_air_temp();
void set_air_temp(float val);

float get_brake_temp();
void set_brake_temp(float val);

float get_dcdc_temp();
void set_dcdc_temp(float val);

float get_mainIO_temp();
void set_mainIO_temp(float val);

float get_motor_controller_temp();
void set_motor_controller_temp(float val);

float get_motor_temp();
void set_motor_temp(float val);

float get_road_temp();
void set_road_temp(float val);

bool get_l_turn_led_en();
void set_l_turn_led_en(bool val);

bool get_r_turn_led_en();
void set_r_turn_led_en(bool val);

bool get_brake_led_en();
void set_brake_led_en(bool val);

bool get_headlights_led_en();
void set_headlights_led_en(bool val);

bool get_hazards();
void set_hazards(bool val);

float get_main_5V_bus();
void set_main_5V_bus(float val);

float get_main_12V_bus();
void set_main_12V_bus(float val);

float get_main_24V_bus();
void set_main_24V_bus(float val);

float get_main_5V_current();
void set_main_5V_current(float val);

float get_main_12V_current();
void set_main_12V_current(float val);

float get_main_24V_current();
void set_main_24V_current(float val);

bool get_bms_can_heartbeat();
void set_bms_can_heartbeat(bool val);

bool get_mainIO_heartbeat();
void set_mainIO_heartbeat(bool val);

bool get_mcc_can_heartbeat();
void set_mcc_can_heartbeat(bool val);

bool get_mppt_can_heartbeat();
void set_mppt_can_heartbeat(bool val);

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

uint16_t get_populated_cells();
void set_populated_cells(uint16_t val);

float get_soc();
void set_soc(float val);

float get_soh();
void set_soh(float val);

float get_pack_amphours();
void set_pack_amphours(float val);

float get_adaptive_total_capacity();
void set_adaptive_total_capacity(float val);

uint8_t get_fan_speed();
void set_fan_speed(uint8_t val);

float get_pack_resistance();
void set_pack_resistance(float val);

float get_bms_input_voltage();
void set_bms_input_voltage(float val);

bool get_bps_fault();
void set_bps_fault(bool val);

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

bool get_high_voltage_interlock_signal_fault();
void set_high_voltage_interlock_signal_fault(bool val);

bool get_precharge_circuit_malfunction();
void set_precharge_circuit_malfunction(bool val);

bool get_abnormal_state_of_charge_behavior();
void set_abnormal_state_of_charge_behavior(bool val);

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

uint16_t get_tstamp_ms();
void set_tstamp_ms(uint16_t val);

uint8_t get_tstamp_sc();
void set_tstamp_sc(uint8_t val);

uint8_t get_tstamp_mn();
void set_tstamp_mn(uint8_t val);

uint8_t get_tstamp_hr();
void set_tstamp_hr(uint8_t val);

uint64_t get_tstamp_unix();
void set_tstamp_unix(uint64_t val);

float get_lat();
void set_lat(float val);

float get_lon();
void set_lon(float val);

float get_elev();
void set_elev(float val);
/* Autogenerated Code Ends */

bool get_restart_enable();

void cleardfdata();

// starts the threads for reading and writing
int runDataFormat();

#pragma pack(pop)
#endif
