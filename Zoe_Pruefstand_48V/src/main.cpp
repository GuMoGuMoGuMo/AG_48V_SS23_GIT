#include "main.h"


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
        while (1){
          Serial.println();
        }
    }
    motor_control_dmc_zoe.speed_setpoint = (motor_control_dmc_zoe.throttle_poti_sensor-motor_control_dmc_zoe.brake_poti_sensor)/100.0*motor_control_dmc_zoe.speed_max;
    motor_control_dmc_zoe.exication_current_setpoint = motor_control_dmc_zoe.excitation_current_poti_sensor/100.0*motor_control.excitation_current_max;
    motor_control_kelly_pmac.speed_setpoint = (motor_control_kelly_pmac.throttle_poti_sensor-motor_control_kelly_pmac.brake_poti_sensor)/100.0*motor_control_kelly_pmac.speed_max;
}

void vehicle_task(vehicle vehicle) {
  // vehicle_task
  //read battery_voltage_pin
  vehicle.battery_voltage = adc_vehicle_dmc_zoe.readADC(BATTERY_VOLTAGE_SENSOR_PIN)*adc_vehicle_dmc_zoe.toVoltage(1)*(R2_VOLTAGE_DIVIDER_U_BATT+R1_VOLTAGE_DIVIDER_U_BATT)/R2_VOLTAGE_DIVIDER_U_BATT;
  // read battery_current_pin
  vehicle.battery_current = battery_current_sensor.mA_DC()/1000.0;

}

void motor1_control_task(motor_control motor_control, vehicle vehicle) {
    // motor1_control_task
    // calculate max excitation current, torque, speed
    motor_control.excitation_current_max = round(vehicle.battery_voltage/R_EXCITATION_COIL);
    motor_control.torque_max = TORQUE_MAX; // put code here to calculate max torque
    motor_control.speed_max = SPEED_MAX; // put code here to calculate max speed
    //read excitation_current
    motor_control.excitation_current_sensor = excitation_current_sensor.mA_DC()/1000.0;
    // read excitation_current_poti
    motor_control.excitation_current_poti_sensor = round(analogRead(EXCITATION_CURRENT_POTI_ZOE_PIN)/1024.0*100.0);
    //read gas_poti
    motor_control.throttle_poti_sensor = round(analogRead(POTI_THROTTLE_DMC_PIN)/1024.0*100.0); // 0...100
    //read bremse_poti
    motor_control.brake_poti_sensor = round(analogRead(POTI_BRAKE_DMC_PIN)/1024.0*100.0); // 0...100
    

    // pid excitation_current
    excitation_current_pid.Compute();
    // set pwm excitation_current
    int dc_pwm = round((constrain(motor_control.excitation_current_output/motor_control.excitation_current_max,0,1)*100.0));
    analogWrite(PWM_ERREGUNG_ZOE_PIN,round(dc_pwm/100.0*255.0)); // frequ= 980 Hz Value = DC 0...255
    
    // pid motor speed
    motor1_speed_pid.Compute();

    // set dac gas/brake
    int percentage = round(abs(motor_control.speed_output)/motor_control.speed_max*100.0); //= calculate percentage of gas/brake applied here;
    uint16_t output = round(percentage/100.0*4096.0); // percentage 0..100
    if (motor_control.speed_output>=0) {
      dac_gas_dmc.setVoltage(abs(output),false);
      dac_bremse_dmc.setVoltage(0,false);
      motor_control.state_foot_switch = 1;
    }
    else { // if speed_output <0
      dac_gas_dmc.setVoltage(0,false);
      dac_bremse_dmc.setVoltage(abs(output),false);
      motor_control.state_foot_switch = 1;
    }

    // set foot switch
    digitalWrite(FOOT_SWITCH_DMC_PIN,motor_control.state_foot_switch);
}

void motor2_control_task(motor_control motor_control, vehicle vehicle) {
  // motor2_control_task
    // calculate max excitation current, torque, speed
    motor_control.excitation_current_max = round(vehicle.battery_voltage/R_EXCITATION_COIL);
    motor_control.torque_max = TORQUE_MAX; // put code here to calculate max torque
    motor_control.speed_max = SPEED_MAX; // put code here to calculate max speed
  
    //read gas_poti
    motor_control.throttle_poti_sensor = round(analogRead(POTI_THROTTLE_KELLY_PIN)/1024.0*100.0); // 0...100
    //read bremse_poti
    motor_control.brake_poti_sensor = round(analogRead(POTI_BRAKE_KELLY_PIN)/1024.0*100.0); // 0...100
    
    // pid motor speed
    motor1_speed_pid.Compute();

    // set dac gas/brake
    int percentage = round(abs(motor_control.speed_output)/motor_control.speed_max*100.0); // calculate percentage of gas/brake applied;
    uint16_t output = round(percentage/100.0*4096.0); // percentage 0..100
    if (motor_control.speed_output>=0) {
      dac_gas_kelly.setVoltage(abs(output),false);
      dac_bremse_kelly.setVoltage(0,false);
      motor_control.state_foot_switch = 1;
      motor_control.state_brake_switch = 0;
    }
    else { // if speed_output <0
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

void measurement_task(measurement measurement) {
    // measurement_task
    // read torque
  measurement.torque_measuring_shaft_sensor = ((adc_measuring_shaft.toVoltage(TORQUE_MEASURING_SHAFT_PIN) - U_SUPPLY_MEASURING_CIRCUIT * (1+R3_LM358_OP_AMP/R1_LM358_OP_AMP) * R4_LM358_OP_AMP/(R4_LM358_OP_AMP+R2_LM358_OP_AMP))* (-R1_LM358_OP_AMP/R3_LM358_OP_AMP)) * deltaM - TORQUE_OFFSET;
    // read speed
  measurement.speed_measuring_shaft_sensor = (adc_measuring_shaft.toVoltage(SPEED_MEASURING_SHAFT_PIN)*((R1_VOLTAGE_DIVIDER_MEASURING_SHAFT+R2_VOLTAGE_DIVIDER_MEASURING_SHAFT)/R2_VOLTAGE_DIVIDER_MEASURING_SHAFT)) * SPEED_MODE_MEASURING_SHAFT; //in rpm 
}

void screen_task(motor_control motor_control1,motor_control motor_control2 ,vehicle vehicle,measurement measurement,test_bench test_bench) {
    // screen_task
}


// setup function
void setup() {
  // initialize serial communication
  Serial.begin(9600);

  // initialize screen
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  tft.drawRGBBitmap(10,10,hs_esslingen_logo_bitmap,HS_ESSLINGEN_LOGO_WIDTH,HS_ESSLINGEN_LOGO_HEIGHT);
  tft.setCursor(10, 60);
  tft.setTextSize(10);
  tft.println(F("AG48V Zoe Prüfstand"));
  
  // initialze analog input pins
  pinMode(EXCITATION_CURRENT_POTI_ZOE_PIN,INPUT);
  pinMode(POTI_THROTTLE_DMC_PIN,INPUT);
  pinMode(POTI_BRAKE_DMC_PIN,INPUT);

  // initialize digital output pins
  pinMode(PWM_ERREGUNG_ZOE_PIN,OUTPUT);
  digitalWrite(PWM_ERREGUNG_ZOE_PIN, LOW); 
  
  pinMode(FOOT_SWITCH_DMC_PIN,OUTPUT);
  digitalWrite(FOOT_SWITCH_DMC_PIN, LOW);  

  pinMode(FOOT_SWITCH_KELLY_PIN,OUTPUT);
  digitalWrite(FOOT_SWITCH_KELLY_PIN, LOW); 
  
  pinMode(BRAKE_SWITCH_KELLY_PIN,OUTPUT);
  digitalWrite(BRAKE_SWITCH_KELLY_PIN, LOW); 

  // initialize digital analog converters
  dac_gas_dmc.begin(ADRESS_DAC_gas_dmc);
  dac_bremse_dmc.begin(ADRESS_DAC_bremse_dmc);
  dac_gas_kelly.begin(ADRESS_DAC_gas_kelly);
  dac_bremse_kelly.begin(ADRESS_DAC_bremse_kelly);

  dac_gas_dmc.setVoltage(0,true);
  dac_bremse_dmc.setVoltage(0,true);
  dac_gas_kelly.setVoltage(0,true);
  dac_bremse_kelly.setVoltage(0,true);

  // initialize current sensors
  battery_current_sensor.setADC(read_adc_battery_current_sensor, 10, 1023);
  battery_current_sensor.autoMidPoint(); 
  excitation_current_sensor.setADC(read_adc_excitation_current_sensor, 10, 1023);
  excitation_current_sensor.autoMidPoint();

  // initialize analog digital converters
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

  // initialize pid controllers
  motor_control_dmc_zoe.speed_max = SPEED_MAX; // put code here to calculate max speed
  motor1_speed_pid.SetOutputLimits(0, double(motor_control_dmc_zoe.speed_max));
  motor1_speed_pid.SetMode(AUTOMATIC);
  
  motor_control_dmc_zoe.excitation_current_max = round(power_supply.battery_voltage/R_EXCITATION_COIL);
  excitation_current_pid.SetOutputLimits(0, double(motor_control_dmc_zoe.excitation_current_max));
  excitation_current_pid.SetMode(AUTOMATIC);

  motor_control_kelly_pmac.speed_max = SPEED_MAX; // put code here to calculate max speed
  motor2_speed_pid.SetOutputLimits(0, double(motor_control_dmc_zoe.speed_max));
  motor2_speed_pid.SetMode(AUTOMATIC);

  // create tasks
  /*xTaskCreate(test_bench_task, "Analog Output Task", 100, NULL, 1, NULL);
  xTaskCreate(vehicle_task, "Screen Task", 100, NULL, 1, NULL);
  xTaskCreate(motor1_control_task, "Control Task", 100, NULL, 1, NULL);
  xTaskCreate(motor2_control_task, "Control Task", 100, NULL, 1, NULL);
  xTaskCreate(measurement_task, "Control Task", 100, NULL, 1, NULL);
  xTaskCreate(screen_task, "Control Task", 100, NULL, 1, NULL);
  // start scheduler
  vTaskStartScheduler();
  */
}

// loop function (not used)
void loop() {}
