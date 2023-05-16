#include "main.h"

// define tasks

void test_bench_task(test_bench_def* test_bench, motor_control_def* motor_control_dmc_zoe,motor_control_def* motor_control_kelly_pmac, const measuring_cycle_def* measuring_cycle_struct[MEASURING_CYCLE_TABLE_SIZE]) {
  // test_bench_task
  test_bench->time = millis(); // set current time

  if (test_bench->mode) { // mode=1 automatic; mode=0 manual
    if(test_bench->start) { // start measuring cycle
      test_bench->measuring_cycle = 1; // acitvate measuring cycle
      test_bench->measuring_cycle_start_time = millis(); // set start time
      test_bench->start = 0; // reset start variable
    }
    if (test_bench->measuring_cycle){ //if condition to go to pre def meas cycle reading 
      int i; // var used to step trough pred def meas caycle
      // Search for the table entry with the next smaller time
      i = MEASURING_CYCLE_TABLE_SIZE - 1; // set i to last entry of pre def measuring cycle
      while (i >= 0 && measuring_cycle_struct[i]->time/1000 > (test_bench->time/1000-test_bench->measuring_cycle_start_time/1000)) {
        i--; // reduce i until time in pre def meas cycle matches measuring cycle start time
      }
      // write the setpoints for rpm and torque from the calculated time step
      if (i >= 0) {
        motor_control_dmc_zoe->speed_setpoint = measuring_cycle_struct[i]->rpm;
        motor_control_kelly_pmac->speed_setpoint = measuring_cycle_struct[i]->rpm;
        motor_control_dmc_zoe->torque_setpoint = measuring_cycle_struct[i]->torque;
        motor_control_kelly_pmac->torque_setpoint = measuring_cycle_struct[i]->torque;
        motor_control_dmc_zoe->exication_current_setpoint = measuring_cycle_struct[i]->exitacion_current;
      } else {
        test_bench->measuring_cycle = 0; // if i<0, pre def meas cycle is finished, deactivate measuring cycle
      }
    }
    if(test_bench->stop){ // condition to stop meassuring cycle setting all PID setpoints to 0
      test_bench->stop = 0;
      test_bench->measuring_cycle = 0;
      motor_control_dmc_zoe->speed_setpoint = 0;
      motor_control_kelly_pmac->speed_setpoint = 0;
      motor_control_dmc_zoe->torque_setpoint = 0;
      motor_control_kelly_pmac->torque_setpoint =0;
      motor_control_dmc_zoe->exication_current_setpoint =0;
    }
  }  
  else {
    // read excitation_current_poti
    motor_control_dmc_zoe->excitation_current_poti_sensor = 100 - round(analogRead(EXCITATION_CURRENT_POTI_ZOE_PIN)/1024.0*100.0);
    //read throttle_poti_dmc_zoe
    motor_control_dmc_zoe->throttle_poti_sensor = 100 - round(analogRead(POTI_THROTTLE_DMC_PIN)/1024.0*100.0); // 0...100
    //read break_poti_dmc_zoe
    motor_control_dmc_zoe->brake_poti_sensor = 100 - round(analogRead(POTI_BRAKE_DMC_PIN)/1024.0*100.0); // 0...100
    //read throttle_poti_kelly_pmac
    motor_control_kelly_pmac->throttle_poti_sensor = 100 - round(analogRead(POTI_THROTTLE_KELLY_PIN)/1024.0*100.0); // 0...100
    //read brake_poti_kelly_pmac
    motor_control_kelly_pmac->brake_poti_sensor = 100 - round(analogRead(POTI_BRAKE_KELLY_PIN)/1024.0*100.0); // 0...100

    // calculate Setpoints for PID-Controllers
    motor_control_dmc_zoe->speed_setpoint = (motor_control_dmc_zoe->throttle_poti_sensor-motor_control_dmc_zoe->brake_poti_sensor)/100.0*motor_control_dmc_zoe->speed_max;
    motor_control_dmc_zoe->torque_setpoint = (motor_control_dmc_zoe->throttle_poti_sensor-motor_control_dmc_zoe->brake_poti_sensor)/100.0*motor_control_dmc_zoe->torque_max;
    motor_control_dmc_zoe->exication_current_setpoint = motor_control_dmc_zoe->excitation_current_poti_sensor/100.0*motor_control_dmc_zoe->excitation_current_max;
    motor_control_kelly_pmac->speed_setpoint = (motor_control_kelly_pmac->throttle_poti_sensor-motor_control_kelly_pmac->brake_poti_sensor)/100.0*motor_control_kelly_pmac->speed_max;
    motor_control_kelly_pmac->torque_setpoint = (motor_control_kelly_pmac->throttle_poti_sensor-motor_control_kelly_pmac->brake_poti_sensor)/100.0*motor_control_kelly_pmac->torque_max;
  }
}

void vehicle_task(vehicle_def* vehicle) {
  // vehicle_task
  //read battery_voltage_pin
  vehicle->battery_voltage = adc_vehicle_dmc_zoe.readADC(BATTERY_VOLTAGE_SENSOR_PIN)*adc_vehicle_dmc_zoe.toVoltage(1)*(R2_VOLTAGE_DIVIDER_U_BATT+R1_VOLTAGE_DIVIDER_U_BATT)/R2_VOLTAGE_DIVIDER_U_BATT;
  // read battery_current_pin
  vehicle->battery_current = (battery_current_sensor_1.mA_DC()+battery_current_sensor_2.mA_DC()+battery_current_sensor_3.mA_DC())/1000.0;
}

void dmc_zoe_control_task(motor_control_def* motor_control_dmc_zoe, vehicle_def* vehicle, measurement_def* measurement) {
    // dmc_zoe_control_task

    // set speed & torque values using last value from measuring shaft 
    motor_control_dmc_zoe->speed_sensor = measurement->speed_measuring_shaft_sensor;
    motor_control_dmc_zoe->torque_sensor = measurement->torque_measuring_shaft_sensor;
    
    //read excitation_current
    motor_control_dmc_zoe->excitation_current_sensor = excitation_current_sensor.mA_DC()/1000.0;
    
    // pid excitation_current
    excitation_current_pid.Compute();
    // set pwm excitation_current
    int dc_pwm = round((constrain(motor_control_dmc_zoe->excitation_current_output/motor_control_dmc_zoe->excitation_current_max,0,1)*100.0));
    analogWrite(PWM_EXCITATION_CURRENT_ZOE_PIN,round(dc_pwm/100.0*255.0)); // frequ= 980 Hz Value = DC 0...255

    int percentage; 
    if (motor_control_dmc_zoe->control_mode){// 0 = speed controlled , 1 = torque controlled
      dmc_zoe_torque_pid.Compute(); // compute PID Output
      percentage = round(abs(motor_control_dmc_zoe->torque_output)/motor_control_dmc_zoe->torque_max*100.0); //calculate percentage of gas/brake applied here;

      // set dac gas/brake
      uint16_t output = round(percentage/100.0*4096.0); // calc output of dac, percentage 0..100
      if (motor_control_dmc_zoe->torque_output>=0) {
        dac_gas_dmc.setVoltage(abs(output),false);
        dac_bremse_dmc.setVoltage(0,false);
        motor_control_dmc_zoe->state_foot_switch = 1; 
      }
      else { // if torque_output <0
        dac_gas_dmc.setVoltage(0,false);
        dac_bremse_dmc.setVoltage(abs(output),false);
        motor_control_dmc_zoe->state_foot_switch = 0;
      }
    } 
    else {
      // pid motor speed
      dmc_zoe_speed_pid.Compute(); // compute PID Output
      percentage = round(abs(motor_control_dmc_zoe->speed_output)/motor_control_dmc_zoe->speed_max*100.0); //calculate percentage of gas/brake applied here;

      // set dac gas/brake
      uint16_t output = round(percentage/100.0*4096.0); // clac output of dac, percentage 0..100
      if (motor_control_dmc_zoe->speed_output>=0) {
        dac_gas_dmc.setVoltage(abs(output),false);
        dac_bremse_dmc.setVoltage(0,false);
        motor_control_dmc_zoe->state_foot_switch = 1;
      }
      else { // if speed_output <0
        dac_gas_dmc.setVoltage(0,false);
        dac_bremse_dmc.setVoltage(abs(output),false);
        motor_control_dmc_zoe->state_foot_switch = 0;
      } 
    }  
    // set foot switch
    digitalWrite(FOOT_SWITCH_DMC_PIN,motor_control_dmc_zoe->state_foot_switch);
}

void kelly_pmac_control_task(motor_control_def* motor_control_kelly_pmac, vehicle_def* vehicle, measurement_def* measurement) {
  // kelly_pmac_control_task
  
    // set speed & torque values using last value from measuring shaft
    motor_control_kelly_pmac->speed_sensor = measurement->speed_measuring_shaft_sensor;
    motor_control_kelly_pmac->torque_sensor = measurement->torque_measuring_shaft_sensor;

    int percentage;
    if (motor_control_kelly_pmac->control_mode){// 0 = speed controlled , 1 = torque controlled
      kelly_pmac_torque_pid.Compute(); // compute PID Output
      percentage = round(abs(motor_control_kelly_pmac->torque_output)/motor_control_kelly_pmac->torque_max*100.0); //calculate percentage of gas/brake applied here;

      // set dac gas/brake
      uint16_t output = round(percentage/100.0*4096.0); //calc output of dac, percentage 0..100
      if (motor_control_kelly_pmac->torque_output>=0) {
        dac_gas_kelly.setVoltage(abs(output),false);
        dac_bremse_kelly.setVoltage(0,false);
        motor_control_kelly_pmac->state_foot_switch = 1;
      }
      else { // if torque_output <0
        dac_gas_kelly.setVoltage(0,false);
        dac_bremse_kelly.setVoltage(abs(output),false);
        motor_control_kelly_pmac->state_foot_switch = 0;
      }
    } 
    else {
      // pid motor speed
      kelly_pmac_speed_pid.Compute(); // compute PID Output
      
      percentage = round(abs(motor_control_kelly_pmac->speed_output)/motor_control_kelly_pmac->speed_max*100.0); //calculate percentage of gas/brake applied here;

      // set dac gas/brake
      uint16_t output = round(percentage/100.0*4096.0); // calc output of dac, percentage 0..100
      if (motor_control_kelly_pmac->speed_output>=0) {
        dac_gas_kelly.setVoltage(abs(output),false);
        dac_bremse_kelly.setVoltage(0,false);
        motor_control_kelly_pmac->state_foot_switch = 1;
        motor_control_kelly_pmac->state_brake_switch = 0;
      }
      else { // if speed_output <0
        dac_gas_dmc.setVoltage(0,false);
        dac_bremse_dmc.setVoltage(abs(output),false);
        motor_control_kelly_pmac->state_foot_switch = 0;
        motor_control_kelly_pmac->state_brake_switch = 1;
      } 
    }  
    // set foot switch
    digitalWrite(FOOT_SWITCH_KELLY_PIN,motor_control_kelly_pmac->state_foot_switch);
    // set brake switch
    digitalWrite(BRAKE_SWITCH_KELLY_PIN,motor_control_kelly_pmac->state_brake_switch);
}

void measurement_task(measurement_def* measurement) {
    // measurement_task
    // read torque
  measurement->torque_measuring_shaft_sensor = ((adc_measuring_shaft.readADC(TORQUE_MEASURING_SHAFT_PIN)*adc_measuring_shaft.toVoltage(1) - U_SUPPLY_MEASURING_CIRCUIT * (1+R3_LM358_OP_AMP/R1_LM358_OP_AMP) * R4_LM358_OP_AMP/(R4_LM358_OP_AMP+R2_LM358_OP_AMP))* (-R1_LM358_OP_AMP/R3_LM358_OP_AMP)) * deltaM - TORQUE_OFFSET; // in Nm
    // read speed
  measurement->speed_measuring_shaft_sensor = (adc_measuring_shaft.readADC(SPEED_MEASURING_SHAFT_PIN)*adc_measuring_shaft.toVoltage(1)*((R1_VOLTAGE_DIVIDER_MEASURING_SHAFT+R2_VOLTAGE_DIVIDER_MEASURING_SHAFT)/R2_VOLTAGE_DIVIDER_MEASURING_SHAFT)) * SPEED_MODE_MEASURING_SHAFT; //in rpm 
}

void screen_task(motor_control_def* motor_control_dmc_zoe,motor_control_def* motor_control_kelly_pmac ,vehicle_def* vehicle,measurement_def* measurement,test_bench_def* test_bench) {
    // screen_task
    // Display:
    // Zoe Testbench        
    // Mode = auto/manual
    // Start/Restart Measuring Cycle = activated/deactivated
    // Stop Measuring Cycle = activated/deactivated
    // Measuring Cycle = aktiv/ inaktiv
    // Controll Mode DMC_ZOE = Torque/Speed
    // Cotroll Modus KELLY_PMAC = Torque/Speed
    // Excitation Current = A
    // Speed = rpm
    // Torque = N
    // Electrical Power DMC_ZOE = W
    // Mechanical Power DMC_ZOE = W
    // Motor Efficiency DMC_ZOE = %
    // Generator Efficiency DMC_ZOE = %
  tft.setCursor(2, 2);
  tft.setTextSize(3);
  tft.setTextColor(ILI9341_WHITE,ILI9341_BLACK);
  tft.println(F("AG48V Test Bench"));
  tft.setTextSize(1);
  tft.print(F("Mode                    : ")); tft.print(test_bench->mode); tft.println(F(" (0 = manual, 1 = auto)"));
  tft.print(F("Start Measuring Cycle   : ")); tft.print(test_bench->start); tft.println(F(" (0 = no, 1 = yes)"));
  tft.print(F("Stop Measuring Cycle    : ")); tft.print(test_bench->stop); tft.println(F(" (0 = no, 1 = yes)"));
  tft.print(F("Measuring Cycle         : ")); tft.print(test_bench->measuring_cycle); tft.println(F(" (0 = inactive, 1 = active)"));
  tft.print(F("Controll Mode DMC_ZOE   : ")); tft.print(motor_control_dmc_zoe->control_mode); tft.println(F(" (0 = speed, 1 = torque)"));
  tft.print(F("Controll Mode KELLY_PMAC: ")); tft.print(motor_control_kelly_pmac->control_mode); tft.println(F(" (0 = speed, 1 = torque)"));
  tft.println();
  tft.print(F("Excitation Current     : ")); tft.print(motor_control_dmc_zoe->excitation_current_sensor); tft.println(F(" A  "));
  tft.println();
  tft.print(F("Battery(DMC) Current   : ")); tft.print(vehicle->battery_current); tft.println(F(" A   "));
  tft.print(F("Battery(DMC) Voltage   : ")); tft.print(vehicle->battery_voltage); tft.println(F(" V   "));
  tft.println();
  tft.print(F("Speed : ")); tft.print(measurement->speed_measuring_shaft_sensor); tft.println(F(" rpm   "));
  tft.print(F("Torque: ")); tft.print(measurement->torque_measuring_shaft_sensor); tft.println(F(" Nm   "));
  tft.println();
  double electrical_power_dmc_zoe = vehicle->battery_voltage*vehicle->battery_current;
  double mechanical_power_dmc_zoe = measurement->speed_measuring_shaft_sensor*measurement->torque_measuring_shaft_sensor*2*PI/60;
  tft.print(F("Electrical Power DMC_ZOE    : ")); tft.print(electrical_power_dmc_zoe); tft.println(F(" W   "));
  tft.print(F("Mechanical Power DMC_ZOE    : ")); tft.print(mechanical_power_dmc_zoe); tft.println(F(" W   "));
  double motor_efficiency_dmc_zoe;
  double generator_efficiency_dmc_zoe;
  if(mechanical_power_dmc_zoe<electrical_power_dmc_zoe){
    motor_efficiency_dmc_zoe = mechanical_power_dmc_zoe/electrical_power_dmc_zoe;
    generator_efficiency_dmc_zoe = 0;
  }
  else{
    motor_efficiency_dmc_zoe = 0;
    generator_efficiency_dmc_zoe = electrical_power_dmc_zoe/mechanical_power_dmc_zoe;  
  }
  tft.print(F("Motor Efficiency DMC_ZOE    : ")); tft.print(motor_efficiency_dmc_zoe); tft.println(F(" %   "));
  tft.print(F("Generator Efficiency DMC_ZOE: ")); tft.print(generator_efficiency_dmc_zoe); tft.println(F(" %   "));
}

void touch_task(test_bench_def* test_bench){
  //touch task
  TSPoint t;    // create touch variable to save not calibrated touch points
  t=ts.getPoint();    // read touch points
  if (t.z > ts.pressureThreshhold) {    //if touch pressure is higher than treshold its a touch event
    touchPoint.x=map(t.y,Y_MAX,Y_MIN,0,ILI9341_TFTHEIGHT); // Kalibrierung und Speichern in globaler Variable
    touchPoint.y=map(t.x,X_MIN,X_MAX,0,ILI9341_TFTWIDTH); // Kalibrierung und Speichern in globaler Variable
    
    // Show Coordinates on serial monitor for debugging
    //Serial.print("X = "); Serial.print(touchPoint.x);
    //Serial.print("\tY = "); Serial.print(touchPoint.y);
    //Serial.print("\tPressure = "); Serial.println(t.z);
    
    // check if button 1 is pressed
    if (touchPoint.x > BUTTON1_TOP_LEFT_X && touchPoint.x <(BUTTON1_TOP_LEFT_X+BUTTON1_WIDTH) && touchPoint.y >BUTTON1_TOP_LEFT_Y && touchPoint.y <(BUTTON1_TOP_LEFT_Y+BUTTON1_HEIGHT)){ // mode button
      tft.drawRect(BUTTON1_TOP_LEFT_X,BUTTON1_TOP_LEFT_Y,BUTTON1_WIDTH,BUTTON1_HEIGHT,ILI9341_BLUE);
      tft.drawRect(BUTTON2_TOP_LEFT_X,BUTTON2_TOP_LEFT_Y,BUTTON2_WIDTH,BUTTON2_HEIGHT,ILI9341_WHITE);
      tft.drawRect(BUTTON3_TOP_LEFT_X,BUTTON3_TOP_LEFT_Y,BUTTON3_WIDTH,BUTTON3_HEIGHT,ILI9341_WHITE);
      if(test_bench->mode){
        test_bench->mode = 0; // set mode
      }
      else{
        test_bench->mode = 1; // set mode
      }
    }

    // check if button 2 is pressed
    if (touchPoint.x > BUTTON2_TOP_LEFT_X && touchPoint.x <(BUTTON2_TOP_LEFT_X+BUTTON2_WIDTH) && touchPoint.y >BUTTON2_TOP_LEFT_Y && touchPoint.y <(BUTTON2_TOP_LEFT_Y+BUTTON2_HEIGHT)){ // start button
      tft.drawRect(BUTTON1_TOP_LEFT_X,BUTTON1_TOP_LEFT_Y,BUTTON1_WIDTH,BUTTON1_HEIGHT,ILI9341_WHITE);
      tft.drawRect(BUTTON2_TOP_LEFT_X,BUTTON2_TOP_LEFT_Y,BUTTON2_WIDTH,BUTTON2_HEIGHT,ILI9341_BLUE);
      tft.drawRect(BUTTON3_TOP_LEFT_X,BUTTON3_TOP_LEFT_Y,BUTTON3_WIDTH,BUTTON3_HEIGHT,ILI9341_WHITE);
      if(test_bench->start){
        test_bench->start = 0; //set start
      }
      else{
        test_bench->start = 1; //set start
      }
    }

    // check if button 3 is pressed
    if (touchPoint.x > BUTTON3_TOP_LEFT_X && touchPoint.x <(BUTTON3_TOP_LEFT_X+BUTTON3_WIDTH) && touchPoint.y >BUTTON3_TOP_LEFT_Y && touchPoint.y <(BUTTON3_TOP_LEFT_Y+BUTTON3_HEIGHT)){ // stop button
      tft.drawRect(BUTTON1_TOP_LEFT_X,BUTTON1_TOP_LEFT_Y,BUTTON1_WIDTH,BUTTON1_HEIGHT,ILI9341_WHITE);
      tft.drawRect(BUTTON2_TOP_LEFT_X,BUTTON2_TOP_LEFT_Y,BUTTON2_WIDTH,BUTTON2_HEIGHT,ILI9341_WHITE);
      tft.drawRect(BUTTON3_TOP_LEFT_X,BUTTON3_TOP_LEFT_Y,BUTTON3_WIDTH,BUTTON3_HEIGHT,ILI9341_BLUE);
      if(test_bench->stop){
        test_bench->stop = 0; // set stop
      }
      else{
        test_bench->stop = 1; // set stop
      }
    }
      
  }
}

void send_data_task(test_bench_def* test_bench, vehicle_def* vehicle, motor_control_def* motor_control_dmc_zoe, motor_control_def* motor_control_kelly_pmac, measurement_def* measurement){
  //send_data_task
  Serial.print(data_string_test_bench(test_bench) + data_string_vehicle(vehicle) + data_string_motor_control_dmc_zoe(motor_control_dmc_zoe) + data_string_motor_control_kelly_pmac(motor_control_kelly_pmac) + data_string_measurement(measurement));
  Serial.write(13); // send terminator 1
  Serial.write(10); // send terminator 2
}

// setup function
void setup() {
  
  // initialize serial communication
  Serial.begin(115200,SERIAL_8N1);
  
  // initialize screen
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(2, 2);
  tft.setTextSize(3);
  tft.println(F("AG48V Test Bench"));
  tft.println();
  // show logo
  tft.drawRGBBitmap(100,100,hs_esslingen_logo_bitmap,HS_ESSLINGEN_LOGO_WIDTH,HS_ESSLINGEN_LOGO_HEIGHT);
  delay(1000);
  
  // initialze analog input pins
  pinMode(EXCITATION_CURRENT_POTI_ZOE_PIN,INPUT);
  pinMode(POTI_THROTTLE_DMC_PIN,INPUT);
  pinMode(POTI_BRAKE_DMC_PIN,INPUT);

  // initialize digital output pins
  pinMode(PWM_EXCITATION_CURRENT_ZOE_PIN,OUTPUT);
  digitalWrite(PWM_EXCITATION_CURRENT_ZOE_PIN, LOW); 
  
  pinMode(FOOT_SWITCH_DMC_PIN,OUTPUT);
  digitalWrite(FOOT_SWITCH_DMC_PIN, LOW);  

  pinMode(FOOT_SWITCH_KELLY_PIN,OUTPUT);
  digitalWrite(FOOT_SWITCH_KELLY_PIN, LOW); 
   
  pinMode(BRAKE_SWITCH_KELLY_PIN,OUTPUT);
  digitalWrite(BRAKE_SWITCH_KELLY_PIN, LOW); 

  pinMode(SWITCH_D_N_DMC_PIN,OUTPUT);   // set motors from Neutral to drive
  pinMode(SWITCH_D_N_KELLY_PIN,OUTPUT);
  digitalWrite(SWITCH_D_N_DMC_PIN,HIGH);
  digitalWrite(SWITCH_D_N_KELLY_PIN,HIGH);
  
  
  // initialize digital analog converters
  dac_gas_dmc.begin(ADRESS_DAC_gas_dmc);
  dac_bremse_dmc.begin(ADRESS_DAC_bremse_dmc);
  dac_gas_kelly.begin(ADRESS_DAC_gas_kelly);
  dac_bremse_kelly.begin(ADRESS_DAC_bremse_kelly);

  dac_gas_dmc.setVoltage(0,true);
  dac_bremse_dmc.setVoltage(0,true);
  dac_gas_kelly.setVoltage(0,true);
  dac_bremse_kelly.setVoltage(0,true);
  

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
  
   if (!adc_measuring_dmc_current.begin()) {
    Serial.println("Failed to initialize adc_measuring_dmc_current.");
    while (1);
  }
  adc_measuring_dmc_current.setGain(0);
  
  
  // initialize current sensors
  battery_current_sensor_1.setADC(read_adc_battery_current_sensor_1, 10, 1023);
  battery_current_sensor_1.autoMidPoint(); 
  battery_current_sensor_2.setADC(read_adc_battery_current_sensor_2, 10, 1023);
  battery_current_sensor_2.autoMidPoint(); 
  battery_current_sensor_3.setADC(read_adc_battery_current_sensor_3, 10, 1023);
  battery_current_sensor_3.autoMidPoint(); 
  excitation_current_sensor.setADC(read_adc_excitation_current_sensor, 10, 1023);
  excitation_current_sensor.autoMidPoint();   

  //set motor control mode
  motor_control_dmc_zoe.control_mode = 0; // 0 = speed controlled , 1 = torque controlled
  motor_control_kelly_pmac.control_mode = 0; // 0 = speed controlled , 1 = torque controlled

  //set max torque, speed, excitation current DMC_ZOE
  motor_control_dmc_zoe.excitation_current_max = EXCITATION_CURRENT_MAX;
  motor_control_dmc_zoe.torque_max = TORQUE_MAX; 
  motor_control_dmc_zoe.speed_max = SPEED_MAX;

  // set max torque, speed kelly_pmac
  motor_control_kelly_pmac.torque_max = TORQUE_MAX; 
  motor_control_kelly_pmac.speed_max = SPEED_MAX;

  // set PID Parameter DMC_ZOE
  motor_control_dmc_zoe.kp_speed=2;
  motor_control_dmc_zoe.ki_speed=5;
  motor_control_dmc_zoe.kd_speed=0;

  motor_control_dmc_zoe.kp_torque=2;
  motor_control_dmc_zoe.ki_torque=1;
  motor_control_dmc_zoe.kd_torque=0;

  // set PID Parameter Kelly_PMAC
  motor_control_kelly_pmac.kp_speed=3;
  motor_control_kelly_pmac.ki_speed=13;
  motor_control_kelly_pmac.kd_speed=0;

  motor_control_kelly_pmac.kp_torque=2;
  motor_control_kelly_pmac.ki_torque=1;
  motor_control_kelly_pmac.kd_torque=0;

  // initialize pid controllers
  motor_control_dmc_zoe.speed_max = SPEED_MAX; // put code here to calculate max speed
  dmc_zoe_speed_pid.SetOutputLimits(0, double(motor_control_dmc_zoe.speed_max));
  dmc_zoe_speed_pid.SetMode(AUTOMATIC);
  dmc_zoe_speed_pid.SetTunings(motor_control_dmc_zoe.kp_speed, motor_control_dmc_zoe.ki_speed, motor_control_dmc_zoe.kd_speed);
   
  motor_control_dmc_zoe.torque_max = TORQUE_MAX; // put code here to calculate max speed
  dmc_zoe_torque_pid.SetOutputLimits(0, double(motor_control_dmc_zoe.torque_max));
  dmc_zoe_torque_pid.SetMode(AUTOMATIC);
  dmc_zoe_torque_pid.SetTunings(motor_control_dmc_zoe.kp_torque, motor_control_dmc_zoe.ki_torque, motor_control_dmc_zoe.kd_torque);

  motor_control_dmc_zoe.excitation_current_max = round(power_supply.battery_voltage/R_EXCITATION_COIL);
  excitation_current_pid.SetOutputLimits(0, double(motor_control_dmc_zoe.excitation_current_max));
  excitation_current_pid.SetMode(AUTOMATIC);
  excitation_current_pid.SetTunings(motor_control_dmc_zoe.kp_excitation_current, motor_control_dmc_zoe.ki_excitation_current, motor_control_dmc_zoe.kd_excitation_current);

  motor_control_kelly_pmac.speed_max = SPEED_MAX; // put code here to calculate max speed
  kelly_pmac_speed_pid.SetOutputLimits(0, double(motor_control_kelly_pmac.speed_max));
  kelly_pmac_speed_pid.SetMode(AUTOMATIC);
  kelly_pmac_speed_pid.SetTunings(motor_control_kelly_pmac.kp_speed, motor_control_kelly_pmac.ki_speed, motor_control_kelly_pmac.kd_speed);

  motor_control_kelly_pmac.torque_max = TORQUE_MAX; // put code here to calculate max speed
  kelly_pmac_torque_pid.SetOutputLimits(0, double(motor_control_kelly_pmac.torque_max));
  kelly_pmac_torque_pid.SetMode(AUTOMATIC);
  kelly_pmac_torque_pid.SetTunings(motor_control_kelly_pmac.kp_torque, motor_control_kelly_pmac.ki_torque, motor_control_kelly_pmac.kd_torque);

  // create tasks
  /*xTaskCreate(test_bench_task, "Analog Output Task", 100, NULL, 1, NULL);
  xTaskCreate(vehicle_task, "Screen Task", 100, NULL, 1, NULL);
  xTaskCreate(dmc_zoe_control_task, "Control Task", 100, NULL, 1, NULL);
  xTaskCreate(kelly_pmac_control_task, "Control Task", 100, NULL, 1, NULL);
  xTaskCreate(measurement_task, "Control Task", 100, NULL, 1, NULL);
  xTaskCreate(screen_task, "Control Task", 100, NULL, 1, NULL);
  // start scheduler
  vTaskStartScheduler();
  */
  
  // init buttons for touchscreen
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextSize(1);
  tft.drawRect(BUTTON1_TOP_LEFT_X,BUTTON1_TOP_LEFT_Y,BUTTON1_WIDTH,BUTTON1_HEIGHT,ILI9341_WHITE);
  tft.fillRect(BUTTON1_TOP_LEFT_X+1,BUTTON1_TOP_LEFT_Y+1,BUTTON1_WIDTH-2,BUTTON1_HEIGHT-2,ILI9341_DARKGREEN);
  tft.setCursor(BUTTON1_TOP_LEFT_X+2, BUTTON1_TOP_LEFT_Y+2);
  tft.print("Mode");
  tft.drawRect(BUTTON2_TOP_LEFT_X,BUTTON2_TOP_LEFT_Y,BUTTON2_WIDTH,BUTTON2_HEIGHT,ILI9341_WHITE);
  tft.fillRect(BUTTON2_TOP_LEFT_X+1,BUTTON2_TOP_LEFT_Y+1,BUTTON2_WIDTH-2,BUTTON2_HEIGHT-2,ILI9341_DARKGREEN);
  tft.setCursor(BUTTON2_TOP_LEFT_X+2, BUTTON2_TOP_LEFT_Y+2);
  tft.print("Start/Restart");
  tft.setCursor(BUTTON2_TOP_LEFT_X+2, BUTTON2_TOP_LEFT_Y+10);
  tft.print("Cycle");
  tft.drawRect(BUTTON3_TOP_LEFT_X,BUTTON3_TOP_LEFT_Y,BUTTON3_WIDTH,BUTTON3_HEIGHT,ILI9341_WHITE);
  tft.fillRect(BUTTON3_TOP_LEFT_X+1,BUTTON3_TOP_LEFT_Y+1,BUTTON3_WIDTH-2,BUTTON3_HEIGHT-2,ILI9341_DARKGREEN);
  tft.setCursor(BUTTON3_TOP_LEFT_X+2, BUTTON3_TOP_LEFT_Y+2);
  tft.print("Stop");
  tft.setCursor(BUTTON3_TOP_LEFT_X+2, BUTTON3_TOP_LEFT_Y+10);
  tft.print("Cycle");
}

// loop function
void loop() {
  test_bench_task(&zoe_test_bench,&motor_control_dmc_zoe,&motor_control_kelly_pmac,(const measuring_cycle_def**)&measuring_cycle_1);
  vehicle_task(&power_supply);
  //dmc_zoe_control_task(&motor_control_dmc_zoe,&power_supply,&measuring_shaft);
  kelly_pmac_control_task(&motor_control_kelly_pmac,&power_supply,&measuring_shaft);
  measurement_task(&measuring_shaft);
  touch_task(&zoe_test_bench);
  screen_task(&motor_control_dmc_zoe,&motor_control_kelly_pmac,&power_supply,&measuring_shaft,&zoe_test_bench);
  send_data_task(&zoe_test_bench,&power_supply,&motor_control_dmc_zoe,&motor_control_kelly_pmac,&measuring_shaft);
}
  