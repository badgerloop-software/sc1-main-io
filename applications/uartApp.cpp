
/*
 * This is an auto-generated file which is automatically generated whenever the
 * target is built
 */

#include "uartApp.h"

#include <iostream>

#include "rtos.h"
#define NUM_COMMAND_BYTES 1
#define T_MESSAGE_US \
  1000000            // 1 second right now (should be around 1/15 of a second)
#define HEARTBEAT 2  // error state if this # messages that aren't read

Thread thread1;
Thread thread2;
Mutex uart_buffer;

data_format dfwrite;
data_format dfdata;
data_format emptyStruct;

bool restart_enable;

void clearDataFormatRead() { dfdata = emptyStruct; }

void check_shutdown_errors();
void copyDataStructToWriteStruct();

void send_message_thread() {
  while (true) {
    check_shutdown_errors();  // check if mcu_hv_en needs to be set to 0
    copyDataStructToWriteStruct();
    uart_buffer.lock();
    writeUart(&dfwrite, TOTAL_BYTES);
    uart_buffer.unlock();
    wait_us(T_MESSAGE_US);
  }
}

void read_command_thread() {
  int messages_not_received =
      0;  // number of consecutive messages DriverIO fails to send
  bool restart_enable_error = 0;  // check if restart_enable has been 1
  while (true) {
    uart_buffer.lock();
    restart_enable = 0;
    // set mcu_hv_en to 0 (error state) if HEARTBEAT consecutive messages aren't
    // read
    if (readUart(&restart_enable, NUM_COMMAND_BYTES) == 0) {
      if (++messages_not_received == HEARTBEAT) {
        set_mcu_hv_en(0);
      }
    } else {  // a message was read
      messages_not_received = 0;
      // check that we've received at least one restart_enable == 1 before we
      // set mcu_hv_en high again
      if (restart_enable) {
        restart_enable_error = true;
      }
      if (restart_enable == 0 && get_mcu_hv_en() == 0 && restart_enable_error) {
        set_mcu_hv_en(1);
        restart_enable_error = false;
      }
    }
    uart_buffer.unlock();
    wait_us(T_MESSAGE_US);
  }
}

int runUart() {
  initUart();
  thread1.start(read_command_thread);
  thread2.start(send_message_thread);
  return 0;
}

Mutex restart_enable_mutex;

bool get_restart_enable() {
  restart_enable_mutex.lock();
  bool val = restart_enable;
  restart_enable_mutex.unlock();
  return val;
}

Mutex speed_mutex;
Mutex driver_eStop_mutex;
Mutex external_eStop_mutex;
Mutex crash_mutex;
Mutex door_mutex;
Mutex door_lim_out_mutex;
Mutex mcu_check_mutex;
Mutex mcu_stat_fdbk_mutex;
Mutex mcu_hv_en_mutex;
Mutex imd_status_mutex;
Mutex mcu_latch_mutex;
Mutex state_mutex;
Mutex fr_telem_mutex;
Mutex fr_out_mutex;
Mutex linear_accel_x_mutex;
Mutex linear_accel_y_mutex;
Mutex linear_accel_z_mutex;
Mutex angular_rate_pitch_mutex;
Mutex angular_rate_roll_mutex;
Mutex angular_rate_yaw_mutex;
Mutex motor_temp_mutex;
Mutex motor_controller_temp_mutex;
Mutex dcdc_temp_mutex;
Mutex driverIO_temp_mutex;
Mutex mainIO_temp_mutex;
Mutex cabin_temp_mutex;
Mutex road_temp_mutex;
Mutex brake_temp_mutex;
Mutex air_temp_mutex;
Mutex bl_turn_led_en_mutex;
Mutex br_turn_led_en_mutex;
Mutex bc_brake_led_en_mutex;
Mutex bc_bps_led_en_mutex;
Mutex headlights_led_en_mutex;
Mutex fl_turn_led_en_mutex;
Mutex fr_turn_led_en_mutex;
Mutex left_turn_mutex;
Mutex right_turn_mutex;
Mutex hazards_mutex;
Mutex headlights_mutex;
Mutex horn_status_mutex;
Mutex crz_pwr_mode_mutex;
Mutex crz_spd_mode_mutex;
Mutex crz_pwr_setpt_mutex;
Mutex crz_spd_setpt_mutex;
Mutex crz_state_mutex;
Mutex eco_mutex;
Mutex main_telem_mutex;
Mutex brake_status_mutex;
Mutex mech_brake_status_mutex;
Mutex parking_brake_mutex;
Mutex accelerator_mutex;
Mutex accelerator_out_mutex;
Mutex motor_current_mutex;
Mutex motor_power_mutex;
Mutex mc_status_mutex;
Mutex mppt_can_heartbeat_mutex;
Mutex mcc_can_heartbeat_mutex;
Mutex bms_can_heartbeat_mutex;
Mutex mainIO_heartbeat_mutex;
Mutex main_5V_bus_mutex;
Mutex main_12V_bus_mutex;
Mutex main_vbus_mutex;
Mutex main_vbus_current_mutex;
Mutex driver_5V_bus_mutex;
Mutex driver_12V_bus_mutex;
Mutex driver_vbus_mutex;
Mutex driver_vbus_current_mutex;
Mutex main_power_critical_mutex;
Mutex main_power_warning_mutex;
Mutex main_power_tc_mutex;
Mutex main_power_valid_mutex;
Mutex driver_power_critical_mutex;
Mutex driver_power_warning_mutex;
Mutex driver_power_tc_mutex;
Mutex driver_power_valid_mutex;
Mutex tstamp_ms_mutex;
Mutex tstamp_sc_mutex;
Mutex tstamp_mn_mutex;
Mutex tstamp_hr_mutex;
Mutex mppt_contactor_mutex;
Mutex motor_controller_contactor_mutex;
Mutex low_contactor_mutex;
Mutex dcdc_valid_mutex;
Mutex supplemental_valid_mutex;
Mutex mppt_mode_mutex;
Mutex mppt_current_out_mutex;
Mutex string1_temp_mutex;
Mutex string2_temp_mutex;
Mutex string3_temp_mutex;
Mutex pack_temp_mutex;
Mutex pack_internal_temp_mutex;
Mutex pack_current_mutex;
Mutex pack_voltage_mutex;
Mutex pack_power_mutex;
Mutex supplemental_voltage_mutex;
Mutex cell_group1_voltage_mutex;
Mutex cell_group2_voltage_mutex;
Mutex cell_group3_voltage_mutex;
Mutex cell_group4_voltage_mutex;
Mutex cell_group5_voltage_mutex;
Mutex cell_group6_voltage_mutex;
Mutex cell_group7_voltage_mutex;
Mutex cell_group8_voltage_mutex;
Mutex cell_group9_voltage_mutex;
Mutex cell_group10_voltage_mutex;
Mutex cell_group11_voltage_mutex;
Mutex cell_group12_voltage_mutex;
Mutex cell_group13_voltage_mutex;
Mutex cell_group14_voltage_mutex;
Mutex cell_group15_voltage_mutex;
Mutex cell_group16_voltage_mutex;
Mutex cell_group17_voltage_mutex;
Mutex cell_group18_voltage_mutex;
Mutex cell_group19_voltage_mutex;
Mutex cell_group20_voltage_mutex;
Mutex cell_group21_voltage_mutex;
Mutex cell_group22_voltage_mutex;
Mutex cell_group23_voltage_mutex;
Mutex cell_group24_voltage_mutex;
Mutex cell_group25_voltage_mutex;
Mutex cell_group26_voltage_mutex;
Mutex cell_group27_voltage_mutex;
Mutex cell_group28_voltage_mutex;
Mutex cell_group29_voltage_mutex;
Mutex cell_group30_voltage_mutex;
Mutex cell_group31_voltage_mutex;
Mutex populated_cells_mutex;
Mutex soc_mutex;
Mutex est_supplemental_soc_mutex;
Mutex soh_mutex;
Mutex pack_capacity_mutex;
Mutex adaptive_total_capacity_mutex;
Mutex bps_fault_mutex;
Mutex fan_enable_mutex;
Mutex fan_speed_mutex;
Mutex voltage_failsafe_mutex;
Mutex current_failsafe_mutex;
Mutex relay_failsafe_mutex;
Mutex cell_balancing_active_mutex;
Mutex charge_interlock_failsafe_mutex;
Mutex thermistor_b_value_table_invalid_mutex;
Mutex input_power_supply_failsafe_mutex;
Mutex discharge_limit_enforcement_fault_mutex;
Mutex charger_safety_relay_fault_mutex;
Mutex internal_hardware_fault_mutex;
Mutex internal_heatsink_fault_mutex;
Mutex internal_software_fault_mutex;
Mutex highest_cell_voltage_too_high_fault_mutex;
Mutex lowest_cell_voltage_too_low_fault_mutex;
Mutex pack_too_hot_fault_mutex;
Mutex internal_communication_fault_mutex;
Mutex cell_balancing_stuck_off_fault_mutex;
Mutex weak_cell_fault_mutex;
Mutex low_cell_voltage_fault_mutex;
Mutex open_wiring_fault_mutex;
Mutex current_sensor_fault_mutex;
Mutex highest_cell_voltage_over_5V_fault_mutex;
Mutex cell_asic_fault_mutex;
Mutex weak_pack_fault_mutex;
Mutex fan_monitor_fault_mutex;
Mutex thermistor_fault_mutex;
Mutex external_communication_fault_mutex;
Mutex redundant_power_supply_fault_mutex;
Mutex high_voltage_isolation_fault_mutex;
Mutex input_power_supply_fault_mutex;
Mutex charge_limit_enforcement_fault_mutex;
Mutex pack_resistance_mutex;
Mutex bms_input_voltage_mutex;
Mutex charge_enable_mutex;
Mutex discharge_enable_mutex;

void copyDataStructToWriteStruct() {
  // set pack power
  float v = get_pack_voltage();
  float i = get_pack_current();
  set_pack_power(i * v);

  dfwrite.speed = get_speed();
  dfwrite.driver_eStop = get_driver_eStop();
  dfwrite.external_eStop = get_external_eStop();
  dfwrite.crash = get_crash();
  dfwrite.door = get_door();
  dfwrite.door_lim_out = get_door_lim_out();
  dfwrite.mcu_check = get_mcu_check();
  dfwrite.mcu_stat_fdbk = get_mcu_stat_fdbk();
  dfwrite.mcu_hv_en = get_mcu_hv_en();
  dfwrite.imd_status = get_imd_status();
  dfwrite.mcu_latch = get_mcu_latch();
  dfwrite.state = get_state();
  dfwrite.fr_telem = get_fr_telem();
  dfwrite.fr_out = get_fr_out();
  dfwrite.linear_accel_x = get_linear_accel_x();
  dfwrite.linear_accel_y = get_linear_accel_y();
  dfwrite.linear_accel_z = get_linear_accel_z();
  dfwrite.angular_rate_pitch = get_angular_rate_pitch();
  dfwrite.angular_rate_roll = get_angular_rate_roll();
  dfwrite.angular_rate_yaw = get_angular_rate_yaw();
  dfwrite.motor_temp = get_motor_temp();
  dfwrite.motor_controller_temp = get_motor_controller_temp();
  dfwrite.dcdc_temp = get_dcdc_temp();
  dfwrite.driverIO_temp = get_driverIO_temp();
  dfwrite.mainIO_temp = get_mainIO_temp();
  dfwrite.cabin_temp = get_cabin_temp();
  dfwrite.road_temp = get_road_temp();
  dfwrite.brake_temp = get_brake_temp();
  dfwrite.air_temp = get_air_temp();
  dfwrite.bl_turn_led_en = get_bl_turn_led_en();
  dfwrite.br_turn_led_en = get_br_turn_led_en();
  dfwrite.bc_brake_led_en = get_bc_brake_led_en();
  dfwrite.bc_bps_led_en = get_bc_bps_led_en();
  dfwrite.headlights_led_en = get_headlights_led_en();
  dfwrite.fl_turn_led_en = get_fl_turn_led_en();
  dfwrite.fr_turn_led_en = get_fr_turn_led_en();
  dfwrite.left_turn = get_left_turn();
  dfwrite.right_turn = get_right_turn();
  dfwrite.hazards = get_hazards();
  dfwrite.headlights = get_headlights();
  dfwrite.horn_status = get_horn_status();
  dfwrite.crz_pwr_mode = get_crz_pwr_mode();
  dfwrite.crz_spd_mode = get_crz_spd_mode();
  dfwrite.crz_pwr_setpt = get_crz_pwr_setpt();
  dfwrite.crz_spd_setpt = get_crz_spd_setpt();
  dfwrite.crz_state = get_crz_state();
  dfwrite.eco = get_eco();
  dfwrite.main_telem = get_main_telem();
  dfwrite.brake_status = get_brake_status();
  dfwrite.mech_brake_status = get_mech_brake_status();
  dfwrite.parking_brake = get_parking_brake();
  dfwrite.accelerator = get_accelerator();
  dfwrite.accelerator_out = get_accelerator_out();
  dfwrite.motor_current = get_motor_current();
  dfwrite.motor_power = get_motor_power();
  dfwrite.mc_status = get_mc_status();
  dfwrite.mppt_can_heartbeat = get_mppt_can_heartbeat();
  dfwrite.mcc_can_heartbeat = get_mcc_can_heartbeat();
  dfwrite.bms_can_heartbeat = get_bms_can_heartbeat();
  dfwrite.mainIO_heartbeat = get_mainIO_heartbeat();
  dfwrite.main_5V_bus = get_main_5V_bus();
  dfwrite.main_12V_bus = get_main_12V_bus();
  dfwrite.main_vbus = get_main_vbus();
  dfwrite.main_vbus_current = get_main_vbus_current();
  dfwrite.driver_5V_bus = get_driver_5V_bus();
  dfwrite.driver_12V_bus = get_driver_12V_bus();
  dfwrite.driver_vbus = get_driver_vbus();
  dfwrite.driver_vbus_current = get_driver_vbus_current();
  dfwrite.main_power_critical = get_main_power_critical();
  dfwrite.main_power_warning = get_main_power_warning();
  dfwrite.main_power_tc = get_main_power_tc();
  dfwrite.main_power_valid = get_main_power_valid();
  dfwrite.driver_power_critical = get_driver_power_critical();
  dfwrite.driver_power_warning = get_driver_power_warning();
  dfwrite.driver_power_tc = get_driver_power_tc();
  dfwrite.driver_power_valid = get_driver_power_valid();
  dfwrite.tstamp_ms = get_tstamp_ms();
  dfwrite.tstamp_sc = get_tstamp_sc();
  dfwrite.tstamp_mn = get_tstamp_mn();
  dfwrite.tstamp_hr = get_tstamp_hr();
  dfwrite.mppt_contactor = get_mppt_contactor();
  dfwrite.motor_controller_contactor = get_motor_controller_contactor();
  dfwrite.low_contactor = get_low_contactor();
  dfwrite.dcdc_valid = get_dcdc_valid();
  dfwrite.supplemental_valid = get_supplemental_valid();
  dfwrite.mppt_mode = get_mppt_mode();
  dfwrite.mppt_current_out = get_mppt_current_out();
  dfwrite.string1_temp = get_string1_temp();
  dfwrite.string2_temp = get_string2_temp();
  dfwrite.string3_temp = get_string3_temp();
  dfwrite.pack_temp = get_pack_temp();
  dfwrite.pack_internal_temp = get_pack_internal_temp();
  dfwrite.pack_current = get_pack_current();
  dfwrite.pack_voltage = get_pack_voltage();
  dfwrite.pack_power = get_pack_power();
  dfwrite.supplemental_voltage = get_supplemental_voltage();
  dfwrite.cell_group1_voltage = get_cell_group1_voltage();
  dfwrite.cell_group2_voltage = get_cell_group2_voltage();
  dfwrite.cell_group3_voltage = get_cell_group3_voltage();
  dfwrite.cell_group4_voltage = get_cell_group4_voltage();
  dfwrite.cell_group5_voltage = get_cell_group5_voltage();
  dfwrite.cell_group6_voltage = get_cell_group6_voltage();
  dfwrite.cell_group7_voltage = get_cell_group7_voltage();
  dfwrite.cell_group8_voltage = get_cell_group8_voltage();
  dfwrite.cell_group9_voltage = get_cell_group9_voltage();
  dfwrite.cell_group10_voltage = get_cell_group10_voltage();
  dfwrite.cell_group11_voltage = get_cell_group11_voltage();
  dfwrite.cell_group12_voltage = get_cell_group12_voltage();
  dfwrite.cell_group13_voltage = get_cell_group13_voltage();
  dfwrite.cell_group14_voltage = get_cell_group14_voltage();
  dfwrite.cell_group15_voltage = get_cell_group15_voltage();
  dfwrite.cell_group16_voltage = get_cell_group16_voltage();
  dfwrite.cell_group17_voltage = get_cell_group17_voltage();
  dfwrite.cell_group18_voltage = get_cell_group18_voltage();
  dfwrite.cell_group19_voltage = get_cell_group19_voltage();
  dfwrite.cell_group20_voltage = get_cell_group20_voltage();
  dfwrite.cell_group21_voltage = get_cell_group21_voltage();
  dfwrite.cell_group22_voltage = get_cell_group22_voltage();
  dfwrite.cell_group23_voltage = get_cell_group23_voltage();
  dfwrite.cell_group24_voltage = get_cell_group24_voltage();
  dfwrite.cell_group25_voltage = get_cell_group25_voltage();
  dfwrite.cell_group26_voltage = get_cell_group26_voltage();
  dfwrite.cell_group27_voltage = get_cell_group27_voltage();
  dfwrite.cell_group28_voltage = get_cell_group28_voltage();
  dfwrite.cell_group29_voltage = get_cell_group29_voltage();
  dfwrite.cell_group30_voltage = get_cell_group30_voltage();
  dfwrite.cell_group31_voltage = get_cell_group31_voltage();
  dfwrite.populated_cells = get_populated_cells();
  dfwrite.soc = get_soc();
  dfwrite.est_supplemental_soc = get_est_supplemental_soc();
  dfwrite.soh = get_soh();
  dfwrite.pack_capacity = get_pack_capacity();
  dfwrite.adaptive_total_capacity = get_adaptive_total_capacity();
  dfwrite.bps_fault = get_bps_fault();
  dfwrite.fan_enable = get_fan_enable();
  dfwrite.fan_speed = get_fan_speed();
  dfwrite.voltage_failsafe = get_voltage_failsafe();
  dfwrite.current_failsafe = get_current_failsafe();
  dfwrite.relay_failsafe = get_relay_failsafe();
  dfwrite.cell_balancing_active = get_cell_balancing_active();
  dfwrite.charge_interlock_failsafe = get_charge_interlock_failsafe();
  dfwrite.thermistor_b_value_table_invalid =
      get_thermistor_b_value_table_invalid();
  dfwrite.input_power_supply_failsafe = get_input_power_supply_failsafe();
  dfwrite.discharge_limit_enforcement_fault =
      get_discharge_limit_enforcement_fault();
  dfwrite.charger_safety_relay_fault = get_charger_safety_relay_fault();
  dfwrite.internal_hardware_fault = get_internal_hardware_fault();
  dfwrite.internal_heatsink_fault = get_internal_heatsink_fault();
  dfwrite.internal_software_fault = get_internal_software_fault();
  dfwrite.highest_cell_voltage_too_high_fault =
      get_highest_cell_voltage_too_high_fault();
  dfwrite.lowest_cell_voltage_too_low_fault =
      get_lowest_cell_voltage_too_low_fault();
  dfwrite.pack_too_hot_fault = get_pack_too_hot_fault();
  dfwrite.internal_communication_fault = get_internal_communication_fault();
  dfwrite.cell_balancing_stuck_off_fault = get_cell_balancing_stuck_off_fault();
  dfwrite.weak_cell_fault = get_weak_cell_fault();
  dfwrite.low_cell_voltage_fault = get_low_cell_voltage_fault();
  dfwrite.open_wiring_fault = get_open_wiring_fault();
  dfwrite.current_sensor_fault = get_current_sensor_fault();
  dfwrite.highest_cell_voltage_over_5V_fault =
      get_highest_cell_voltage_over_5V_fault();
  dfwrite.cell_asic_fault = get_cell_asic_fault();
  dfwrite.weak_pack_fault = get_weak_pack_fault();
  dfwrite.fan_monitor_fault = get_fan_monitor_fault();
  dfwrite.thermistor_fault = get_thermistor_fault();
  dfwrite.external_communication_fault = get_external_communication_fault();
  dfwrite.redundant_power_supply_fault = get_redundant_power_supply_fault();
  dfwrite.high_voltage_isolation_fault = get_high_voltage_isolation_fault();
  dfwrite.input_power_supply_fault = get_input_power_supply_fault();
  dfwrite.charge_limit_enforcement_fault = get_charge_limit_enforcement_fault();
  dfwrite.pack_resistance = get_pack_resistance();
  dfwrite.bms_input_voltage = get_bms_input_voltage();
  dfwrite.charge_enable = get_charge_enable();
  dfwrite.discharge_enable = get_discharge_enable();
}

float get_speed() {
  speed_mutex.lock();
  float val = dfdata.speed;
  speed_mutex.unlock();
  return val;
}
void set_speed(float val) {
  speed_mutex.lock();
  dfdata.speed = val;
  speed_mutex.unlock();
}

bool get_driver_eStop() {
  driver_eStop_mutex.lock();
  bool val = dfdata.driver_eStop;
  driver_eStop_mutex.unlock();
  return val;
}
void set_driver_eStop(bool val) {
  driver_eStop_mutex.lock();
  dfdata.driver_eStop = val;
  driver_eStop_mutex.unlock();
}

bool get_external_eStop() {
  external_eStop_mutex.lock();
  bool val = dfdata.external_eStop;
  external_eStop_mutex.unlock();
  return val;
}
void set_external_eStop(bool val) {
  external_eStop_mutex.lock();
  dfdata.external_eStop = val;
  external_eStop_mutex.unlock();
}

bool get_crash() {
  crash_mutex.lock();
  bool val = dfdata.crash;
  crash_mutex.unlock();
  return val;
}
void set_crash(bool val) {
  crash_mutex.lock();
  dfdata.crash = val;
  crash_mutex.unlock();
}

bool get_door() {
  door_mutex.lock();
  bool val = dfdata.door;
  door_mutex.unlock();
  return val;
}
void set_door(bool val) {
  door_mutex.lock();
  dfdata.door = val;
  door_mutex.unlock();
}

bool get_door_lim_out() {
  door_lim_out_mutex.lock();
  bool val = dfdata.door_lim_out;
  door_lim_out_mutex.unlock();
  return val;
}
void set_door_lim_out(bool val) {
  door_lim_out_mutex.lock();
  dfdata.door_lim_out = val;
  door_lim_out_mutex.unlock();
}

bool get_mcu_check() {
  mcu_check_mutex.lock();
  bool val = dfdata.mcu_check;
  mcu_check_mutex.unlock();
  return val;
}
void set_mcu_check(bool val) {
  mcu_check_mutex.lock();
  dfdata.mcu_check = val;
  mcu_check_mutex.unlock();
}

bool get_mcu_stat_fdbk() {
  mcu_stat_fdbk_mutex.lock();
  bool val = dfdata.mcu_stat_fdbk;
  mcu_stat_fdbk_mutex.unlock();
  return val;
}
void set_mcu_stat_fdbk(bool val) {
  mcu_stat_fdbk_mutex.lock();
  dfdata.mcu_stat_fdbk = val;
  mcu_stat_fdbk_mutex.unlock();
}

bool get_mcu_hv_en() {
  mcu_hv_en_mutex.lock();
  bool val = dfdata.mcu_hv_en;
  mcu_hv_en_mutex.unlock();
  return val;
}
void set_mcu_hv_en(bool val) {
  mcu_hv_en_mutex.lock();
  dfdata.mcu_hv_en = val;
  mcu_hv_en_mutex.unlock();
}

bool get_imd_status() {
  imd_status_mutex.lock();
  bool val = dfdata.imd_status;
  imd_status_mutex.unlock();
  return val;
}
void set_imd_status(bool val) {
  imd_status_mutex.lock();
  dfdata.imd_status = val;
  imd_status_mutex.unlock();
}

bool get_mcu_latch() {
  mcu_latch_mutex.lock();
  bool val = dfdata.mcu_latch;
  mcu_latch_mutex.unlock();
  return val;
}
void set_mcu_latch(bool val) {
  mcu_latch_mutex.lock();
  dfdata.mcu_latch = val;
  mcu_latch_mutex.unlock();
}

char get_state() {
  state_mutex.lock();
  char val = dfdata.state;
  state_mutex.unlock();
  return val;
}
void set_state(char val) {
  state_mutex.lock();
  dfdata.state = val;
  state_mutex.unlock();
}

bool get_fr_telem() {
  fr_telem_mutex.lock();
  bool val = dfdata.fr_telem;
  fr_telem_mutex.unlock();
  return val;
}
void set_fr_telem(bool val) {
  fr_telem_mutex.lock();
  dfdata.fr_telem = val;
  fr_telem_mutex.unlock();
}

bool get_fr_out() {
  fr_out_mutex.lock();
  bool val = dfdata.fr_out;
  fr_out_mutex.unlock();
  return val;
}
void set_fr_out(bool val) {
  fr_out_mutex.lock();
  dfdata.fr_out = val;
  fr_out_mutex.unlock();
}

float get_linear_accel_x() {
  linear_accel_x_mutex.lock();
  float val = dfdata.linear_accel_x;
  linear_accel_x_mutex.unlock();
  return val;
}
void set_linear_accel_x(float val) {
  linear_accel_x_mutex.lock();
  dfdata.linear_accel_x = val;
  linear_accel_x_mutex.unlock();
}

float get_linear_accel_y() {
  linear_accel_y_mutex.lock();
  float val = dfdata.linear_accel_y;
  linear_accel_y_mutex.unlock();
  return val;
}
void set_linear_accel_y(float val) {
  linear_accel_y_mutex.lock();
  dfdata.linear_accel_y = val;
  linear_accel_y_mutex.unlock();
}

float get_linear_accel_z() {
  linear_accel_z_mutex.lock();
  float val = dfdata.linear_accel_z;
  linear_accel_z_mutex.unlock();
  return val;
}
void set_linear_accel_z(float val) {
  linear_accel_z_mutex.lock();
  dfdata.linear_accel_z = val;
  linear_accel_z_mutex.unlock();
}

float get_angular_rate_pitch() {
  angular_rate_pitch_mutex.lock();
  float val = dfdata.angular_rate_pitch;
  angular_rate_pitch_mutex.unlock();
  return val;
}
void set_angular_rate_pitch(float val) {
  angular_rate_pitch_mutex.lock();
  dfdata.angular_rate_pitch = val;
  angular_rate_pitch_mutex.unlock();
}

float get_angular_rate_roll() {
  angular_rate_roll_mutex.lock();
  float val = dfdata.angular_rate_roll;
  angular_rate_roll_mutex.unlock();
  return val;
}
void set_angular_rate_roll(float val) {
  angular_rate_roll_mutex.lock();
  dfdata.angular_rate_roll = val;
  angular_rate_roll_mutex.unlock();
}

float get_angular_rate_yaw() {
  angular_rate_yaw_mutex.lock();
  float val = dfdata.angular_rate_yaw;
  angular_rate_yaw_mutex.unlock();
  return val;
}
void set_angular_rate_yaw(float val) {
  angular_rate_yaw_mutex.lock();
  dfdata.angular_rate_yaw = val;
  angular_rate_yaw_mutex.unlock();
}

float get_motor_temp() {
  motor_temp_mutex.lock();
  float val = dfdata.motor_temp;
  motor_temp_mutex.unlock();
  return val;
}
void set_motor_temp(float val) {
  motor_temp_mutex.lock();
  dfdata.motor_temp = val;
  motor_temp_mutex.unlock();
}

float get_motor_controller_temp() {
  motor_controller_temp_mutex.lock();
  float val = dfdata.motor_controller_temp;
  motor_controller_temp_mutex.unlock();
  return val;
}
void set_motor_controller_temp(float val) {
  motor_controller_temp_mutex.lock();
  dfdata.motor_controller_temp = val;
  motor_controller_temp_mutex.unlock();
}

float get_dcdc_temp() {
  dcdc_temp_mutex.lock();
  float val = dfdata.dcdc_temp;
  dcdc_temp_mutex.unlock();
  return val;
}
void set_dcdc_temp(float val) {
  dcdc_temp_mutex.lock();
  dfdata.dcdc_temp = val;
  dcdc_temp_mutex.unlock();
}

float get_driverIO_temp() {
  driverIO_temp_mutex.lock();
  float val = dfdata.driverIO_temp;
  driverIO_temp_mutex.unlock();
  return val;
}
void set_driverIO_temp(float val) {
  driverIO_temp_mutex.lock();
  dfdata.driverIO_temp = val;
  driverIO_temp_mutex.unlock();
}

float get_mainIO_temp() {
  mainIO_temp_mutex.lock();
  float val = dfdata.mainIO_temp;
  mainIO_temp_mutex.unlock();
  return val;
}
void set_mainIO_temp(float val) {
  mainIO_temp_mutex.lock();
  dfdata.mainIO_temp = val;
  mainIO_temp_mutex.unlock();
}

float get_cabin_temp() {
  cabin_temp_mutex.lock();
  float val = dfdata.cabin_temp;
  cabin_temp_mutex.unlock();
  return val;
}
void set_cabin_temp(float val) {
  cabin_temp_mutex.lock();
  dfdata.cabin_temp = val;
  cabin_temp_mutex.unlock();
}

float get_road_temp() {
  road_temp_mutex.lock();
  float val = dfdata.road_temp;
  road_temp_mutex.unlock();
  return val;
}
void set_road_temp(float val) {
  road_temp_mutex.lock();
  dfdata.road_temp = val;
  road_temp_mutex.unlock();
}

float get_brake_temp() {
  brake_temp_mutex.lock();
  float val = dfdata.brake_temp;
  brake_temp_mutex.unlock();
  return val;
}
void set_brake_temp(float val) {
  brake_temp_mutex.lock();
  dfdata.brake_temp = val;
  brake_temp_mutex.unlock();
}

float get_air_temp() {
  air_temp_mutex.lock();
  float val = dfdata.air_temp;
  air_temp_mutex.unlock();
  return val;
}
void set_air_temp(float val) {
  air_temp_mutex.lock();
  dfdata.air_temp = val;
  air_temp_mutex.unlock();
}

bool get_bl_turn_led_en() {
  bl_turn_led_en_mutex.lock();
  bool val = dfdata.bl_turn_led_en;
  bl_turn_led_en_mutex.unlock();
  return val;
}
void set_bl_turn_led_en(bool val) {
  bl_turn_led_en_mutex.lock();
  dfdata.bl_turn_led_en = val;
  bl_turn_led_en_mutex.unlock();
}

bool get_br_turn_led_en() {
  br_turn_led_en_mutex.lock();
  bool val = dfdata.br_turn_led_en;
  br_turn_led_en_mutex.unlock();
  return val;
}
void set_br_turn_led_en(bool val) {
  br_turn_led_en_mutex.lock();
  dfdata.br_turn_led_en = val;
  br_turn_led_en_mutex.unlock();
}

bool get_bc_brake_led_en() {
  bc_brake_led_en_mutex.lock();
  bool val = dfdata.bc_brake_led_en;
  bc_brake_led_en_mutex.unlock();
  return val;
}
void set_bc_brake_led_en(bool val) {
  bc_brake_led_en_mutex.lock();
  dfdata.bc_brake_led_en = val;
  bc_brake_led_en_mutex.unlock();
}

bool get_bc_bps_led_en() {
  bc_bps_led_en_mutex.lock();
  bool val = dfdata.bc_bps_led_en;
  bc_bps_led_en_mutex.unlock();
  return val;
}
void set_bc_bps_led_en(bool val) {
  bc_bps_led_en_mutex.lock();
  dfdata.bc_bps_led_en = val;
  bc_bps_led_en_mutex.unlock();
}

bool get_headlights_led_en() {
  headlights_led_en_mutex.lock();
  bool val = dfdata.headlights_led_en;
  headlights_led_en_mutex.unlock();
  return val;
}
void set_headlights_led_en(bool val) {
  headlights_led_en_mutex.lock();
  dfdata.headlights_led_en = val;
  headlights_led_en_mutex.unlock();
}

bool get_fl_turn_led_en() {
  fl_turn_led_en_mutex.lock();
  bool val = dfdata.fl_turn_led_en;
  fl_turn_led_en_mutex.unlock();
  return val;
}
void set_fl_turn_led_en(bool val) {
  fl_turn_led_en_mutex.lock();
  dfdata.fl_turn_led_en = val;
  fl_turn_led_en_mutex.unlock();
}

bool get_fr_turn_led_en() {
  fr_turn_led_en_mutex.lock();
  bool val = dfdata.fr_turn_led_en;
  fr_turn_led_en_mutex.unlock();
  return val;
}
void set_fr_turn_led_en(bool val) {
  fr_turn_led_en_mutex.lock();
  dfdata.fr_turn_led_en = val;
  fr_turn_led_en_mutex.unlock();
}

bool get_left_turn() {
  left_turn_mutex.lock();
  bool val = dfdata.left_turn;
  left_turn_mutex.unlock();
  return val;
}
void set_left_turn(bool val) {
  left_turn_mutex.lock();
  dfdata.left_turn = val;
  left_turn_mutex.unlock();
}

bool get_right_turn() {
  right_turn_mutex.lock();
  bool val = dfdata.right_turn;
  right_turn_mutex.unlock();
  return val;
}
void set_right_turn(bool val) {
  right_turn_mutex.lock();
  dfdata.right_turn = val;
  right_turn_mutex.unlock();
}

bool get_hazards() {
  hazards_mutex.lock();
  bool val = dfdata.hazards;
  hazards_mutex.unlock();
  return val;
}
void set_hazards(bool val) {
  hazards_mutex.lock();
  dfdata.hazards = val;
  hazards_mutex.unlock();
}

bool get_headlights() {
  headlights_mutex.lock();
  bool val = dfdata.headlights;
  headlights_mutex.unlock();
  return val;
}
void set_headlights(bool val) {
  headlights_mutex.lock();
  dfdata.headlights = val;
  headlights_mutex.unlock();
}

bool get_horn_status() {
  horn_status_mutex.lock();
  bool val = dfdata.horn_status;
  horn_status_mutex.unlock();
  return val;
}
void set_horn_status(bool val) {
  horn_status_mutex.lock();
  dfdata.horn_status = val;
  horn_status_mutex.unlock();
}

bool get_crz_pwr_mode() {
  crz_pwr_mode_mutex.lock();
  bool val = dfdata.crz_pwr_mode;
  crz_pwr_mode_mutex.unlock();
  return val;
}
void set_crz_pwr_mode(bool val) {
  crz_pwr_mode_mutex.lock();
  dfdata.crz_pwr_mode = val;
  crz_pwr_mode_mutex.unlock();
}

bool get_crz_spd_mode() {
  crz_spd_mode_mutex.lock();
  bool val = dfdata.crz_spd_mode;
  crz_spd_mode_mutex.unlock();
  return val;
}
void set_crz_spd_mode(bool val) {
  crz_spd_mode_mutex.lock();
  dfdata.crz_spd_mode = val;
  crz_spd_mode_mutex.unlock();
}

float get_crz_pwr_setpt() {
  crz_pwr_setpt_mutex.lock();
  float val = dfdata.crz_pwr_setpt;
  crz_pwr_setpt_mutex.unlock();
  return val;
}
void set_crz_pwr_setpt(float val) {
  crz_pwr_setpt_mutex.lock();
  dfdata.crz_pwr_setpt = val;
  crz_pwr_setpt_mutex.unlock();
}

float get_crz_spd_setpt() {
  crz_spd_setpt_mutex.lock();
  float val = dfdata.crz_spd_setpt;
  crz_spd_setpt_mutex.unlock();
  return val;
}
void set_crz_spd_setpt(float val) {
  crz_spd_setpt_mutex.lock();
  dfdata.crz_spd_setpt = val;
  crz_spd_setpt_mutex.unlock();
}

uint8_t get_crz_state() {
  crz_state_mutex.lock();
  uint8_t val = dfdata.crz_state;
  crz_state_mutex.unlock();
  return val;
}
void set_crz_state(uint8_t val) {
  crz_state_mutex.lock();
  dfdata.crz_state = val;
  crz_state_mutex.unlock();
}

bool get_eco() {
  eco_mutex.lock();
  bool val = dfdata.eco;
  eco_mutex.unlock();
  return val;
}
void set_eco(bool val) {
  eco_mutex.lock();
  dfdata.eco = val;
  eco_mutex.unlock();
}

bool get_main_telem() {
  main_telem_mutex.lock();
  bool val = dfdata.main_telem;
  main_telem_mutex.unlock();
  return val;
}
void set_main_telem(bool val) {
  main_telem_mutex.lock();
  dfdata.main_telem = val;
  main_telem_mutex.unlock();
}

bool get_brake_status() {
  brake_status_mutex.lock();
  bool val = dfdata.brake_status;
  brake_status_mutex.unlock();
  return val;
}
void set_brake_status(bool val) {
  brake_status_mutex.lock();
  dfdata.brake_status = val;
  brake_status_mutex.unlock();
}

bool get_mech_brake_status() {
  mech_brake_status_mutex.lock();
  bool val = dfdata.mech_brake_status;
  mech_brake_status_mutex.unlock();
  return val;
}
void set_mech_brake_status(bool val) {
  mech_brake_status_mutex.lock();
  dfdata.mech_brake_status = val;
  mech_brake_status_mutex.unlock();
}

bool get_parking_brake() {
  parking_brake_mutex.lock();
  bool val = dfdata.parking_brake;
  parking_brake_mutex.unlock();
  return val;
}
void set_parking_brake(bool val) {
  parking_brake_mutex.lock();
  dfdata.parking_brake = val;
  parking_brake_mutex.unlock();
}

float get_accelerator() {
  accelerator_mutex.lock();
  float val = dfdata.accelerator;
  accelerator_mutex.unlock();
  return val;
}
void set_accelerator(float val) {
  accelerator_mutex.lock();
  dfdata.accelerator = val;
  accelerator_mutex.unlock();
}

float get_accelerator_out() {
  accelerator_out_mutex.lock();
  float val = dfdata.accelerator_out;
  accelerator_out_mutex.unlock();
  return val;
}
void set_accelerator_out(float val) {
  accelerator_out_mutex.lock();
  dfdata.accelerator_out = val;
  accelerator_out_mutex.unlock();
}

float get_motor_current() {
  motor_current_mutex.lock();
  float val = dfdata.motor_current;
  motor_current_mutex.unlock();
  return val;
}
void set_motor_current(float val) {
  motor_current_mutex.lock();
  dfdata.motor_current = val;
  motor_current_mutex.unlock();
}

float get_motor_power() {
  motor_power_mutex.lock();
  float val = dfdata.motor_power;
  motor_power_mutex.unlock();
  return val;
}
void set_motor_power(float val) {
  motor_power_mutex.lock();
  dfdata.motor_power = val;
  motor_power_mutex.unlock();
}

uint8_t get_mc_status() {
  mc_status_mutex.lock();
  uint8_t val = dfdata.mc_status;
  mc_status_mutex.unlock();
  return val;
}
void set_mc_status(uint8_t val) {
  mc_status_mutex.lock();
  dfdata.mc_status = val;
  mc_status_mutex.unlock();
}

bool get_mppt_can_heartbeat() {
  mppt_can_heartbeat_mutex.lock();
  bool val = dfdata.mppt_can_heartbeat;
  mppt_can_heartbeat_mutex.unlock();
  return val;
}
void set_mppt_can_heartbeat(bool val) {
  mppt_can_heartbeat_mutex.lock();
  dfdata.mppt_can_heartbeat = val;
  mppt_can_heartbeat_mutex.unlock();
}

bool get_mcc_can_heartbeat() {
  mcc_can_heartbeat_mutex.lock();
  bool val = dfdata.mcc_can_heartbeat;
  mcc_can_heartbeat_mutex.unlock();
  return val;
}
void set_mcc_can_heartbeat(bool val) {
  mcc_can_heartbeat_mutex.lock();
  dfdata.mcc_can_heartbeat = val;
  mcc_can_heartbeat_mutex.unlock();
}

bool get_bms_can_heartbeat() {
  bms_can_heartbeat_mutex.lock();
  bool val = dfdata.bms_can_heartbeat;
  bms_can_heartbeat_mutex.unlock();
  return val;
}
void set_bms_can_heartbeat(bool val) {
  bms_can_heartbeat_mutex.lock();
  dfdata.bms_can_heartbeat = val;
  bms_can_heartbeat_mutex.unlock();
}

bool get_mainIO_heartbeat() {
  mainIO_heartbeat_mutex.lock();
  bool val = dfdata.mainIO_heartbeat;
  mainIO_heartbeat_mutex.unlock();
  return val;
}
void set_mainIO_heartbeat(bool val) {
  mainIO_heartbeat_mutex.lock();
  dfdata.mainIO_heartbeat = val;
  mainIO_heartbeat_mutex.unlock();
}

float get_main_5V_bus() {
  main_5V_bus_mutex.lock();
  float val = dfdata.main_5V_bus;
  main_5V_bus_mutex.unlock();
  return val;
}
void set_main_5V_bus(float val) {
  main_5V_bus_mutex.lock();
  dfdata.main_5V_bus = val;
  main_5V_bus_mutex.unlock();
}

float get_main_12V_bus() {
  main_12V_bus_mutex.lock();
  float val = dfdata.main_12V_bus;
  main_12V_bus_mutex.unlock();
  return val;
}
void set_main_12V_bus(float val) {
  main_12V_bus_mutex.lock();
  dfdata.main_12V_bus = val;
  main_12V_bus_mutex.unlock();
}

float get_main_vbus() {
  main_vbus_mutex.lock();
  float val = dfdata.main_vbus;
  main_vbus_mutex.unlock();
  return val;
}
void set_main_vbus(float val) {
  main_vbus_mutex.lock();
  dfdata.main_vbus = val;
  main_vbus_mutex.unlock();
}

float get_main_vbus_current() {
  main_vbus_current_mutex.lock();
  float val = dfdata.main_vbus_current;
  main_vbus_current_mutex.unlock();
  return val;
}
void set_main_vbus_current(float val) {
  main_vbus_current_mutex.lock();
  dfdata.main_vbus_current = val;
  main_vbus_current_mutex.unlock();
}

float get_driver_5V_bus() {
  driver_5V_bus_mutex.lock();
  float val = dfdata.driver_5V_bus;
  driver_5V_bus_mutex.unlock();
  return val;
}
void set_driver_5V_bus(float val) {
  driver_5V_bus_mutex.lock();
  dfdata.driver_5V_bus = val;
  driver_5V_bus_mutex.unlock();
}

float get_driver_12V_bus() {
  driver_12V_bus_mutex.lock();
  float val = dfdata.driver_12V_bus;
  driver_12V_bus_mutex.unlock();
  return val;
}
void set_driver_12V_bus(float val) {
  driver_12V_bus_mutex.lock();
  dfdata.driver_12V_bus = val;
  driver_12V_bus_mutex.unlock();
}

float get_driver_vbus() {
  driver_vbus_mutex.lock();
  float val = dfdata.driver_vbus;
  driver_vbus_mutex.unlock();
  return val;
}
void set_driver_vbus(float val) {
  driver_vbus_mutex.lock();
  dfdata.driver_vbus = val;
  driver_vbus_mutex.unlock();
}

float get_driver_vbus_current() {
  driver_vbus_current_mutex.lock();
  float val = dfdata.driver_vbus_current;
  driver_vbus_current_mutex.unlock();
  return val;
}
void set_driver_vbus_current(float val) {
  driver_vbus_current_mutex.lock();
  dfdata.driver_vbus_current = val;
  driver_vbus_current_mutex.unlock();
}

bool get_main_power_critical() {
  main_power_critical_mutex.lock();
  bool val = dfdata.main_power_critical;
  main_power_critical_mutex.unlock();
  return val;
}
void set_main_power_critical(bool val) {
  main_power_critical_mutex.lock();
  dfdata.main_power_critical = val;
  main_power_critical_mutex.unlock();
}

bool get_main_power_warning() {
  main_power_warning_mutex.lock();
  bool val = dfdata.main_power_warning;
  main_power_warning_mutex.unlock();
  return val;
}
void set_main_power_warning(bool val) {
  main_power_warning_mutex.lock();
  dfdata.main_power_warning = val;
  main_power_warning_mutex.unlock();
}

bool get_main_power_tc() {
  main_power_tc_mutex.lock();
  bool val = dfdata.main_power_tc;
  main_power_tc_mutex.unlock();
  return val;
}
void set_main_power_tc(bool val) {
  main_power_tc_mutex.lock();
  dfdata.main_power_tc = val;
  main_power_tc_mutex.unlock();
}

bool get_main_power_valid() {
  main_power_valid_mutex.lock();
  bool val = dfdata.main_power_valid;
  main_power_valid_mutex.unlock();
  return val;
}
void set_main_power_valid(bool val) {
  main_power_valid_mutex.lock();
  dfdata.main_power_valid = val;
  main_power_valid_mutex.unlock();
}

bool get_driver_power_critical() {
  driver_power_critical_mutex.lock();
  bool val = dfdata.driver_power_critical;
  driver_power_critical_mutex.unlock();
  return val;
}
void set_driver_power_critical(bool val) {
  driver_power_critical_mutex.lock();
  dfdata.driver_power_critical = val;
  driver_power_critical_mutex.unlock();
}

bool get_driver_power_warning() {
  driver_power_warning_mutex.lock();
  bool val = dfdata.driver_power_warning;
  driver_power_warning_mutex.unlock();
  return val;
}
void set_driver_power_warning(bool val) {
  driver_power_warning_mutex.lock();
  dfdata.driver_power_warning = val;
  driver_power_warning_mutex.unlock();
}

bool get_driver_power_tc() {
  driver_power_tc_mutex.lock();
  bool val = dfdata.driver_power_tc;
  driver_power_tc_mutex.unlock();
  return val;
}
void set_driver_power_tc(bool val) {
  driver_power_tc_mutex.lock();
  dfdata.driver_power_tc = val;
  driver_power_tc_mutex.unlock();
}

bool get_driver_power_valid() {
  driver_power_valid_mutex.lock();
  bool val = dfdata.driver_power_valid;
  driver_power_valid_mutex.unlock();
  return val;
}
void set_driver_power_valid(bool val) {
  driver_power_valid_mutex.lock();
  dfdata.driver_power_valid = val;
  driver_power_valid_mutex.unlock();
}

uint16_t get_tstamp_ms() {
  tstamp_ms_mutex.lock();
  uint16_t val = dfdata.tstamp_ms;
  tstamp_ms_mutex.unlock();
  return val;
}
void set_tstamp_ms(uint16_t val) {
  tstamp_ms_mutex.lock();
  dfdata.tstamp_ms = val;
  tstamp_ms_mutex.unlock();
}

uint8_t get_tstamp_sc() {
  tstamp_sc_mutex.lock();
  uint8_t val = dfdata.tstamp_sc;
  tstamp_sc_mutex.unlock();
  return val;
}
void set_tstamp_sc(uint8_t val) {
  tstamp_sc_mutex.lock();
  dfdata.tstamp_sc = val;
  tstamp_sc_mutex.unlock();
}

uint8_t get_tstamp_mn() {
  tstamp_mn_mutex.lock();
  uint8_t val = dfdata.tstamp_mn;
  tstamp_mn_mutex.unlock();
  return val;
}
void set_tstamp_mn(uint8_t val) {
  tstamp_mn_mutex.lock();
  dfdata.tstamp_mn = val;
  tstamp_mn_mutex.unlock();
}

uint8_t get_tstamp_hr() {
  tstamp_hr_mutex.lock();
  uint8_t val = dfdata.tstamp_hr;
  tstamp_hr_mutex.unlock();
  return val;
}
void set_tstamp_hr(uint8_t val) {
  tstamp_hr_mutex.lock();
  dfdata.tstamp_hr = val;
  tstamp_hr_mutex.unlock();
}

bool get_mppt_contactor() {
  mppt_contactor_mutex.lock();
  bool val = dfdata.mppt_contactor;
  mppt_contactor_mutex.unlock();
  return val;
}
void set_mppt_contactor(bool val) {
  mppt_contactor_mutex.lock();
  dfdata.mppt_contactor = val;
  mppt_contactor_mutex.unlock();
}

bool get_motor_controller_contactor() {
  motor_controller_contactor_mutex.lock();
  bool val = dfdata.motor_controller_contactor;
  motor_controller_contactor_mutex.unlock();
  return val;
}
void set_motor_controller_contactor(bool val) {
  motor_controller_contactor_mutex.lock();
  dfdata.motor_controller_contactor = val;
  motor_controller_contactor_mutex.unlock();
}

bool get_low_contactor() {
  low_contactor_mutex.lock();
  bool val = dfdata.low_contactor;
  low_contactor_mutex.unlock();
  return val;
}
void set_low_contactor(bool val) {
  low_contactor_mutex.lock();
  dfdata.low_contactor = val;
  low_contactor_mutex.unlock();
}

bool get_dcdc_valid() {
  dcdc_valid_mutex.lock();
  bool val = dfdata.dcdc_valid;
  dcdc_valid_mutex.unlock();
  return val;
}
void set_dcdc_valid(bool val) {
  dcdc_valid_mutex.lock();
  dfdata.dcdc_valid = val;
  dcdc_valid_mutex.unlock();
}

bool get_supplemental_valid() {
  supplemental_valid_mutex.lock();
  bool val = dfdata.supplemental_valid;
  supplemental_valid_mutex.unlock();
  return val;
}
void set_supplemental_valid(bool val) {
  supplemental_valid_mutex.lock();
  dfdata.supplemental_valid = val;
  supplemental_valid_mutex.unlock();
}

bool get_mppt_mode() {
  mppt_mode_mutex.lock();
  bool val = dfdata.mppt_mode;
  mppt_mode_mutex.unlock();
  return val;
}
void set_mppt_mode(bool val) {
  mppt_mode_mutex.lock();
  dfdata.mppt_mode = val;
  mppt_mode_mutex.unlock();
}

float get_mppt_current_out() {
  mppt_current_out_mutex.lock();
  float val = dfdata.mppt_current_out;
  mppt_current_out_mutex.unlock();
  return val;
}
void set_mppt_current_out(float val) {
  mppt_current_out_mutex.lock();
  dfdata.mppt_current_out = val;
  mppt_current_out_mutex.unlock();
}

float get_string1_temp() {
  string1_temp_mutex.lock();
  float val = dfdata.string1_temp;
  string1_temp_mutex.unlock();
  return val;
}
void set_string1_temp(float val) {
  string1_temp_mutex.lock();
  dfdata.string1_temp = val;
  string1_temp_mutex.unlock();
}

float get_string2_temp() {
  string2_temp_mutex.lock();
  float val = dfdata.string2_temp;
  string2_temp_mutex.unlock();
  return val;
}
void set_string2_temp(float val) {
  string2_temp_mutex.lock();
  dfdata.string2_temp = val;
  string2_temp_mutex.unlock();
}

float get_string3_temp() {
  string3_temp_mutex.lock();
  float val = dfdata.string3_temp;
  string3_temp_mutex.unlock();
  return val;
}
void set_string3_temp(float val) {
  string3_temp_mutex.lock();
  dfdata.string3_temp = val;
  string3_temp_mutex.unlock();
}

float get_pack_temp() {
  pack_temp_mutex.lock();
  float val = dfdata.pack_temp;
  pack_temp_mutex.unlock();
  return val;
}
void set_pack_temp(float val) {
  pack_temp_mutex.lock();
  dfdata.pack_temp = val;
  pack_temp_mutex.unlock();
}

float get_pack_internal_temp() {
  pack_internal_temp_mutex.lock();
  float val = dfdata.pack_internal_temp;
  pack_internal_temp_mutex.unlock();
  return val;
}
void set_pack_internal_temp(float val) {
  pack_internal_temp_mutex.lock();
  dfdata.pack_internal_temp = val;
  pack_internal_temp_mutex.unlock();
}

float get_pack_current() {
  pack_current_mutex.lock();
  float val = dfdata.pack_current;
  pack_current_mutex.unlock();
  return val;
}
void set_pack_current(float val) {
  pack_current_mutex.lock();
  dfdata.pack_current = val;
  pack_current_mutex.unlock();
}

float get_pack_voltage() {
  pack_voltage_mutex.lock();
  float val = dfdata.pack_voltage;
  pack_voltage_mutex.unlock();
  return val;
}
void set_pack_voltage(float val) {
  pack_voltage_mutex.lock();
  dfdata.pack_voltage = val;
  pack_voltage_mutex.unlock();
}

float get_pack_power() {
  pack_power_mutex.lock();
  float val = dfdata.pack_power;
  pack_power_mutex.unlock();
  return val;
}
void set_pack_power(float val) {
  pack_power_mutex.lock();
  dfdata.pack_power = val;
  pack_power_mutex.unlock();
}

float get_supplemental_voltage() {
  supplemental_voltage_mutex.lock();
  float val = dfdata.supplemental_voltage;
  supplemental_voltage_mutex.unlock();
  return val;
}
void set_supplemental_voltage(float val) {
  supplemental_voltage_mutex.lock();
  dfdata.supplemental_voltage = val;
  supplemental_voltage_mutex.unlock();
}

float get_cell_group1_voltage() {
  cell_group1_voltage_mutex.lock();
  float val = dfdata.cell_group1_voltage;
  cell_group1_voltage_mutex.unlock();
  return val;
}
void set_cell_group1_voltage(float val) {
  cell_group1_voltage_mutex.lock();
  dfdata.cell_group1_voltage = val;
  cell_group1_voltage_mutex.unlock();
}

float get_cell_group2_voltage() {
  cell_group2_voltage_mutex.lock();
  float val = dfdata.cell_group2_voltage;
  cell_group2_voltage_mutex.unlock();
  return val;
}
void set_cell_group2_voltage(float val) {
  cell_group2_voltage_mutex.lock();
  dfdata.cell_group2_voltage = val;
  cell_group2_voltage_mutex.unlock();
}

float get_cell_group3_voltage() {
  cell_group3_voltage_mutex.lock();
  float val = dfdata.cell_group3_voltage;
  cell_group3_voltage_mutex.unlock();
  return val;
}
void set_cell_group3_voltage(float val) {
  cell_group3_voltage_mutex.lock();
  dfdata.cell_group3_voltage = val;
  cell_group3_voltage_mutex.unlock();
}

float get_cell_group4_voltage() {
  cell_group4_voltage_mutex.lock();
  float val = dfdata.cell_group4_voltage;
  cell_group4_voltage_mutex.unlock();
  return val;
}
void set_cell_group4_voltage(float val) {
  cell_group4_voltage_mutex.lock();
  dfdata.cell_group4_voltage = val;
  cell_group4_voltage_mutex.unlock();
}

float get_cell_group5_voltage() {
  cell_group5_voltage_mutex.lock();
  float val = dfdata.cell_group5_voltage;
  cell_group5_voltage_mutex.unlock();
  return val;
}
void set_cell_group5_voltage(float val) {
  cell_group5_voltage_mutex.lock();
  dfdata.cell_group5_voltage = val;
  cell_group5_voltage_mutex.unlock();
}

float get_cell_group6_voltage() {
  cell_group6_voltage_mutex.lock();
  float val = dfdata.cell_group6_voltage;
  cell_group6_voltage_mutex.unlock();
  return val;
}
void set_cell_group6_voltage(float val) {
  cell_group6_voltage_mutex.lock();
  dfdata.cell_group6_voltage = val;
  cell_group6_voltage_mutex.unlock();
}

float get_cell_group7_voltage() {
  cell_group7_voltage_mutex.lock();
  float val = dfdata.cell_group7_voltage;
  cell_group7_voltage_mutex.unlock();
  return val;
}
void set_cell_group7_voltage(float val) {
  cell_group7_voltage_mutex.lock();
  dfdata.cell_group7_voltage = val;
  cell_group7_voltage_mutex.unlock();
}

float get_cell_group8_voltage() {
  cell_group8_voltage_mutex.lock();
  float val = dfdata.cell_group8_voltage;
  cell_group8_voltage_mutex.unlock();
  return val;
}
void set_cell_group8_voltage(float val) {
  cell_group8_voltage_mutex.lock();
  dfdata.cell_group8_voltage = val;
  cell_group8_voltage_mutex.unlock();
}

float get_cell_group9_voltage() {
  cell_group9_voltage_mutex.lock();
  float val = dfdata.cell_group9_voltage;
  cell_group9_voltage_mutex.unlock();
  return val;
}
void set_cell_group9_voltage(float val) {
  cell_group9_voltage_mutex.lock();
  dfdata.cell_group9_voltage = val;
  cell_group9_voltage_mutex.unlock();
}

float get_cell_group10_voltage() {
  cell_group10_voltage_mutex.lock();
  float val = dfdata.cell_group10_voltage;
  cell_group10_voltage_mutex.unlock();
  return val;
}
void set_cell_group10_voltage(float val) {
  cell_group10_voltage_mutex.lock();
  dfdata.cell_group10_voltage = val;
  cell_group10_voltage_mutex.unlock();
}

float get_cell_group11_voltage() {
  cell_group11_voltage_mutex.lock();
  float val = dfdata.cell_group11_voltage;
  cell_group11_voltage_mutex.unlock();
  return val;
}
void set_cell_group11_voltage(float val) {
  cell_group11_voltage_mutex.lock();
  dfdata.cell_group11_voltage = val;
  cell_group11_voltage_mutex.unlock();
}

float get_cell_group12_voltage() {
  cell_group12_voltage_mutex.lock();
  float val = dfdata.cell_group12_voltage;
  cell_group12_voltage_mutex.unlock();
  return val;
}
void set_cell_group12_voltage(float val) {
  cell_group12_voltage_mutex.lock();
  dfdata.cell_group12_voltage = val;
  cell_group12_voltage_mutex.unlock();
}

float get_cell_group13_voltage() {
  cell_group13_voltage_mutex.lock();
  float val = dfdata.cell_group13_voltage;
  cell_group13_voltage_mutex.unlock();
  return val;
}
void set_cell_group13_voltage(float val) {
  cell_group13_voltage_mutex.lock();
  dfdata.cell_group13_voltage = val;
  cell_group13_voltage_mutex.unlock();
}

float get_cell_group14_voltage() {
  cell_group14_voltage_mutex.lock();
  float val = dfdata.cell_group14_voltage;
  cell_group14_voltage_mutex.unlock();
  return val;
}
void set_cell_group14_voltage(float val) {
  cell_group14_voltage_mutex.lock();
  dfdata.cell_group14_voltage = val;
  cell_group14_voltage_mutex.unlock();
}

float get_cell_group15_voltage() {
  cell_group15_voltage_mutex.lock();
  float val = dfdata.cell_group15_voltage;
  cell_group15_voltage_mutex.unlock();
  return val;
}
void set_cell_group15_voltage(float val) {
  cell_group15_voltage_mutex.lock();
  dfdata.cell_group15_voltage = val;
  cell_group15_voltage_mutex.unlock();
}

float get_cell_group16_voltage() {
  cell_group16_voltage_mutex.lock();
  float val = dfdata.cell_group16_voltage;
  cell_group16_voltage_mutex.unlock();
  return val;
}
void set_cell_group16_voltage(float val) {
  cell_group16_voltage_mutex.lock();
  dfdata.cell_group16_voltage = val;
  cell_group16_voltage_mutex.unlock();
}

float get_cell_group17_voltage() {
  cell_group17_voltage_mutex.lock();
  float val = dfdata.cell_group17_voltage;
  cell_group17_voltage_mutex.unlock();
  return val;
}
void set_cell_group17_voltage(float val) {
  cell_group17_voltage_mutex.lock();
  dfdata.cell_group17_voltage = val;
  cell_group17_voltage_mutex.unlock();
}

float get_cell_group18_voltage() {
  cell_group18_voltage_mutex.lock();
  float val = dfdata.cell_group18_voltage;
  cell_group18_voltage_mutex.unlock();
  return val;
}
void set_cell_group18_voltage(float val) {
  cell_group18_voltage_mutex.lock();
  dfdata.cell_group18_voltage = val;
  cell_group18_voltage_mutex.unlock();
}

float get_cell_group19_voltage() {
  cell_group19_voltage_mutex.lock();
  float val = dfdata.cell_group19_voltage;
  cell_group19_voltage_mutex.unlock();
  return val;
}
void set_cell_group19_voltage(float val) {
  cell_group19_voltage_mutex.lock();
  dfdata.cell_group19_voltage = val;
  cell_group19_voltage_mutex.unlock();
}

float get_cell_group20_voltage() {
  cell_group20_voltage_mutex.lock();
  float val = dfdata.cell_group20_voltage;
  cell_group20_voltage_mutex.unlock();
  return val;
}
void set_cell_group20_voltage(float val) {
  cell_group20_voltage_mutex.lock();
  dfdata.cell_group20_voltage = val;
  cell_group20_voltage_mutex.unlock();
}

float get_cell_group21_voltage() {
  cell_group21_voltage_mutex.lock();
  float val = dfdata.cell_group21_voltage;
  cell_group21_voltage_mutex.unlock();
  return val;
}
void set_cell_group21_voltage(float val) {
  cell_group21_voltage_mutex.lock();
  dfdata.cell_group21_voltage = val;
  cell_group21_voltage_mutex.unlock();
}

float get_cell_group22_voltage() {
  cell_group22_voltage_mutex.lock();
  float val = dfdata.cell_group22_voltage;
  cell_group22_voltage_mutex.unlock();
  return val;
}
void set_cell_group22_voltage(float val) {
  cell_group22_voltage_mutex.lock();
  dfdata.cell_group22_voltage = val;
  cell_group22_voltage_mutex.unlock();
}

float get_cell_group23_voltage() {
  cell_group23_voltage_mutex.lock();
  float val = dfdata.cell_group23_voltage;
  cell_group23_voltage_mutex.unlock();
  return val;
}
void set_cell_group23_voltage(float val) {
  cell_group23_voltage_mutex.lock();
  dfdata.cell_group23_voltage = val;
  cell_group23_voltage_mutex.unlock();
}

float get_cell_group24_voltage() {
  cell_group24_voltage_mutex.lock();
  float val = dfdata.cell_group24_voltage;
  cell_group24_voltage_mutex.unlock();
  return val;
}
void set_cell_group24_voltage(float val) {
  cell_group24_voltage_mutex.lock();
  dfdata.cell_group24_voltage = val;
  cell_group24_voltage_mutex.unlock();
}

float get_cell_group25_voltage() {
  cell_group25_voltage_mutex.lock();
  float val = dfdata.cell_group25_voltage;
  cell_group25_voltage_mutex.unlock();
  return val;
}
void set_cell_group25_voltage(float val) {
  cell_group25_voltage_mutex.lock();
  dfdata.cell_group25_voltage = val;
  cell_group25_voltage_mutex.unlock();
}

float get_cell_group26_voltage() {
  cell_group26_voltage_mutex.lock();
  float val = dfdata.cell_group26_voltage;
  cell_group26_voltage_mutex.unlock();
  return val;
}
void set_cell_group26_voltage(float val) {
  cell_group26_voltage_mutex.lock();
  dfdata.cell_group26_voltage = val;
  cell_group26_voltage_mutex.unlock();
}

float get_cell_group27_voltage() {
  cell_group27_voltage_mutex.lock();
  float val = dfdata.cell_group27_voltage;
  cell_group27_voltage_mutex.unlock();
  return val;
}
void set_cell_group27_voltage(float val) {
  cell_group27_voltage_mutex.lock();
  dfdata.cell_group27_voltage = val;
  cell_group27_voltage_mutex.unlock();
}

float get_cell_group28_voltage() {
  cell_group28_voltage_mutex.lock();
  float val = dfdata.cell_group28_voltage;
  cell_group28_voltage_mutex.unlock();
  return val;
}
void set_cell_group28_voltage(float val) {
  cell_group28_voltage_mutex.lock();
  dfdata.cell_group28_voltage = val;
  cell_group28_voltage_mutex.unlock();
}

float get_cell_group29_voltage() {
  cell_group29_voltage_mutex.lock();
  float val = dfdata.cell_group29_voltage;
  cell_group29_voltage_mutex.unlock();
  return val;
}
void set_cell_group29_voltage(float val) {
  cell_group29_voltage_mutex.lock();
  dfdata.cell_group29_voltage = val;
  cell_group29_voltage_mutex.unlock();
}

float get_cell_group30_voltage() {
  cell_group30_voltage_mutex.lock();
  float val = dfdata.cell_group30_voltage;
  cell_group30_voltage_mutex.unlock();
  return val;
}
void set_cell_group30_voltage(float val) {
  cell_group30_voltage_mutex.lock();
  dfdata.cell_group30_voltage = val;
  cell_group30_voltage_mutex.unlock();
}

float get_cell_group31_voltage() {
  cell_group31_voltage_mutex.lock();
  float val = dfdata.cell_group31_voltage;
  cell_group31_voltage_mutex.unlock();
  return val;
}
void set_cell_group31_voltage(float val) {
  cell_group31_voltage_mutex.lock();
  dfdata.cell_group31_voltage = val;
  cell_group31_voltage_mutex.unlock();
}

uint16_t get_populated_cells() {
  populated_cells_mutex.lock();
  uint16_t val = dfdata.populated_cells;
  populated_cells_mutex.unlock();
  return val;
}
void set_populated_cells(uint16_t val) {
  populated_cells_mutex.lock();
  dfdata.populated_cells = val;
  populated_cells_mutex.unlock();
}

float get_soc() {
  soc_mutex.lock();
  float val = dfdata.soc;
  soc_mutex.unlock();
  return val;
}
void set_soc(float val) {
  soc_mutex.lock();
  dfdata.soc = val;
  soc_mutex.unlock();
}

float get_est_supplemental_soc() {
  est_supplemental_soc_mutex.lock();
  float val = dfdata.est_supplemental_soc;
  est_supplemental_soc_mutex.unlock();
  return val;
}
void set_est_supplemental_soc(float val) {
  est_supplemental_soc_mutex.lock();
  dfdata.est_supplemental_soc = val;
  est_supplemental_soc_mutex.unlock();
}

float get_soh() {
  soh_mutex.lock();
  float val = dfdata.soh;
  soh_mutex.unlock();
  return val;
}
void set_soh(float val) {
  soh_mutex.lock();
  dfdata.soh = val;
  soh_mutex.unlock();
}

float get_pack_capacity() {
  pack_capacity_mutex.lock();
  float val = dfdata.pack_capacity;
  pack_capacity_mutex.unlock();
  return val;
}
void set_pack_capacity(float val) {
  pack_capacity_mutex.lock();
  dfdata.pack_capacity = val;
  pack_capacity_mutex.unlock();
}

float get_adaptive_total_capacity() {
  adaptive_total_capacity_mutex.lock();
  float val = dfdata.adaptive_total_capacity;
  adaptive_total_capacity_mutex.unlock();
  return val;
}
void set_adaptive_total_capacity(float val) {
  adaptive_total_capacity_mutex.lock();
  dfdata.adaptive_total_capacity = val;
  adaptive_total_capacity_mutex.unlock();
}

bool get_bps_fault() {
  bps_fault_mutex.lock();
  bool val = dfdata.bps_fault;
  bps_fault_mutex.unlock();
  return val;
}
void set_bps_fault(bool val) {
  bps_fault_mutex.lock();
  dfdata.bps_fault = val;
  bps_fault_mutex.unlock();
}

bool get_fan_enable() {
  fan_enable_mutex.lock();
  bool val = dfdata.fan_enable;
  fan_enable_mutex.unlock();
  return val;
}
void set_fan_enable(bool val) {
  fan_enable_mutex.lock();
  dfdata.fan_enable = val;
  fan_enable_mutex.unlock();
}

uint8_t get_fan_speed() {
  fan_speed_mutex.lock();
  uint8_t val = dfdata.fan_speed;
  fan_speed_mutex.unlock();
  return val;
}
void set_fan_speed(uint8_t val) {
  fan_speed_mutex.lock();
  dfdata.fan_speed = val;
  fan_speed_mutex.unlock();
}

bool get_voltage_failsafe() {
  voltage_failsafe_mutex.lock();
  bool val = dfdata.voltage_failsafe;
  voltage_failsafe_mutex.unlock();
  return val;
}
void set_voltage_failsafe(bool val) {
  voltage_failsafe_mutex.lock();
  dfdata.voltage_failsafe = val;
  voltage_failsafe_mutex.unlock();
}

bool get_current_failsafe() {
  current_failsafe_mutex.lock();
  bool val = dfdata.current_failsafe;
  current_failsafe_mutex.unlock();
  return val;
}
void set_current_failsafe(bool val) {
  current_failsafe_mutex.lock();
  dfdata.current_failsafe = val;
  current_failsafe_mutex.unlock();
}

bool get_relay_failsafe() {
  relay_failsafe_mutex.lock();
  bool val = dfdata.relay_failsafe;
  relay_failsafe_mutex.unlock();
  return val;
}
void set_relay_failsafe(bool val) {
  relay_failsafe_mutex.lock();
  dfdata.relay_failsafe = val;
  relay_failsafe_mutex.unlock();
}

bool get_cell_balancing_active() {
  cell_balancing_active_mutex.lock();
  bool val = dfdata.cell_balancing_active;
  cell_balancing_active_mutex.unlock();
  return val;
}
void set_cell_balancing_active(bool val) {
  cell_balancing_active_mutex.lock();
  dfdata.cell_balancing_active = val;
  cell_balancing_active_mutex.unlock();
}

bool get_charge_interlock_failsafe() {
  charge_interlock_failsafe_mutex.lock();
  bool val = dfdata.charge_interlock_failsafe;
  charge_interlock_failsafe_mutex.unlock();
  return val;
}
void set_charge_interlock_failsafe(bool val) {
  charge_interlock_failsafe_mutex.lock();
  dfdata.charge_interlock_failsafe = val;
  charge_interlock_failsafe_mutex.unlock();
}

bool get_thermistor_b_value_table_invalid() {
  thermistor_b_value_table_invalid_mutex.lock();
  bool val = dfdata.thermistor_b_value_table_invalid;
  thermistor_b_value_table_invalid_mutex.unlock();
  return val;
}
void set_thermistor_b_value_table_invalid(bool val) {
  thermistor_b_value_table_invalid_mutex.lock();
  dfdata.thermistor_b_value_table_invalid = val;
  thermistor_b_value_table_invalid_mutex.unlock();
}

bool get_input_power_supply_failsafe() {
  input_power_supply_failsafe_mutex.lock();
  bool val = dfdata.input_power_supply_failsafe;
  input_power_supply_failsafe_mutex.unlock();
  return val;
}
void set_input_power_supply_failsafe(bool val) {
  input_power_supply_failsafe_mutex.lock();
  dfdata.input_power_supply_failsafe = val;
  input_power_supply_failsafe_mutex.unlock();
}

bool get_discharge_limit_enforcement_fault() {
  discharge_limit_enforcement_fault_mutex.lock();
  bool val = dfdata.discharge_limit_enforcement_fault;
  discharge_limit_enforcement_fault_mutex.unlock();
  return val;
}
void set_discharge_limit_enforcement_fault(bool val) {
  discharge_limit_enforcement_fault_mutex.lock();
  dfdata.discharge_limit_enforcement_fault = val;
  discharge_limit_enforcement_fault_mutex.unlock();
}

bool get_charger_safety_relay_fault() {
  charger_safety_relay_fault_mutex.lock();
  bool val = dfdata.charger_safety_relay_fault;
  charger_safety_relay_fault_mutex.unlock();
  return val;
}
void set_charger_safety_relay_fault(bool val) {
  charger_safety_relay_fault_mutex.lock();
  dfdata.charger_safety_relay_fault = val;
  charger_safety_relay_fault_mutex.unlock();
}

bool get_internal_hardware_fault() {
  internal_hardware_fault_mutex.lock();
  bool val = dfdata.internal_hardware_fault;
  internal_hardware_fault_mutex.unlock();
  return val;
}
void set_internal_hardware_fault(bool val) {
  internal_hardware_fault_mutex.lock();
  dfdata.internal_hardware_fault = val;
  internal_hardware_fault_mutex.unlock();
}

bool get_internal_heatsink_fault() {
  internal_heatsink_fault_mutex.lock();
  bool val = dfdata.internal_heatsink_fault;
  internal_heatsink_fault_mutex.unlock();
  return val;
}
void set_internal_heatsink_fault(bool val) {
  internal_heatsink_fault_mutex.lock();
  dfdata.internal_heatsink_fault = val;
  internal_heatsink_fault_mutex.unlock();
}

bool get_internal_software_fault() {
  internal_software_fault_mutex.lock();
  bool val = dfdata.internal_software_fault;
  internal_software_fault_mutex.unlock();
  return val;
}
void set_internal_software_fault(bool val) {
  internal_software_fault_mutex.lock();
  dfdata.internal_software_fault = val;
  internal_software_fault_mutex.unlock();
}

bool get_highest_cell_voltage_too_high_fault() {
  highest_cell_voltage_too_high_fault_mutex.lock();
  bool val = dfdata.highest_cell_voltage_too_high_fault;
  highest_cell_voltage_too_high_fault_mutex.unlock();
  return val;
}
void set_highest_cell_voltage_too_high_fault(bool val) {
  highest_cell_voltage_too_high_fault_mutex.lock();
  dfdata.highest_cell_voltage_too_high_fault = val;
  highest_cell_voltage_too_high_fault_mutex.unlock();
}

bool get_lowest_cell_voltage_too_low_fault() {
  lowest_cell_voltage_too_low_fault_mutex.lock();
  bool val = dfdata.lowest_cell_voltage_too_low_fault;
  lowest_cell_voltage_too_low_fault_mutex.unlock();
  return val;
}
void set_lowest_cell_voltage_too_low_fault(bool val) {
  lowest_cell_voltage_too_low_fault_mutex.lock();
  dfdata.lowest_cell_voltage_too_low_fault = val;
  lowest_cell_voltage_too_low_fault_mutex.unlock();
}

bool get_pack_too_hot_fault() {
  pack_too_hot_fault_mutex.lock();
  bool val = dfdata.pack_too_hot_fault;
  pack_too_hot_fault_mutex.unlock();
  return val;
}
void set_pack_too_hot_fault(bool val) {
  pack_too_hot_fault_mutex.lock();
  dfdata.pack_too_hot_fault = val;
  pack_too_hot_fault_mutex.unlock();
}

bool get_internal_communication_fault() {
  internal_communication_fault_mutex.lock();
  bool val = dfdata.internal_communication_fault;
  internal_communication_fault_mutex.unlock();
  return val;
}
void set_internal_communication_fault(bool val) {
  internal_communication_fault_mutex.lock();
  dfdata.internal_communication_fault = val;
  internal_communication_fault_mutex.unlock();
}

bool get_cell_balancing_stuck_off_fault() {
  cell_balancing_stuck_off_fault_mutex.lock();
  bool val = dfdata.cell_balancing_stuck_off_fault;
  cell_balancing_stuck_off_fault_mutex.unlock();
  return val;
}
void set_cell_balancing_stuck_off_fault(bool val) {
  cell_balancing_stuck_off_fault_mutex.lock();
  dfdata.cell_balancing_stuck_off_fault = val;
  cell_balancing_stuck_off_fault_mutex.unlock();
}

bool get_weak_cell_fault() {
  weak_cell_fault_mutex.lock();
  bool val = dfdata.weak_cell_fault;
  weak_cell_fault_mutex.unlock();
  return val;
}
void set_weak_cell_fault(bool val) {
  weak_cell_fault_mutex.lock();
  dfdata.weak_cell_fault = val;
  weak_cell_fault_mutex.unlock();
}

bool get_low_cell_voltage_fault() {
  low_cell_voltage_fault_mutex.lock();
  bool val = dfdata.low_cell_voltage_fault;
  low_cell_voltage_fault_mutex.unlock();
  return val;
}
void set_low_cell_voltage_fault(bool val) {
  low_cell_voltage_fault_mutex.lock();
  dfdata.low_cell_voltage_fault = val;
  low_cell_voltage_fault_mutex.unlock();
}

bool get_open_wiring_fault() {
  open_wiring_fault_mutex.lock();
  bool val = dfdata.open_wiring_fault;
  open_wiring_fault_mutex.unlock();
  return val;
}
void set_open_wiring_fault(bool val) {
  open_wiring_fault_mutex.lock();
  dfdata.open_wiring_fault = val;
  open_wiring_fault_mutex.unlock();
}

bool get_current_sensor_fault() {
  current_sensor_fault_mutex.lock();
  bool val = dfdata.current_sensor_fault;
  current_sensor_fault_mutex.unlock();
  return val;
}
void set_current_sensor_fault(bool val) {
  current_sensor_fault_mutex.lock();
  dfdata.current_sensor_fault = val;
  current_sensor_fault_mutex.unlock();
}

bool get_highest_cell_voltage_over_5V_fault() {
  highest_cell_voltage_over_5V_fault_mutex.lock();
  bool val = dfdata.highest_cell_voltage_over_5V_fault;
  highest_cell_voltage_over_5V_fault_mutex.unlock();
  return val;
}
void set_highest_cell_voltage_over_5V_fault(bool val) {
  highest_cell_voltage_over_5V_fault_mutex.lock();
  dfdata.highest_cell_voltage_over_5V_fault = val;
  highest_cell_voltage_over_5V_fault_mutex.unlock();
}

bool get_cell_asic_fault() {
  cell_asic_fault_mutex.lock();
  bool val = dfdata.cell_asic_fault;
  cell_asic_fault_mutex.unlock();
  return val;
}
void set_cell_asic_fault(bool val) {
  cell_asic_fault_mutex.lock();
  dfdata.cell_asic_fault = val;
  cell_asic_fault_mutex.unlock();
}

bool get_weak_pack_fault() {
  weak_pack_fault_mutex.lock();
  bool val = dfdata.weak_pack_fault;
  weak_pack_fault_mutex.unlock();
  return val;
}
void set_weak_pack_fault(bool val) {
  weak_pack_fault_mutex.lock();
  dfdata.weak_pack_fault = val;
  weak_pack_fault_mutex.unlock();
}

bool get_fan_monitor_fault() {
  fan_monitor_fault_mutex.lock();
  bool val = dfdata.fan_monitor_fault;
  fan_monitor_fault_mutex.unlock();
  return val;
}
void set_fan_monitor_fault(bool val) {
  fan_monitor_fault_mutex.lock();
  dfdata.fan_monitor_fault = val;
  fan_monitor_fault_mutex.unlock();
}

bool get_thermistor_fault() {
  thermistor_fault_mutex.lock();
  bool val = dfdata.thermistor_fault;
  thermistor_fault_mutex.unlock();
  return val;
}
void set_thermistor_fault(bool val) {
  thermistor_fault_mutex.lock();
  dfdata.thermistor_fault = val;
  thermistor_fault_mutex.unlock();
}

bool get_external_communication_fault() {
  external_communication_fault_mutex.lock();
  bool val = dfdata.external_communication_fault;
  external_communication_fault_mutex.unlock();
  return val;
}
void set_external_communication_fault(bool val) {
  external_communication_fault_mutex.lock();
  dfdata.external_communication_fault = val;
  external_communication_fault_mutex.unlock();
}

bool get_redundant_power_supply_fault() {
  redundant_power_supply_fault_mutex.lock();
  bool val = dfdata.redundant_power_supply_fault;
  redundant_power_supply_fault_mutex.unlock();
  return val;
}
void set_redundant_power_supply_fault(bool val) {
  redundant_power_supply_fault_mutex.lock();
  dfdata.redundant_power_supply_fault = val;
  redundant_power_supply_fault_mutex.unlock();
}

bool get_high_voltage_isolation_fault() {
  high_voltage_isolation_fault_mutex.lock();
  bool val = dfdata.high_voltage_isolation_fault;
  high_voltage_isolation_fault_mutex.unlock();
  return val;
}
void set_high_voltage_isolation_fault(bool val) {
  high_voltage_isolation_fault_mutex.lock();
  dfdata.high_voltage_isolation_fault = val;
  high_voltage_isolation_fault_mutex.unlock();
}

bool get_input_power_supply_fault() {
  input_power_supply_fault_mutex.lock();
  bool val = dfdata.input_power_supply_fault;
  input_power_supply_fault_mutex.unlock();
  return val;
}
void set_input_power_supply_fault(bool val) {
  input_power_supply_fault_mutex.lock();
  dfdata.input_power_supply_fault = val;
  input_power_supply_fault_mutex.unlock();
}

bool get_charge_limit_enforcement_fault() {
  charge_limit_enforcement_fault_mutex.lock();
  bool val = dfdata.charge_limit_enforcement_fault;
  charge_limit_enforcement_fault_mutex.unlock();
  return val;
}
void set_charge_limit_enforcement_fault(bool val) {
  charge_limit_enforcement_fault_mutex.lock();
  dfdata.charge_limit_enforcement_fault = val;
  charge_limit_enforcement_fault_mutex.unlock();
}

float get_pack_resistance() {
  pack_resistance_mutex.lock();
  float val = dfdata.pack_resistance;
  pack_resistance_mutex.unlock();
  return val;
}
void set_pack_resistance(float val) {
  pack_resistance_mutex.lock();
  dfdata.pack_resistance = val;
  pack_resistance_mutex.unlock();
}

float get_bms_input_voltage() {
  bms_input_voltage_mutex.lock();
  float val = dfdata.bms_input_voltage;
  bms_input_voltage_mutex.unlock();
  return val;
}
void set_bms_input_voltage(float val) {
  bms_input_voltage_mutex.lock();
  dfdata.bms_input_voltage = val;
  bms_input_voltage_mutex.unlock();
}

bool get_charge_enable() {
  charge_enable_mutex.lock();
  bool val = dfdata.charge_enable;
  charge_enable_mutex.unlock();
  return val;
}
void set_charge_enable(bool val) {
  charge_enable_mutex.lock();
  dfdata.charge_enable = val;
  charge_enable_mutex.unlock();
}

bool get_discharge_enable() {
  discharge_enable_mutex.lock();
  bool val = dfdata.discharge_enable;
  discharge_enable_mutex.unlock();
  return val;
}
void set_discharge_enable(bool val) {
  discharge_enable_mutex.lock();
  dfdata.discharge_enable = val;
  discharge_enable_mutex.unlock();
}

void check_shutdown_errors() {
  if (get_driver_eStop() || get_external_eStop() || get_crash() || get_door() ||
      get_imd_status() || get_mcu_stat_fdbk() || get_door_lim_out() ||
      get_mcu_latch()) {
    set_mcu_hv_en(0);
  }
}
/* Autogenerated Code Ends */
