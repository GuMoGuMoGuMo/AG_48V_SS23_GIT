#include <Arduino.h>
#include <math.h>

// include libraries
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include <SPI.h>

// define pins
#ifdef ESP8266
   #define STMPE_CS 16
   #define TFT_CS   0
   #define TFT_DC   15
   #define SD_CS    2
#elif defined(ESP32) && !defined(ARDUINO_ADAFRUIT_FEATHER_ESP32S2)
   #define STMPE_CS 32
   #define TFT_CS   15
   #define TFT_DC   33
   #define SD_CS    14
#elif defined(TEENSYDUINO)
   #define TFT_DC   10
   #define TFT_CS   4
   #define STMPE_CS 3
   #define SD_CS    8
#elif defined(ARDUINO_STM32_FEATHER)
   #define TFT_DC   PB4
   #define TFT_CS   PA15
   #define STMPE_CS PC7
   #define SD_CS    PC5
#elif defined(ARDUINO_NRF52832_FEATHER)  /* BSP 0.6.5 and higher! */
   #define TFT_DC   11
   #define TFT_CS   31
   #define STMPE_CS 30
   #define SD_CS    27
#elif defined(ARDUINO_MAX32620FTHR) || defined(ARDUINO_MAX32630FTHR)
   #define TFT_DC   P5_4
   #define TFT_CS   P5_3
   #define STMPE_CS P3_3
   #define SD_CS    P3_2
#else
    // Anything else, defaults!
   #define STMPE_CS 6
   #define TFT_CS   9
   #define TFT_DC   10
   #define SD_CS    5
#endif

#define BATTERY_VOLTAGE_SENSOR_PIN 1  
#define BATTERY_CURRENT_SENSOR_PIN 1

#define FOOT_SWITCH_DMC_PIN 1
#define BRAKE_SWITCH_DMC_PIN 1
#define PWM_ERREGUNG_ZOE_PIN 1

#define EXCITATION_CURRENT_SENSOR_ZOE_PIN 1

#define EXCITATION_CURRENT_POTI_ZOE_PIN 1
#define GAS_POTI_ZOE_PIN 1
#define BREMS_POTI_ZOE_PIN 1

#define FOOT_SWITCH_KELLY_PIN 1
#define BRAKE_SWITCH_KELLY_PIN 1

#define GAS_POTI_KELLY_PIN 1
#define BREMS_POTI_KELLY_PIN 1



// define constants
#define R_ERREGERCOIL 1
#define U_REF 1
#define R1_VOLTAGE_DIVIDER 1
#define R2_VOLTAGE_DIVIDER 1

// define variables

// create objects 

// define a structure
struct test_bench {
  int time;
  int time_t_minus_1;
  
  bool mode = 0; // 1:automatik 0:manuell
  bool ready = 0; // 1: ja 0: nein
  bool start; // 1: ja 0: nein
  bool stop; // 1: ja 0: nein

  int start_time;
  int stop_time;

  // add more members as needed
};

// define a structure
struct vehicle {
  double battery_voltage;
  double battery_current;
  // add more members as needed
};

// define a structure
struct motor_control {
  int excitation_current_max;
  int torque_max;
  int speed_max;

  int gaspoti_sensor;
  int gaspoti_sensor_t_minus_1;

  int bremspoti_sensor;
  int bremspoti_sensor_t_minus_1;

  int excitation_current_poti_sensor;
  int excitation_current_poti_sensor_t_minus_1;

  double speed_setpoint;
  double speed_setpoint_t_minus_1;
  double torque_setpoint;
  double torque_setpoint_t_minus_1;
  double speed_ist;
  double speed_ist_t_minus_1;
  double torque_ist;
  double torque_ist_t_minus_1;

  double drehzahl_output;
  double torque_output;
  
  double excitation_current_ist;
  double excitation_current_ist_t_minus_1;
  double excitation_current_output;
  double exication_current_setpoint; 

  double kp_speed;
  double ki_speed;
  double kd_speed;

  double kp_excitation_current;
  double ki_excitation_current;
  double kd_excitation_current;

  bool state_foot_switch; // 0: open 1:closed
  bool state_brake_switch; // 0: open 1:closed
  
  // add more members as needed
};

// define a structure
struct measurement {
  double torque_messwelle_sensor;
  double torque_messwelle_sensor_t_minus_1;
  double drehzahl_messwelle_sensor;
  double drehzahl_messwelle_sensor_t_minus_1;

  // add more members as needed
};

// create objects
struct test_bench zoe_test_bench;
struct vehicle power_supply;
struct motor_control motor_control_dmc_zoe;
struct motor_control motor_control_kelly_pmac;
struct measurement measuring_shaft; 

// display
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

// adcs Analog-Digital Converter ADS1115
#include "ADS1X15.h"
#define ADRESS_ADC_VEHICLE_DMZ_ZOE 0x48
#define ADRESS_ADC_MEASURING_SHAFT_ZOE 0x49

ADS1115 adc_vehicle_dmc_zoe(ADRESS_ADC_VEHICLE_DMZ_ZOE);
ADS1115 adc_measuring_shaft(ADRESS_ADC_MEASURING_SHAFT_ZOE);


// current sensors
#include <ACS712.h> // Stromsensor lib
ACS712 battery_current_sensor(BATTERY_CURRENT_SENSOR_PIN, U_REF, 1023,66); // init Stomsensor Objekt: PIN, VCC, ADC Auflösung, 66mV/A
ACS712 excitation_current_sensor(EXCITATION_CURRENT_SENSOR_ZOE_PIN, U_REF, 1023,66); // init Stomsensor Objekt: PIN, VCC, ADC Auflösung, 66mV/A

//  wrapper needed for external analogRead()
//  as casting behavior is undefined between different function signatures.
uint16_t read_adc_battery_current_sensor(ADS1115 adc) {
  return adc.readADC(BATTERY_CURRENT_SENSOR_PIN);
  //  replace with an external ADC call.
  //  return ADS.readADC(p);
};

//  wrapper needed for external analogRead()
//  as casting behavior is undefined between different function signatures.
uint16_t read_adc_excitation_current_sensor(ADS1115 adc) {
  return adc.readADC(EXCITATION_CURRENT_SENSOR_ZOE_PIN);
  //  replace with an external ADC call.
  //  return ADS.readADC(p);
};


// dacs
#include <Adafruit_MCP4725.h>

#define ADRESS_DAC_gas_dmc 0x60
#define ADRESS_DAC_bremse_dmc 0x61
#define ADRESS_DAC_gas_kelly 0x62
#define ADRESS_DAC_bremse_kelly 0x63
Adafruit_MCP4725 dac_gas_dmc;
Adafruit_MCP4725 dac_bremse_dmc;
Adafruit_MCP4725 dac_gas_kelly;
Adafruit_MCP4725 dac_bremse_kelly;

// create pid controller
#include <PID_v1.h> 
PID motor1_speed_pid(&measuring_shaft.drehzahl_messwelle_sensor, &motor_control_dmc_zoe.drehzahl_output, &motor_control_dmc_zoe.speed_setpoint, motor_control_dmc_zoe.kp_speed, motor_control_dmc_zoe.ki_speed, motor_control_dmc_zoe.kd_speed, DIRECT);
PID excitation_current_pid(&motor_control_dmc_zoe.excitation_current_ist, &motor_control_dmc_zoe.excitation_current_output, &motor_control_dmc_zoe.exication_current_setpoint, motor_control_dmc_zoe.kp_excitation_current, motor_control_dmc_zoe.ki_excitation_current, motor_control_dmc_zoe.kd_excitation_current, DIRECT);
PID motor2_speed_pid(&measuring_shaft.drehzahl_messwelle_sensor, &motor_control_kelly_pmac.drehzahl_output, &motor_control_kelly_pmac.speed_setpoint, motor_control_kelly_pmac.kp_speed, motor_control_kelly_pmac.ki_speed, motor_control_kelly_pmac.kd_speed, DIRECT);



// define tasks
/*
void sensor_task(void *pvParameters) {
    // read sensor value
    
    vTaskDelay(10); // wait for 10 ms
}
*/

void test_bench_task(test_bench test_bench, motor_control motor_control) {
    // test_bench_task
    if (test_bench.mode) { // mode=1 automatic; mode=0 manual
        // hier code mit tabelle prüfgramm zeit sollmoment solldrezahl
    }
    motor_control_dmc_zoe.speed_setpoint = (motor_control_dmc_zoe.gaspoti_sensor-motor_control_dmc_zoe.bremspoti_sensor)/100.0*motor_control_dmc_zoe.speed_max;
    motor_control_dmc_zoe.exication_current_setpoint = motor_control_dmc_zoe.excitation_current_poti_sensor/100.0*motor_control.excitation_current_max;
    motor_control_kelly_pmac.speed_setpoint = (motor_control_kelly_pmac.gaspoti_sensor-motor_control_kelly_pmac.bremspoti_sensor)/100.0*motor_control_kelly_pmac.speed_max;
}

void vehicle_task(vehicle vehicle) {
  // vehicle_task
  //read battery_voltage_pin
  vehicle.battery_voltage = adc_vehicle_dmc_zoe.readADC(BATTERY_VOLTAGE_SENSOR_PIN)*adc_vehicle_dmc_zoe.toVoltage(1)*(R2_VOLTAGE_DIVIDER+R1_VOLTAGE_DIVIDER)/R2_VOLTAGE_DIVIDER;
  // read battery_current_pin
  vehicle.battery_current = battery_current_sensor.mA_DC()/1000.0;

}

void motor1_control_task(motor_control motor_control, vehicle vehicle) {
    // motor1_control_task
    // calculate max excitation current, torque, speed
    motor_control.excitation_current_max = round(vehicle.battery_voltage/R_ERREGERCOIL);
    motor_control.torque_max; // put code here to calculate max torque
    motor_control.speed_max; // put code here to calculate max speed
    //read excitation_current
    motor_control.excitation_current_ist = excitation_current_sensor.mA_DC()/1000.0;
    // read excitation_current_poti
    motor_control.excitation_current_poti_sensor = round(analogRead(EXCITATION_CURRENT_POTI_ZOE_PIN)/1024.0*100.0);
    //read gas_poti
    motor_control.gaspoti_sensor = round(analogRead(GAS_POTI_ZOE_PIN)/1024.0*100.0); // 0...100
    //read bremse_poti
    motor_control.bremspoti_sensor = round(analogRead(BREMS_POTI_ZOE_PIN)/1024.0*100.0); // 0...100
    

    // pid excitation_current
    excitation_current_pid.Compute();
    // set pwm excitation_current
    int dc_pwm = round((constrain(motor_control.excitation_current_output/motor_control.excitation_current_max,0,1)*100.0));
    analogWrite(PWM_ERREGUNG_ZOE_PIN,round(dc_pwm/100.0*255.0)); // frequ= 980 Hz Value = DC 0...255
    
    // pid motor speed
    motor1_speed_pid.Compute();

    // set dac gas/brake
    int prozent = round(abs(motor_control.drehzahl_output)/motor_control.speed_max*100.0); //= calculate percentage of gas/brake applied here;
    uint16_t output = round(prozent/100.0*4096.0); // Prozent 0..100
    if (motor_control.drehzahl_output>=0) {
      dac_gas_dmc.setVoltage(abs(output),false);
      dac_bremse_dmc.setVoltage(0,false);
      motor_control.state_foot_switch = 1;
      motor_control.state_brake_switch = 0;
    }
    else { // if drehzahl_output <0
      dac_gas_dmc.setVoltage(0,false);
      dac_bremse_dmc.setVoltage(abs(output),false);
      motor_control.state_foot_switch = 1;
      motor_control.state_brake_switch = 0;
    }

    // set foot switch
    digitalWrite(FOOT_SWITCH_DMC_PIN,motor_control.state_foot_switch);
    // set brake switch
    digitalWrite(BRAKE_SWITCH_DMC_PIN,motor_control.state_brake_switch);
}

void motor2_control_task(motor_control motor_control, vehicle vehicle) {
  // motor2_control_task
    // calculate max excitation current, torque, speed
    motor_control.excitation_current_max = round(vehicle.battery_voltage/R_ERREGERCOIL);
    motor_control.torque_max; // put code here to calculate max torque
    motor_control.speed_max; // put code here to calculate max speed
  
    //read gas_poti
    motor_control.gaspoti_sensor = round(analogRead(GAS_POTI_KELLY_PIN)/1024.0*100.0); // 0...100
    //read bremse_poti
    motor_control.bremspoti_sensor = round(analogRead(BREMS_POTI_KELLY_PIN)/1024.0*100.0); // 0...100
    
    // pid motor speed
    motor1_speed_pid.Compute();

    // set dac gas/brake
    int prozent = round(abs(motor_control.drehzahl_output)/motor_control.speed_max*100.0); // calculate percentage of gas/brake applied;
    uint16_t output = round(prozent/100.0*4096.0); // prozent 0..100
    if (motor_control.drehzahl_output>=0) {
      dac_gas_kelly.setVoltage(abs(output),false);
      dac_bremse_kelly.setVoltage(0,false);
      motor_control.state_foot_switch = 1;
      motor_control.state_brake_switch = 0;
    }
    else { // if drehzahl_output <0
      dac_gas_kelly.setVoltage(0,false);
      dac_bremse_kelly.setVoltage(abs(output),false);
      motor_control.state_foot_switch = 0;
      motor_control.state_brake_switch = 1;
    }

    // set foot switch
    digitalWrite(FOOT_SWITCH_KELLY_PIN,motor_control.state_foot_switch);
    // set brake switch
    digitalWrite(BRAKE_SWITCH_KELLY_PIN,motor_control.state_brake_switch);
}

void measurement_task(void *pvParameters) {
    // measurement_task
    
    // read torque

    // read speed
  
}

void screen_task(void *pvParameters) {
    // screen_task
    
    // print desired current to LCD
    
}



// setup function
void setup() {
  // initialize serial communication
  Serial.begin(9600);

  // initialize analog output pins
  
  // initialze analog input pins
  pinMode(EXCITATION_CURRENT_POTI_ZOE_PIN,INPUT);
  pinMode(GAS_POTI_ZOE_PIN,INPUT);
  pinMode(BREMS_POTI_ZOE_PIN,INPUT);

  // initialize digital output pins
  pinMode(PWM_ERREGUNG_ZOE_PIN,OUTPUT);
  digitalWrite(PWM_ERREGUNG_ZOE_PIN, LOW); 
  
  pinMode(FOOT_SWITCH_DMC_PIN,OUTPUT);
  digitalWrite(FOOT_SWITCH_DMC_PIN, LOW); 
  
  pinMode(BRAKE_SWITCH_DMC_PIN,OUTPUT);
  digitalWrite(BRAKE_SWITCH_DMC_PIN, LOW); 

  pinMode(FOOT_SWITCH_KELLY_PIN,OUTPUT);
  digitalWrite(FOOT_SWITCH_KELLY_PIN, LOW); 
  
  pinMode(BRAKE_SWITCH_KELLY_PIN,OUTPUT);
  digitalWrite(BRAKE_SWITCH_KELLY_PIN, LOW); 

  // initialize dacs
  dac_gas_dmc.begin(ADRESS_DAC_gas_dmc);
  dac_bremse_dmc.begin(ADRESS_DAC_bremse_dmc);
  dac_gas_kelly.begin(ADRESS_DAC_gas_kelly);
  dac_bremse_kelly.begin(ADRESS_DAC_bremse_kelly);

  dac_gas_dmc.setVoltage(0,false);
  dac_bremse_dmc.setVoltage(0,false);
  dac_gas_kelly.setVoltage(0,false);
  dac_bremse_kelly.setVoltage(0,false);



  // initialize current sensors
  battery_current_sensor.setADC(read_adc_battery_current_sensor, 10, 1023);
  battery_current_sensor.autoMidPoint(); 
  excitation_current_sensor.setADC(read_adc_excitation_current_sensor, 10, 1023);
  excitation_current_sensor.autoMidPoint();

  // initialize adcs
  if (!adc_vehicle_dmc_zoe.begin()) {
    Serial.println("Failed to initialize adc_vehicle_dmc_zoe.");
    while (1);
  }
  adc_vehicle_dmc_zoe.setGain(0);

  if (!adc_measuring_shaft.begin()) {
    Serial.println("Failed to initialize adc_measuring_shaft.");
    while (1);
  }
  adc_measuring_shaft.setGain(0);

  // initialize LCD screen

  // initialize pid controllers
  motor_control_dmc_zoe.speed_max; // put code here to calculate max speed
  motor1_speed_pid.SetOutputLimits(0, double(motor_control_dmc_zoe.speed_max));
  motor1_speed_pid.SetMode(AUTOMATIC);
  
  motor_control_dmc_zoe.excitation_current_max = round(power_supply.battery_voltage/R_ERREGERCOIL);
  excitation_current_pid.SetOutputLimits(0, double(motor_control_dmc_zoe.excitation_current_max));
  excitation_current_pid.SetMode(AUTOMATIC);

  motor_control_kelly_pmac.speed_max; // put code here to calculate max speed
  motor2_speed_pid.SetOutputLimits(0, double(motor_control_dmc_zoe.speed_max));
  motor2_speed_pid.SetMode(AUTOMATIC);

  // create tasks
  xTaskCreate(test_bench_task, "Analog Output Task", 100, NULL, 1, NULL);
  xTaskCreate(vehicle_task, "Screen Task", 100, NULL, 1, NULL);
  xTaskCreate(motor1_control_task, "Control Task", 100, NULL, 1, NULL);
  xTaskCreate(motor2_control_task, "Control Task", 100, NULL, 1, NULL);
  xTaskCreate(measurement_task, "Control Task", 100, NULL, 1, NULL);
  xTaskCreate(screen_task, "Control Task", 100, NULL, 1, NULL);
  // start scheduler
  vTaskStartScheduler();
}

// loop function (not used)
void loop() {}
