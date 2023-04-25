// include standard libraries

#include <Arduino.h>
#include <math.h>
#include <SPI.h>
#include <stdint.h>

//#include measuring cycles
#include "measuring_cycles.h"

// include FreeRTOS libs
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <semphr.h>

// define bench limits
#define TORQUE_MAX 10
#define SPEED_MAX 500

 // define constants
#define R_EXCITATION_COIL 8.5
#define L_EXCITATION_COIL 1
#define U_REF 5
#define R1_VOLTAGE_DIVIDER_U_BATT 100000
#define R2_VOLTAGE_DIVIDER_U_BATT 5600

// define measuring shaft constants
#define SPEED_MODE_MEASURING_SHAFT 100
#define R1_VOLTAGE_DIVIDER_MEASURING_SHAFT 21.56e03
#define R2_VOLTAGE_DIVIDER_MEASURING_SHAFT 21.37e03

#define R1_LM358_OP_AMP 11.9e03
#define R2_LM358_OP_AMP 11.75e03
#define R3_LM358_OP_AMP 3.24e03
#define R4_LM358_OP_AMP 3.29e03

#define TORQUE_OFFSET 1.92
#define U_SUPPLY_MEASURING_CIRCUIT 9.9
#define deltaM 10 //delta M in Nm/V



// define Analog/Digital Pins
#define EXCITATION_CURRENT_POTI_ZOE_PIN A0
#define POTI_THROTTLE_DMC_PIN A1
#define POTI_BRAKE_DMC_PIN A2

#define POTI_EGAS_DMC_PIN A5
#define SWITCH_EGAS_DMC_PIN 28

#define FOOT_SWITCH_DMC_PIN 26

#define PWM_ERREGUNG_ZOE_PIN A13

#define FOOT_SWITCH_KELLY_PIN 22
#define BRAKE_SWITCH_KELLY_PIN 24

#define POTI_THROTTLE_KELLY_PIN A3
#define POTI_BRAKE_KELLY_PIN A4


// define ILI9341+Touchscreen
#include <SPI.h>
#include <stdint.h>
#include <TouchScreen.h>
#include <Adafruit_GFX.h>
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

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);


// define Analog-Digital Converter ADS1115
#include "ADS1X15.h"
#define ADRESS_ADC_VEHICLE_DMZ_ZOE 0x48
#define ADRESS_ADC_MEASURING_SHAFT_ZOE 0x49

ADS1115 adc_vehicle_dmc_zoe(ADRESS_ADC_VEHICLE_DMZ_ZOE);
ADS1115 adc_measuring_shaft(ADRESS_ADC_MEASURING_SHAFT_ZOE);

// define analog-digital converter DMC PINS 
#define BATTERY_VOLTAGE_SENSOR_PIN 1  
#define BATTERY_CURRENT_SENSOR_1_PIN 2
#define BATTERY_CURRENT_SENSOR_2_PIN 0
#define EXCITATION_CURRENT_SENSOR_ZOE_PIN 3

// define analog-digital converter DMC measuring shaft PINS
 #define TORQUE_MEASURING_SHAFT_PIN 1
 #define SPEED_MEASURING_SHAFT_PIN 0

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
ACS712 excitation_current_sensor(EXCITATION_CURRENT_SENSOR_ZOE_PIN, U_REF, 1023,66); // init Stomsensor Objekt: PIN, VCC, ADC Auflösung, 66mV/A

//  wrapper needed for external analogRead()
//  as casting behavior is undefined between different function signatures.
uint16_t read_adc_battery_current_sensor_1(uint8_t p) {
  return adc_vehicle_dmc_zoe.readADC(BATTERY_CURRENT_SENSOR_1_PIN);
};

//  wrapper needed for external analogRead()
//  as casting behavior is undefined between different function signatures.
uint16_t read_adc_battery_current_sensor_2(uint8_t p) {
  return adc_vehicle_dmc_zoe.readADC(BATTERY_CURRENT_SENSOR_2_PIN);
};

//  wrapper needed for external analogRead()
//  as casting behavior is undefined between different function signatures.
uint16_t read_adc_excitation_current_sensor(uint8_t p) {
  return adc_vehicle_dmc_zoe.readADC(EXCITATION_CURRENT_SENSOR_ZOE_PIN);
};


// define variables


// define objects 

// define a structure
struct test_bench {  
  bool mode = 0; // 1:automatik 0:manuell
  bool ready = 0; // 1: ja 0: nein
  bool start; // 1: ja 0: nein
  uint16_t measuring_cycle_start_time;
  bool stop; // 1: ja 0: nein
  bool measuring_cycle; // 0: deactivated 1:activated
};

// define a structure
struct vehicle {
  double battery_voltage;
  double battery_current;
};

// define a structure
struct motor_control {
  bool control_mode;  // 0 = speed controlled , 1 = torque controlled

  int excitation_current_max;
  int torque_max;
  int speed_max;

  int throttle_poti_sensor;
  int throttle_poti_sensor_t_minus_1;

  int brake_poti_sensor;
  int brake_poti_sensor_t_minus_1;

  int excitation_current_poti_sensor;
  int excitation_current_poti_sensor_t_minus_1;

  double speed_setpoint;
  double torque_setpoint;
  double speed_sensor;
  double torque_sensor;

  double speed_output;
  double torque_output;
  
  double excitation_current_sensor;
  double excitation_current_output;
  double exication_current_setpoint; 

  double kp_speed;
  double ki_speed;
  double kd_speed;

  double kp_torque;
  double ki_torque;
  double kd_torque;

  double kp_excitation_current;
  double ki_excitation_current;
  double kd_excitation_current;

  bool state_foot_switch; // 0: open 1:closed
  bool state_brake_switch; // 0: open 1:closed
};

// define a structure
struct measurement {
  double torque_measuring_shaft_sensor;
  double speed_measuring_shaft_sensor;
};

// create objects
struct test_bench zoe_test_bench;
struct vehicle power_supply;
struct motor_control motor_control_dmc_zoe;
struct motor_control motor_control_kelly_pmac;
struct measurement measuring_shaft;

// define send data functions

void send_data_test_bench (test_bench data_struct){
    char buf[sizeof(data_struct)];
    memcpy(buf, &data_struct, sizeof(data_struct)); 
    Serial.write(buf, sizeof(buf));
}

void send_data_vehicle (vehicle data_struct){
    char buf[sizeof(data_struct)];
    memcpy(buf, &data_struct, sizeof(data_struct)); 
    Serial.write(buf, sizeof(buf));
}

void send_data_motor_control (motor_control data_struct){
    char buf[sizeof(data_struct)];
    memcpy(buf, &data_struct, sizeof(data_struct)); 
    Serial.write(buf, sizeof(buf));
}

void send_data_measurement (measurement data_struct){
    char buf[sizeof(data_struct)];
    memcpy(buf, &data_struct, sizeof(data_struct)); 
    Serial.write(buf, sizeof(buf));
}

// create pid controller
#include <PID_v1.h> 
PID dmc_zoe_speed_pid(&measuring_shaft.speed_measuring_shaft_sensor, &motor_control_dmc_zoe.speed_output, &motor_control_dmc_zoe.speed_setpoint, motor_control_dmc_zoe.kp_speed, motor_control_dmc_zoe.ki_speed, motor_control_dmc_zoe.kd_speed, DIRECT);
PID dmc_zoe_torque_pid(&measuring_shaft.torque_measuring_shaft_sensor, &motor_control_dmc_zoe.torque_output, &motor_control_dmc_zoe.torque_setpoint, motor_control_dmc_zoe.kp_torque, motor_control_dmc_zoe.ki_torque, motor_control_dmc_zoe.kd_torque, DIRECT);
PID excitation_current_pid(&motor_control_dmc_zoe.excitation_current_sensor, &motor_control_dmc_zoe.excitation_current_output, &motor_control_dmc_zoe.exication_current_setpoint, motor_control_dmc_zoe.kp_excitation_current, motor_control_dmc_zoe.ki_excitation_current, motor_control_dmc_zoe.kd_excitation_current, DIRECT);
PID kelly_pmac_speed_pid(&measuring_shaft.speed_measuring_shaft_sensor, &motor_control_kelly_pmac.speed_output, &motor_control_kelly_pmac.speed_setpoint, motor_control_kelly_pmac.kp_speed, motor_control_kelly_pmac.ki_speed, motor_control_kelly_pmac.kd_speed, DIRECT);
PID kelly_pmac_torque_pid(&measuring_shaft.torque_measuring_shaft_sensor, &motor_control_kelly_pmac.torque_output, &motor_control_kelly_pmac.torque_setpoint, motor_control_kelly_pmac.kp_torque, motor_control_kelly_pmac.ki_torque, motor_control_kelly_pmac.kd_torque, DIRECT);