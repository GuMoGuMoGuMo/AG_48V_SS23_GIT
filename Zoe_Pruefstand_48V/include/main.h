// include standard libraries

#include <Arduino.h>
#include <math.h>
#include <SPI.h>
#include <stdint.h>

//#include measuring cycles
#include "measuring_cycle.h"

// define bench limits
#define TORQUE_MAX 40
#define SPEED_MAX 5000 // 8000 rpm @48V PMAC
#define EXCITATION_CURRENT_MAX 5

 // define constants
#define R_EXCITATION_COIL 8.5
#define L_EXCITATION_COIL 1
#define U_REF 5
#define R1_VOLTAGE_DIVIDER_U_BATT 100000
#define R2_VOLTAGE_DIVIDER_U_BATT 5600

// define measuring shaft constants
#define SPEED_MODE_MEASURING_SHAFT 400 // rpm/V
#define R1_VOLTAGE_DIVIDER_MEASURING_SHAFT 21.56e03
#define R2_VOLTAGE_DIVIDER_MEASURING_SHAFT 21.37e03

#define R1_LM358_OP_AMP 11.9e03
#define R2_LM358_OP_AMP 11.75e03
#define R3_LM358_OP_AMP 3.24e03
#define R4_LM358_OP_AMP 3.29e03

double torque_offset;
double speed_offset;

#define U_SUPPLY_MEASURING_CIRCUIT 9.9
#define deltaM 10 //delta M in Nm/V



// define Analog/Digital Pins
#define EXCITATION_CURRENT_POTI_ZOE_PIN A0
#define POTI_THROTTLE_DMC_PIN A1
#define POTI_BRAKE_DMC_PIN A2

#define POTI_EGAS_DMC_PIN A5
#define SWITCH_EGAS_DMC_PIN 28

#define FOOT_SWITCH_DMC_PIN 26
#define BRAKE_SWITCH_DMC_PIN 40

#define PWM_EXCITATION_CURRENT_ZOE_PIN A13

#define FOOT_SWITCH_KELLY_PIN 22
#define BRAKE_SWITCH_KELLY_PIN 24

#define POTI_THROTTLE_KELLY_PIN A3
#define POTI_BRAKE_KELLY_PIN A4

#define SWITCH_D_N_DMC_PIN 36
#define SWITCH_D_N_KELLY_PIN 38


// define ILI9341+Touchscreen
#include <SPI.h>
#include <stdint.h>
#include <TouchScreen.h>
#include <Adafruit_ILI9341.h>
#include "hs_esslingen_logo_bitmap.h"


#define WIDTH  ILI9341_TFTWIDTH
#define HEIGHT ILI9341_TFTHEIGHT

#define TFT_DC 32
#define TFT_CS 30
#define YP A6  // must be an analog pin, use "An" notation!
#define XM A7  // must be an analog pin, use "An" notation!
#define YM 34   // can be a digital pin
#define XP 32   // can be a digital pin

#define X_MAX 885
#define X_MIN 132
#define Y_MAX 921
#define Y_MIN 99

#define BUTTON1_TOP_LEFT_X 5
#define BUTTON1_TOP_LEFT_Y 190
#define BUTTON1_WIDTH 100
#define BUTTON1_HEIGHT 40

#define BUTTON2_TOP_LEFT_X 110
#define BUTTON2_TOP_LEFT_Y 190
#define BUTTON2_WIDTH 100
#define BUTTON2_HEIGHT 40

#define BUTTON3_TOP_LEFT_X 215
#define BUTTON3_TOP_LEFT_Y 190
#define BUTTON3_WIDTH 100
#define BUTTON3_HEIGHT 40

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint touchPoint;

// define Analog-Digital Converter ADS1115
#include "ADS1X15.h"
#define ADRESS_ADC_VEHICLE_DMZ_ZOE 0x48
#define ADRESS_ADC_MEASURING_SHAFT_ZOE 0x49
#define ADRESS_ADC_DMC_CURRENT 0x4A

ADS1115 adc_vehicle_dmc_zoe(ADRESS_ADC_VEHICLE_DMZ_ZOE);
ADS1115 adc_measuring_shaft(ADRESS_ADC_MEASURING_SHAFT_ZOE);
ADS1115 adc_measuring_dmc_current(ADRESS_ADC_DMC_CURRENT);

// define analog-digital converter DMC PINS 
#define BATTERY_VOLTAGE_SENSOR_PIN 1 

// define analog-digital converter DMC measuring shaft PINS
#define TORQUE_MEASURING_SHAFT_PIN 1
#define SPEED_MEASURING_SHAFT_PIN 0

// define analog-digital converter adc_measuring_dmc_current
#define EXCITATION_CURRENT_SENSOR_ZOE_PIN 0
#define BATTERY_CURRENT_SENSOR_1_PIN 1
#define BATTERY_CURRENT_SENSOR_2_PIN 2
#define BATTERY_CURRENT_SENSOR_3_PIN 3

// define digital-analog converters
#include <Adafruit_MCP4725.h>

#define ADRESS_DAC_gas_dmc 0x62
#define ADRESS_DAC_bremse_dmc 0x63
#define ADRESS_DAC_gas_kelly 0x60
#define ADRESS_DAC_bremse_kelly 0x61
Adafruit_MCP4725 dac_gas_dmc;
Adafruit_MCP4725 dac_bremse_dmc;
Adafruit_MCP4725 dac_gas_kelly;
Adafruit_MCP4725 dac_bremse_kelly;


// current sensors
#include <ACS712.h> // Stromsensor lib
ACS712 battery_current_sensor_1(BATTERY_CURRENT_SENSOR_1_PIN, U_REF, 1023,40); // init Stomsensor Objekt: PIN, VCC, ADC Auflösung, 40mV/A
ACS712 battery_current_sensor_2(BATTERY_CURRENT_SENSOR_2_PIN, U_REF, 1023,40); // init Stomsensor Objekt: PIN, VCC, ADC Auflösung, 40mV/A
ACS712 battery_current_sensor_3(BATTERY_CURRENT_SENSOR_3_PIN, U_REF, 1023,40); // init Stomsensor Objekt: PIN, VCC, ADC Auflösung, 40mV/A
ACS712 excitation_current_sensor(EXCITATION_CURRENT_SENSOR_ZOE_PIN, U_REF, 1023,66); // init Stomsensor Objekt: PIN, VCC, ADC Auflösung, 66mV/A

//  wrapper needed for external analogRead()
//  as casting behavior is undefined between different function signatures.
uint16_t read_adc_battery_current_sensor_1(uint8_t p) {
  return adc_measuring_dmc_current.readADC(BATTERY_CURRENT_SENSOR_1_PIN);
};

//  wrapper needed for external analogRead()
//  as casting behavior is undefined between different function signatures.
uint16_t read_adc_battery_current_sensor_2(uint8_t p) {
  return adc_measuring_dmc_current.readADC(BATTERY_CURRENT_SENSOR_2_PIN);
};

//  wrapper needed for external analogRead()
//  as casting behavior is undefined between different function signatures.
uint16_t read_adc_battery_current_sensor_3(uint8_t p) {
  return adc_measuring_dmc_current.readADC(BATTERY_CURRENT_SENSOR_3_PIN);
};

//  wrapper needed for external analogRead()
//  as casting behavior is undefined between different function signatures.
uint16_t read_adc_excitation_current_sensor(uint8_t p) {
  return adc_measuring_dmc_current.readADC(EXCITATION_CURRENT_SENSOR_ZOE_PIN);
};
 

// define a structure
struct test_bench_def {  
  bool mode = 0; // 1:automatik 0:manuell
  bool start = 0; // 1: ja 0: nein
  double measuring_cycle_start_time = 0;
  double time = 0;
  bool stop = 0; // 1: ja 0: nein
  bool measuring_cycle = 0; // 0: deactivated 1:activated
};

// define a structure
struct vehicle_def {
  double battery_voltage;
  double battery_current;
};

// define a structure
struct motor_control_def {
  bool control_mode = 0;  // 0 = speed controlled , 1 = torque controlled

  int excitation_current_max = EXCITATION_CURRENT_MAX;
  int torque_max =TORQUE_MAX ;
  int speed_max = SPEED_MAX;

  int throttle_poti_sensor = 0.01;

  int brake_poti_sensor = 0.01;

  int excitation_current_poti_sensor = 0.01;

  double speed_setpoint = 0;
  double torque_setpoint = 0;
  double speed_sensor = 0;
  double torque_sensor = 0;

  double speed_output = 0;
  double torque_output = 0;
  
  double excitation_current_sensor = 0;
  double excitation_current_output = 0;
  double exication_current_setpoint = 0; 

  double kp_speed = 0;
  double ki_speed = 0;
  double kd_speed = 0;

  double kp_torque = 0;
  double ki_torque = 0;
  double kd_torque = 0;

  double kp_excitation_current = 0;
  double ki_excitation_current = 0;
  double kd_excitation_current = 0;

  bool state_foot_switch = 0; // 0: open 1:closed
  bool state_brake_switch = 0; // 0: open 1:closed
};

// define a structure
struct measurement_def {
  double torque_measuring_shaft_sensor = 0;
  double speed_measuring_shaft_sensor = 0;
};

// create objects
struct test_bench_def zoe_test_bench;
struct vehicle_def power_supply;
struct motor_control_def motor_control_dmc_zoe;
struct motor_control_def motor_control_kelly_pmac;
struct measurement_def measuring_shaft;

// define send data functions

String data_string_test_bench (test_bench_def* test_bench){
    String test_bench_data = (String("tb ") + \
                test_bench->mode + " " + \
                test_bench->start + " " + \
                test_bench->stop + " " + \
                test_bench->measuring_cycle + " " + \
                test_bench->time + " " + \
                test_bench->measuring_cycle_start_time)+ " " ;
  return test_bench_data;
}

String data_string_vehicle (vehicle_def* vehicle){
    String vehicle_data = (String("vh ") + \
                vehicle->battery_current + " " + \
                vehicle->battery_voltage)+ " " ;
  return vehicle_data;
}

String data_string_motor_control_dmc_zoe(motor_control_def* motor_control) {
    String motor_control_dmc_zoe_data = (String("dmc ") +
                 motor_control->control_mode + " " +
                 motor_control->excitation_current_max + " " +
                 motor_control->torque_max + " " +
                 motor_control->speed_max + " " +
                 motor_control->throttle_poti_sensor + " " +
                 motor_control->brake_poti_sensor + " " +
                 motor_control->excitation_current_poti_sensor + " " +
                 motor_control->speed_setpoint + " " +
                 motor_control->torque_setpoint + " " +
                 motor_control->speed_sensor + " " +
                 motor_control->torque_sensor + " " +
                 motor_control->speed_output + " " +
                 motor_control->torque_output + " " +
                 motor_control->excitation_current_sensor + " " +
                 motor_control->excitation_current_output + " " +
                 motor_control->exication_current_setpoint + " " +
                 motor_control->kp_speed + " " +
                 motor_control->ki_speed + " " +
                 motor_control->kd_speed + " " +
                 motor_control->kp_torque + " " +
                 motor_control->ki_torque + " " +
                 motor_control->kd_torque + " " +
                 motor_control->kp_excitation_current + " " +
                 motor_control->ki_excitation_current + " " +
                 motor_control->kd_excitation_current + " " +
                 motor_control->state_foot_switch + " " +
                 motor_control->state_brake_switch)+ " " ;
  return motor_control_dmc_zoe_data;
}

String data_string_motor_control_kelly_pmac (motor_control_def* motor_control){
    String motor_control_kelly_pmac_data = (String("kelly ") + \
                motor_control->control_mode + " " + \
                motor_control->excitation_current_max + " " + \
                motor_control->torque_max + " " + \
                motor_control->speed_max + " " + \
                motor_control->throttle_poti_sensor + " " + \
                motor_control->brake_poti_sensor + " " + \
                motor_control->excitation_current_poti_sensor + " " + \
                motor_control->speed_setpoint + " " + \
                motor_control->torque_setpoint + " " + \
                motor_control->speed_sensor + " " + \
                motor_control->torque_sensor + " " + \
                motor_control->speed_output + " " + \
                motor_control->torque_output + " " + \
                motor_control->excitation_current_sensor + " " + \
                motor_control->excitation_current_output + " " + \
                motor_control->exication_current_setpoint + " " + \
                motor_control->kp_speed + " " + \
                motor_control->ki_speed + " " + \
                motor_control->kd_speed + " " + \
                motor_control->kp_torque + " " + \
                motor_control->ki_torque + " " + \
                motor_control->kd_torque + " " + \
                motor_control->kp_excitation_current + " " + \
                motor_control->ki_excitation_current + " " + \
                motor_control->kd_excitation_current + " " + \
                motor_control->state_foot_switch + " " + \
                motor_control->state_brake_switch)+ " " ;
  return motor_control_kelly_pmac_data;
}

String data_string_measurement (measurement_def* measurement){
    String measurement_data = (String("msr ") + \
                measurement->torque_measuring_shaft_sensor + " " + \
                measurement->speed_measuring_shaft_sensor)+ " " ;
  return measurement_data;
}

// create pid controller
#include <PID_v1.h> 
PID dmc_zoe_speed_pid(&measuring_shaft.speed_measuring_shaft_sensor, &motor_control_dmc_zoe.speed_output, &motor_control_dmc_zoe.speed_setpoint, motor_control_dmc_zoe.kp_speed, motor_control_dmc_zoe.ki_speed, motor_control_dmc_zoe.kd_speed, P_ON_E, DIRECT);
PID dmc_zoe_torque_pid(&measuring_shaft.torque_measuring_shaft_sensor, &motor_control_dmc_zoe.torque_output, &motor_control_dmc_zoe.torque_setpoint, motor_control_dmc_zoe.kp_torque, motor_control_dmc_zoe.ki_torque, motor_control_dmc_zoe.kd_torque, P_ON_E,DIRECT);
PID excitation_current_pid(&motor_control_dmc_zoe.excitation_current_sensor, &motor_control_dmc_zoe.excitation_current_output, &motor_control_dmc_zoe.exication_current_setpoint, motor_control_dmc_zoe.kp_excitation_current, motor_control_dmc_zoe.ki_excitation_current, motor_control_dmc_zoe.kd_excitation_current, P_ON_E, DIRECT);
PID kelly_pmac_speed_pid(&measuring_shaft.speed_measuring_shaft_sensor, &motor_control_kelly_pmac.speed_output, &motor_control_kelly_pmac.speed_setpoint, motor_control_kelly_pmac.kp_speed, motor_control_kelly_pmac.ki_speed, motor_control_kelly_pmac.kd_speed, P_ON_E, DIRECT);
PID kelly_pmac_torque_pid(&measuring_shaft.torque_measuring_shaft_sensor, &motor_control_kelly_pmac.torque_output, &motor_control_kelly_pmac.torque_setpoint, motor_control_kelly_pmac.kp_torque, motor_control_kelly_pmac.ki_torque, motor_control_kelly_pmac.kd_torque, P_ON_E, DIRECT);