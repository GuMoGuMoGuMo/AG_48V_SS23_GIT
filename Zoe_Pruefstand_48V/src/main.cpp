#include "main.h"

// define tasks

void test_bench_task(test_bench_def* test_bench, motor_control_def* motor_control_dmc_q90,motor_control_def* motor_control_kelly_pmac,const struct measuring_cycle_def* table_ptr, size_t table_size) {
  //test_bench_task to set setpoint values for the controllers and handle the measuring cycles when testbench is in auto mode
  DEBUG_PRINT(">fcn_test_bench_task:"); DEBUG_PRINTLN(1); //debug print 1:start task 0:stop task
  if (millis()-last_time_test_bench_task>MIN_TIME_BETWEEN_TEST_BENCH_TASK_EXEC){ //minimum time  between exec is set to save cpu capacity for the control tasks
    // test_bench_task
    test_bench->time = millis()/1000; // set current time

    if (test_bench->mode) { // mode=1 automatic; mode=0 manual
      if(test_bench->start) { // start measuring cycle
        test_bench->measuring_cycle = 1; // acitvate measuring cycle
        test_bench->measuring_cycle_start_time = millis()/1000; // set start time
        test_bench->start = 0; // reset start variable
      }  
      if (test_bench->measuring_cycle){ //if condition to go to pre def meas cycle reading 
        const struct measuring_cycle_def* closest_entry = NULL;  
        // Iterate through the table using the provided pointer
        size_t last_entry = 0;
        
        for (size_t i = 0; i < table_size; ++i) {
          const struct measuring_cycle_def* entry_ptr = table_ptr + i;
          // Check if the entry's time has already passed
          if (entry_ptr->time <= (test_bench->time-test_bench->measuring_cycle_start_time)) {
            // Check if the current entry has a smaller time than the previous closest entry
            if (closest_entry == NULL || entry_ptr->time > closest_entry->time) {
              closest_entry = entry_ptr;
              last_entry = i;
            }
          }
        }  
        if (closest_entry != NULL && last_entry != table_size-1) {
          // write the values of the closest entry to the current time
          motor_control_dmc_q90->speed_setpoint = double(closest_entry->rpm);
          motor_control_kelly_pmac->speed_setpoint = double(closest_entry->rpm);
          motor_control_dmc_q90->torque_setpoint = -1*double(closest_entry->torque); // to brake torque at dmc must be negative
          motor_control_kelly_pmac->torque_setpoint = double(closest_entry->torque); // to brake torque at kelly must be positive
          motor_control_dmc_q90->exication_current_setpoint = double(closest_entry->exitacion_current);
        } 
        DEBUG_PRINT(">last_entry:");DEBUG_PRINTLN(last_entry);
        if (last_entry+2 == table_size){
          // No matching entry found, set measuring cycle to 0
          test_bench->measuring_cycle = 0;
          test_bench->stop = 1;
        }
      }  
      if(test_bench->stop){ // condition to stop meassuring cycle setting all PID setpoints to 0
        test_bench->stop = 0;
        test_bench->measuring_cycle = 0;
        motor_control_dmc_q90->speed_setpoint = 0;
        motor_control_kelly_pmac->speed_setpoint = 0;
        motor_control_dmc_q90->torque_setpoint = 0;
        motor_control_kelly_pmac->torque_setpoint = 0;
        motor_control_dmc_q90->exication_current_setpoint = 0;
      }
    }  
    else { // manual mode
      // read excitation_current_poti
      motor_control_dmc_q90->excitation_current_poti_sensor = 100 - round(analogRead(EXCITATION_CURRENT_POTI_Q90_PIN)/1024.0*100.0);
      //read throttle_poti_dmc_q90
      motor_control_dmc_q90->throttle_poti_sensor = 100 - round(analogRead(POTI_THROTTLE_DMC_PIN)/1024.0*100.0); // 0...100
      //read break_poti_dmc_q90
      motor_control_dmc_q90->brake_poti_sensor = 100 - round(analogRead(POTI_BRAKE_DMC_PIN)/1024.0*100.0); // 0...100
      //read throttle_poti_kelly_pmac
      motor_control_kelly_pmac->throttle_poti_sensor = 100 - round(analogRead(POTI_THROTTLE_KELLY_PIN)/1024.0*100.0); // 0...100
      //read brake_poti_kelly_pmac
      motor_control_kelly_pmac->brake_poti_sensor = 100 - round(analogRead(POTI_BRAKE_KELLY_PIN)/1024.0*100.0); // 0...100

      // calculate Setpoints for PID-Controllers
      motor_control_dmc_q90->speed_setpoint = (motor_control_dmc_q90->throttle_poti_sensor-motor_control_dmc_q90->brake_poti_sensor)/100.0*motor_control_dmc_q90->speed_max;
      motor_control_dmc_q90->torque_setpoint = (motor_control_dmc_q90->throttle_poti_sensor-motor_control_dmc_q90->brake_poti_sensor)/100.0*motor_control_dmc_q90->torque_max;
      motor_control_dmc_q90->exication_current_setpoint = motor_control_dmc_q90->excitation_current_poti_sensor/100.0*motor_control_dmc_q90->excitation_current_max;
      motor_control_kelly_pmac->speed_setpoint = (motor_control_kelly_pmac->throttle_poti_sensor-motor_control_kelly_pmac->brake_poti_sensor)/100.0*motor_control_kelly_pmac->speed_max;
      motor_control_kelly_pmac->torque_setpoint = -1*(motor_control_kelly_pmac->throttle_poti_sensor-motor_control_kelly_pmac->brake_poti_sensor)/100.0*motor_control_kelly_pmac->torque_max; // to brake torque at kelly must be positive
    }
    last_time_test_bench_task = millis();  
  }  
  DEBUG_PRINT(">fcn_test_bench_task:"); DEBUG_PRINTLN(0); //debug print 1:start task 0:stop task
}

void vehicle_task(vehicle_def* vehicle) {
  // vehicle_task
  DEBUG_PRINT(">fcn_vehicle_task:"); DEBUG_PRINTLN(1); //debug print 1:start task 0:stop task
  //read battery_voltage_pin
  vehicle->battery_voltage = adc_vehicle_dmc_q90.readADC(BATTERY_VOLTAGE_SENSOR_PIN)*adc_vehicle_dmc_q90.toVoltage(1)*(R2_VOLTAGE_DIVIDER_U_BATT+R1_VOLTAGE_DIVIDER_U_BATT)/R2_VOLTAGE_DIVIDER_U_BATT;
  
  // read battery_current_pin
  vehicle->battery_current = CURRENT_DMC_ON +(battery_current_sensor_1.mA_DC(CURRENT_SENSOR_SAMPLES)+battery_current_sensor_2.mA_DC(CURRENT_SENSOR_SAMPLES)+battery_current_sensor_3.mA_DC(CURRENT_SENSOR_SAMPLES))/1000.0;
  DEBUG_PRINT(">fcn_vehicle_task:"); DEBUG_PRINTLN(0); //debug print 1:start task 0:stop task
}

void dmc_q90_control_task(motor_control_def* motor_control_dmc_q90, measurement_def* measurement, vehicle_def* vehicle) {
    // dmc_q90_control_task to calculate controller, set dac outputs and switches
    DEBUG_PRINT(">fcn_dmc_q90_control_task:"); DEBUG_PRINTLN(1); //debug print 1:start task 0:stop task
    // set speed & torque values using last value from measuring shaft 
    motor_control_dmc_q90->speed_sensor = measurement->speed_measuring_shaft_sensor; // get value from measuring shaft
    motor_control_dmc_q90->torque_sensor = measurement->torque_measuring_shaft_sensor; // get value from measuring shaft

    //read excitation_current
    double excitation_current = excitation_current_sensor.mA_DC(CURRENT_SENSOR_SAMPLES)/1000.0; // get excitation current
    if (excitation_current>0 && abs(excitation_current)>NOISE_ZERO_POINT_EXCITATION_CURRENT){ // get rid of noise around 0 A  
      motor_control_dmc_q90->excitation_current_sensor =  excitation_current; 
    } else {
      motor_control_dmc_q90->excitation_current_sensor = 0;
    }
    
    // pid excitation_current
    excitation_current_pid.Compute();
    // set pwm excitation_current
    int dc_pwm = round((constrain(motor_control_dmc_q90->excitation_current_output/motor_control_dmc_q90->excitation_current_max,0,1)*100.0)); // calc PWM Duty cycle
    analogWrite(PWM_EXCITATION_CURRENT_Q90_PIN,round(dc_pwm/100.0*255.0)); // frequ= 980 Hz Value = DC 0...255

    int percentage; 
    if (motor_control_dmc_q90->control_mode){// 0 = speed controlled , 1 = torque controlled
      dmc_q90_torque_pid.Compute(); // compute PID Output
      percentage = round(abs(motor_control_dmc_q90->torque_output)/motor_control_dmc_q90->torque_max*100.0); //calculate percentage of gas/brake applied here;

      // set dac gas/brake
      uint16_t output = round(percentage/100.0*4095.0); // calc output of dac, percentage 0..100
      if (motor_control_dmc_q90->speed_sensor>MIN_RPM_FOR_TORQUE){
        if (motor_control_dmc_q90->torque_output>=0) {
          dac_gas_dmc.setVoltage(abs(output),false);
          dac_bremse_dmc.setVoltage(0,false);
          motor_control_dmc_q90->state_foot_switch = 1; 
          motor_control_dmc_q90->state_brake_switch = 0;
        }
        else { // if torque_output <0
          dac_gas_dmc.setVoltage(0,false);
          dac_bremse_dmc.setVoltage(abs(output),false);
          motor_control_dmc_q90->state_foot_switch = 0;
          motor_control_dmc_q90->state_brake_switch = 1;
        }
      }  
    } 
    else {
      // pid motor speed
      dmc_q90_speed_pid.Compute(); // compute PID Output
      percentage = round(abs(motor_control_dmc_q90->speed_output)/motor_control_dmc_q90->speed_max*100.0); //calculate percentage of gas/brake applied here;

      // set dac gas/brake
      uint16_t output = round(percentage/100.0*4095.0); // calc output of dac, percentage 0..100
      if (motor_control_dmc_q90->speed_output>=0) {
        dac_gas_dmc.setVoltage(abs(output),false);
        dac_bremse_dmc.setVoltage(0,false);
        motor_control_dmc_q90->state_foot_switch = 1;
        motor_control_dmc_q90->state_brake_switch = 0;
      }
      else { // if speed_output <0
        dac_gas_dmc.setVoltage(0,false);
        dac_bremse_dmc.setVoltage(abs(output),false);
        motor_control_dmc_q90->state_foot_switch = 0;
        motor_control_dmc_q90->state_brake_switch = 1;
      } 
    }  

  // set driving status
  if (vehicle->battery_voltage > MIN_BATTERY_VOLTAGE){
    motor_control_dmc_q90->state_drive_switch = 1;
  } else {
    motor_control_dmc_q90->state_drive_switch = 0;
  }

    // set foot switch
    digitalWrite(FOOT_SWITCH_DMC_PIN,motor_control_dmc_q90->state_foot_switch);
    digitalWrite(BRAKE_SWITCH_DMC_PIN,motor_control_dmc_q90->state_brake_switch);
    digitalWrite(SWITCH_D_N_DMC_PIN,motor_control_dmc_q90->state_drive_switch);
    DEBUG_PRINT(">fcn_dmc_q90_control_task:"); DEBUG_PRINTLN(0); //debug print 1:start task 0:stop task
}

void kelly_pmac_control_task(motor_control_def* motor_control_kelly_pmac, measurement_def* measurement, vehicle_def* vehicle) {
  // kelly_pmac_control_task to calculate controller, set dac outputs and switches
    DEBUG_PRINT(">fcn_kelly_pmac_control_task:"); DEBUG_PRINTLN(1); //debug print 1:start task 0:stop task
    // set speed & torque values using last value from measuring shaft
    motor_control_kelly_pmac->speed_sensor = measurement->speed_measuring_shaft_sensor; // get value from measuring shaft
    motor_control_kelly_pmac->torque_sensor = measurement->torque_measuring_shaft_sensor; // get value from measuring shaft

    int percentage;
    if (motor_control_kelly_pmac->control_mode){// 0 = speed controlled , 1 = torque controlled
      kelly_pmac_torque_pid.Compute(); // compute PID Output
      percentage = round(abs(motor_control_kelly_pmac->torque_output)/motor_control_kelly_pmac->torque_max*100.0); //calculate percentage of gas/brake applied here;

      // set dac gas/brake
      uint16_t output = round(percentage/100.0*4095.0); //calc output of dac, percentage 0..100
      if (motor_control_kelly_pmac->speed_sensor>MIN_RPM_FOR_TORQUE){
        if (motor_control_kelly_pmac->torque_output>=0) {
          dac_gas_kelly.setVoltage(0,false);
          dac_bremse_kelly.setVoltage(abs(output),false);
          motor_control_kelly_pmac->state_foot_switch = 0;
          motor_control_kelly_pmac->state_brake_switch = 1;
        }
        else { // if torque_output <0
          dac_gas_kelly.setVoltage(abs(output),false);
          dac_bremse_kelly.setVoltage(0,false);
          motor_control_kelly_pmac->state_foot_switch = 1;
          motor_control_kelly_pmac->state_brake_switch = 0;
        }
      }
    } 
    else {
      // pid motor speed
      kelly_pmac_speed_pid.Compute(); // compute PID Output
      percentage = round(abs(motor_control_kelly_pmac->speed_output)/motor_control_kelly_pmac->speed_max*100.0); //calculate percentage of gas/brake applied here;

      // set dac gas/brake
      uint16_t output = round(percentage/100.0*4095.0); // calc output of dac, percentage 0..100
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

  // set driving status
  if (vehicle->battery_voltage > MIN_BATTERY_VOLTAGE){
    motor_control_kelly_pmac->state_drive_switch = 1;
  } else {
    motor_control_kelly_pmac->state_drive_switch = 0;
  }
    // set switches
    digitalWrite(FOOT_SWITCH_KELLY_PIN,motor_control_kelly_pmac->state_foot_switch);
    digitalWrite(BRAKE_SWITCH_KELLY_PIN,motor_control_kelly_pmac->state_brake_switch);
    digitalWrite(SWITCH_D_N_KELLY_PIN,motor_control_kelly_pmac->state_drive_switch);
    DEBUG_PRINT(">fcn_kelly_pmac_control_task:"); DEBUG_PRINTLN(0); //debug print 1:start task 0:stop task
}

void measurement_task(measurement_def* measurement) {
  // measurement_task: read in torque and speed values from the measuring shaft
  DEBUG_PRINT(">fcn_measurement_task:"); DEBUG_PRINTLN(1); //debug print 1:start task 0:stop task
  // read torque
  double torque = ((adc_measuring_shaft.readADC(TORQUE_MEASURING_SHAFT_PIN)*adc_measuring_shaft.toVoltage(1) - U_SUPPLY_MEASURING_CIRCUIT * (1+R3_LM358_OP_AMP/R1_LM358_OP_AMP) * R4_LM358_OP_AMP/(R4_LM358_OP_AMP+R2_LM358_OP_AMP))* (-R1_LM358_OP_AMP/R3_LM358_OP_AMP)) * deltaM - torque_offset; // in Nm
  if (abs(torque)>NOISE_ZERO_POINT_TORQUE){ //check abs value to filter out noise close to 0 Nm
    measurement->torque_measuring_shaft_sensor = torque;
  }else{
    measurement->torque_measuring_shaft_sensor = 0;
  }
    // read speed
  double speed = (adc_measuring_shaft.readADC(SPEED_MEASURING_SHAFT_PIN)*adc_measuring_shaft.toVoltage(1)*((R1_VOLTAGE_DIVIDER_MEASURING_SHAFT+R2_VOLTAGE_DIVIDER_MEASURING_SHAFT)/R2_VOLTAGE_DIVIDER_MEASURING_SHAFT)) * SPEED_MODE_MEASURING_SHAFT - speed_offset; //in rpm 
  if (speed>0 && abs(speed)>NOISE_ZERO_POINT_SPEED){ //check abs value to filter out noise close to 0 rpm
    measurement->speed_measuring_shaft_sensor = speed;
  } else {
    measurement->speed_measuring_shaft_sensor = 0; // since the motors are always turning in the same direction the speed can`t be negative, so it must be an error close to 0 rpm
  }
  DEBUG_PRINT(">fcn_measurement_task:"); DEBUG_PRINTLN(0); //debug print 1:start task 0:stop task
}

void screen_task(motor_control_def* motor_control_dmc_q90,motor_control_def* motor_control_kelly_pmac ,vehicle_def* vehicle,measurement_def* measurement,test_bench_def* test_bench) {
  // function purpose: updated screen values during loop()
  DEBUG_PRINT(">fcn_screen_task:"); DEBUG_PRINTLN(1); //debug print 1:start task 0:stop task
  if (millis()-last_time_screen_task>MIN_TIME_BETWEEN_SCREEN_TASK_EXEC){ //minimum time  between exec is set to save cpu capacity for the control tasks
      // screen_task
      // Display:
      // q90 Testbench        
      // Mode = auto/manual
      // Start/Restart Measuring Cycle = activated/deactivated
      // Stop Measuring Cycle = activated/deactivated
      // Measuring Cycle = aktiv/ inaktiv
      // Controll Mode DMC_q90 = Torque/Speed
      // Cotroll Modus KELLY_PMAC = Torque/Speed
      // Excitation Current = A
      // Speed = rpm
      // Torque = N
      // electrical Power = W
      // mechanical Power = W

    tft.setTextSize(1);
    tft.setCursor(302,26);   tft.print(test_bench->mode); 
    tft.setCursor(302,34);   tft.print(test_bench->start);
    tft.setCursor(302,42);   tft.print(test_bench->stop);
    tft.setCursor(302,50);   tft.print(test_bench->measuring_cycle); 
    tft.setCursor(302,58);   tft.print(motor_control_dmc_q90->control_mode);
    tft.setCursor(302,66);   tft.print(motor_control_kelly_pmac->control_mode);
    tft.setCursor(158,82);   tft.print(motor_control_dmc_q90->excitation_current_sensor,2); tft.print("  ");
    tft.setCursor(158,98);   tft.print(vehicle->battery_current,2); tft.print("  ");
    tft.setCursor(158,106);   tft.print(vehicle->battery_voltage,2);
    tft.setCursor(86,122);   tft.print(measurement->speed_measuring_shaft_sensor,2); tft.print("   ");
    tft.setCursor(86,130);   tft.print(measurement->torque_measuring_shaft_sensor,2); tft.print("   ");
    tft.setCursor(206,146);   tft.print((vehicle->battery_voltage*vehicle->battery_current),2); tft.print("  ");
    tft.setCursor(206,154);   tft.print(((measurement->speed_measuring_shaft_sensor*measurement->torque_measuring_shaft_sensor*2*PI)/60),2); tft.print("  ");
  last_time_screen_task = millis();
  }  
  DEBUG_PRINT(">fcn_screen_task:"); DEBUG_PRINTLN(0); //debug print 1:start task 0:stop task
}

void touch_task(test_bench_def* test_bench){
  // // function purpose: check if a touch button is being pressed and set the values in testbench struct
  DEBUG_PRINT(">fcn_touch_task:"); DEBUG_PRINTLN(1); //debug print 1:start task 0:stop task
  if (millis()-last_time_touch_task>MIN_TIME_BETWEEN_TOUCH_TASK_EXEC){ //minimum time  between exec is set to save cpu capacity for the control tasks
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
    last_time_touch_task = millis();
  }
  DEBUG_PRINT(">fcn_touch_task:"); DEBUG_PRINTLN(0); //debug print 1:start task 0:stop task
}

void send_data_task_loop_tp(test_bench_def* test_bench, vehicle_def* vehicle, motor_control_def* motor_control_dmc, motor_control_def* motor_control_kelly, measurement_def* measurement){
  // only send data releant for calculating performance and controller monitoring of the testbench to save time during the loop
  DEBUG_PRINT(">fcn_send_data_task_loop_tp:"); DEBUG_PRINTLN(1); //debug print 1:start task 0:stop task
  send_test_bench_data_loop_tp(test_bench);
  send_vehicle_data_loop_tp(vehicle);
  send_motor_control_data_dmc_loop_tp(motor_control_dmc);
  send_motor_control_data_kelly_loop_tp(motor_control_kelly);
  send_measurement_data_loop_tp(measurement);
  DEBUG_PRINT(">fcn_send_data_task_loop_tp:"); DEBUG_PRINTLN(0); //debug print 1:start task 0:stop task
}

void send_data_task_setup_tp(test_bench_def* test_bench, vehicle_def* vehicle, motor_control_def* motor_control_dmc, motor_control_def* motor_control_kelly, measurement_def* measurement){
  // function purpose: send all available data during setup up (to save all needed parameters for example controller settings for later examination)
  DEBUG_PRINT(">fcn_send_data_task_setup_tp:"); DEBUG_PRINTLN(1); //debug print 1:start task 0:stop task
  send_test_bench_data_setup_tp(test_bench);
  send_vehicle_data_setup_tp(vehicle);
  send_motor_control_data_dmc_setup_tp(motor_control_dmc);
  send_motor_control_data_kelly_setup_tp(motor_control_kelly);
  send_measurement_data_setup_tp(measurement);
  DEBUG_PRINT(">fcn_send_data_task_setup_tp:"); DEBUG_PRINTLN(0); //debug print 1:start task 0:stop task
}

void init_screen_touchscreen(){
  // function purpose: init and set display and touchscreen with values from main.h
  DEBUG_PRINT(">fcn_init_screen_touchscreen:"); DEBUG_PRINTLN(1); //debug print 1:start task 0:stop task
  // initialize screen
  delay(1000); // delay need for display controller to power up before beiing initialized
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

  // init static text for screen
  tft.setCursor(2, 2);
  tft.setTextSize(3);
  tft.setTextColor(ILI9341_WHITE,ILI9341_BLACK);
  tft.println(F("AG48V Test Bench"));
  tft.setTextSize(1);
  tft.println(F("Mode (0 = manual, 1 = auto)                      : ")); 
  tft.println(F("Start Measuring Cycle (0 = no, 1 = yes)          : ")); 
  tft.println(F("Stop Measuring Cycle (0 = no, 1 = yes)           : "));
  tft.println(F("Measuring Cycle (0 = inactive, 1 = active)       : "));
  tft.println(F("Controll Mode DMC_q90 (0 = speed, 1 = torque)    : ")); 
  tft.println(F("Controll Mode KELLY_PMAC (0 = speed, 1 = torque) : "));
  tft.println();
  tft.println(F("Excitation Current (A)   : "));
  tft.println();
  tft.println(F("Battery(DMC) Current (A) : "));
  tft.println(F("Battery(DMC) Voltage (V) : ")); 
  tft.println();
  tft.println(F("Speed (rpm)  : "));
  tft.println(F("Torque (Nm)  : "));
  tft.println();
  tft.println(F("Electrical Power DMC_q90 (W)     : "));
  tft.println(F("Mechanical Power DMC_q90 (W)     : "));
  DEBUG_PRINT(">fcn_init_screen_touchscreen:"); DEBUG_PRINTLN(0); //debug print 1:start task 0:stop task
}

void init_dacs(){
  // function purpose: init and set dacs with values from main.h using warning msg in case of failed setup
  DEBUG_PRINT(">fcn_init_dacs:"); DEBUG_PRINTLN(1); //debug print 1:start task 0:stop task
  // initialize digital analog converters

  int retries = 0;

  while (retries < MAX_RETRIES && !dac_gas_dmc.begin(ADRESS_DAC_gas_dmc)) {
    Serial.println("Failed to initialize dac_gas_dmc. Retrying...");
    retries++;
    delay(DELAY_TIME_INIT_RETRY);
  }

  if (retries == MAX_RETRIES) {
    Serial.println("Failed to initialize dac_gas_dmc after multiple attempts.");
    while(1);
  } else {
    Serial.println("dac_gas_dmc initialized successfully.");
    // Proceed with the rest of the program
  }

  retries = 0;

  while (retries < MAX_RETRIES && !dac_bremse_dmc.begin(ADRESS_DAC_bremse_dmc)) {
    Serial.println("Failed to initialize dac_bremse_dmc. Retrying...");
    retries++;
    delay(DELAY_TIME_INIT_RETRY);
  }

  if (retries == MAX_RETRIES) {
    Serial.println("Failed to initialize dac_bremse_dmc after multiple attempts.");
    while(1);
  } else {
    Serial.println("dac_bremse_dmc initialized successfully.");
    // Proceed with the rest of the program
  }

  retries = 0;
  
  while (retries < MAX_RETRIES && !dac_gas_kelly.begin(ADRESS_DAC_gas_kelly)) {
    Serial.println("Failed to initialize dac_gas_kelly. Retrying...");
    retries++;
    delay(DELAY_TIME_INIT_RETRY);
  }

  if (retries == MAX_RETRIES) {
    Serial.println("Failed to initialize dac_gas_kelly after multiple attempts.");
    while(1);
  } else {
    Serial.println("dac_gas_kelly initialized successfully.");
    // Proceed with the rest of the program
  }

  retries = 0;

  while (retries < MAX_RETRIES && !dac_bremse_kelly.begin(ADRESS_DAC_bremse_kelly)) {
    Serial.println("Failed to initialize dac_bremse_kelly. Retrying...");
    retries++;
    delay(DELAY_TIME_INIT_RETRY);
  }

  if (retries == MAX_RETRIES) {
    Serial.println("Failed to initialize dac_bremse_kelly after multiple attempts.");
    while(1);
  } else {
    Serial.println("dac_bremse_kelly initialized successfully.");
    // Proceed with the rest of the program
  }
  

  dac_gas_dmc.setVoltage(0,true);
  dac_bremse_dmc.setVoltage(0,true);
  dac_gas_kelly.setVoltage(0,true);
  dac_bremse_kelly.setVoltage(0,true);
  DEBUG_PRINT(">fcn_init_dacs:"); DEBUG_PRINTLN(0); //debug print 1:start task 0:stop task
}

void init_input_output_pins(){
  // function purpose: init and set input and output pins with values from main.h
  DEBUG_PRINT(">fcn_init_input_output_pins:"); DEBUG_PRINTLN(1); //debug print 1:start task 0:stop task
  // initialze analog input pins
  pinMode(EXCITATION_CURRENT_POTI_Q90_PIN,INPUT);
  pinMode(POTI_THROTTLE_DMC_PIN,INPUT);
  pinMode(POTI_BRAKE_DMC_PIN,INPUT);

  // initialize digital output pins
  pinMode(PWM_EXCITATION_CURRENT_Q90_PIN,OUTPUT);
  digitalWrite(PWM_EXCITATION_CURRENT_Q90_PIN, LOW); 
  
  pinMode(FOOT_SWITCH_DMC_PIN,OUTPUT);
  digitalWrite(FOOT_SWITCH_DMC_PIN, LOW);  

  pinMode(BRAKE_SWITCH_DMC_PIN,OUTPUT);
  digitalWrite(BRAKE_SWITCH_DMC_PIN, LOW);  

  pinMode(FOOT_SWITCH_KELLY_PIN,OUTPUT);
  digitalWrite(FOOT_SWITCH_KELLY_PIN, LOW); 
   
  pinMode(BRAKE_SWITCH_KELLY_PIN,OUTPUT);
  digitalWrite(BRAKE_SWITCH_KELLY_PIN, LOW); 

  pinMode(SWITCH_D_N_DMC_PIN,OUTPUT);   // set motors from Neutral to drive
  pinMode(SWITCH_D_N_KELLY_PIN,OUTPUT);
  digitalWrite(SWITCH_D_N_DMC_PIN,LOW);
  digitalWrite(SWITCH_D_N_KELLY_PIN,LOW);
  DEBUG_PRINT(">fcn_init_input_output_pins:"); DEBUG_PRINTLN(0); //debug print 1:start task 0:stop task
}

void init_adcs(){
  // function purpose: init and set adcs with values from main.h using warning msg in case of failed setup
  DEBUG_PRINT(">fcn_init_adcs:"); DEBUG_PRINTLN(1); //debug print 1:start task 0:stop task
  // initialize analog digital converters
  int retries = 0;
  while (retries < MAX_RETRIES && !adc_measuring_dmc_current.begin()) {
    Serial.println("Failed to initialize adc_measuring_dmc_current. Retrying...");
    retries++;
    delay(DELAY_TIME_INIT_RETRY);
  }

  if (retries == MAX_RETRIES) {
    Serial.println("Failed to initialize adc_measuring_dmc_current after multiple attempts.");
    while(1);
  } else {
    Serial.println("adc_measuring_dmc_current initialized successfully.");
    // Proceed with the rest of the program
  }
    adc_vehicle_dmc_q90.setGain(0);
  
  retries = 0; 
  while (retries < MAX_RETRIES && !adc_measuring_dmc_current.begin()) {
    Serial.println("Failed to initialize adc_measuring_dmc_current. Retrying...");
    retries++;
    delay(DELAY_TIME_INIT_RETRY);
  }

  if (retries == MAX_RETRIES) {
    Serial.println("Failed to initialize adc_measuring_dmc_current after multiple attempts.");
    while(1);
  } else {
    Serial.println("adc_measuring_dmc_current initialized successfully.");
    // Proceed with the rest of the program
  }
  adc_measuring_shaft.setGain(0);

  retries = 0;   
  while (retries < MAX_RETRIES && !adc_measuring_dmc_current.begin()) {
    Serial.println("Failed to initialize adc_measuring_dmc_current. Retrying...");
    retries++;
    delay(DELAY_TIME_INIT_RETRY);
  }

  if (retries == MAX_RETRIES) {
    Serial.println("Failed to initialize adc_measuring_dmc_current after multiple attempts.");
    while(1);
  } else {
    Serial.println("adc_measuring_dmc_current initialized successfully.");
    // Proceed with the rest of the program
  }

  adc_measuring_dmc_current.setGain(0);

  DEBUG_PRINT(">fcn_init_adcs:"); DEBUG_PRINTLN(0); //debug print 1:start task 0:stop task
}

void init_measuring_shaft(){
   // function purpose: init and set measuring shaft with values from main.h
  DEBUG_PRINT(">fcn_init_measuring_shaft:"); DEBUG_PRINTLN(1); //debug print 1:start task 0:stop task
  //set torque and speed offset, test bench must be standing still with no torque applied
  torque_offset = ((adc_measuring_shaft.readADC(TORQUE_MEASURING_SHAFT_PIN)*adc_measuring_shaft.toVoltage(1) - U_SUPPLY_MEASURING_CIRCUIT * (1+R3_LM358_OP_AMP/R1_LM358_OP_AMP) * R4_LM358_OP_AMP/(R4_LM358_OP_AMP+R2_LM358_OP_AMP))* (-R1_LM358_OP_AMP/R3_LM358_OP_AMP)) * deltaM;
  speed_offset = (adc_measuring_shaft.readADC(SPEED_MEASURING_SHAFT_PIN)*adc_measuring_shaft.toVoltage(1)*((R1_VOLTAGE_DIVIDER_MEASURING_SHAFT+R2_VOLTAGE_DIVIDER_MEASURING_SHAFT)/R2_VOLTAGE_DIVIDER_MEASURING_SHAFT)) * SPEED_MODE_MEASURING_SHAFT;
  DEBUG_PRINT(">fcn_init_measuring_shaft:"); DEBUG_PRINTLN(0); //debug print 1:start task 0:stop task
}

void init_current_sensors(){
   // function purpose: init and set current sensors with values from main.h
  DEBUG_PRINT(">fcn_init_current_sensors:"); DEBUG_PRINTLN(1); //debug print 1:start task 0:stop task
  // initialize current sensors
  battery_current_sensor_1.setADC(read_adc_battery_current_sensor_1,V_CC_CURRENT_SENSOR, ADS115_RESOLUTION);
  battery_current_sensor_1.autoMidPoint(); 
  battery_current_sensor_2.setADC(read_adc_battery_current_sensor_2,V_CC_CURRENT_SENSOR, ADS115_RESOLUTION);
  battery_current_sensor_2.autoMidPoint(); 
  battery_current_sensor_3.setADC(read_adc_battery_current_sensor_3,V_CC_CURRENT_SENSOR, ADS115_RESOLUTION);
  battery_current_sensor_3.autoMidPoint(); 
  excitation_current_sensor.setADC(read_adc_excitation_current_sensor,V_CC_CURRENT_SENSOR, ADS115_RESOLUTION);
  excitation_current_sensor.autoMidPoint();  
  
  DEBUG_PRINT(">fcn_init_current_sensors:"); DEBUG_PRINTLN(0); //debug print 1:start task 0:stop task 
}

void init_controllers(){
  // function purpose: init and set controllers with values from main.h
  DEBUG_PRINT(">fcn_init_controllers:"); DEBUG_PRINTLN(1); //debug print 1:start task 0:stop task
  //set motor control mode
  motor_control_dmc_q90.control_mode = CONTROL_MODE_DMC_Q90; // 0 = speed controlled , 1 = torque controlled
  motor_control_kelly_pmac.control_mode = CONTROL_MODE_KELLY_PMAC; // 0 = speed controlled , 1 = torque controlled

  //set max torque, speed, excitation current DMC_q90
  motor_control_dmc_q90.excitation_current_max = EXCITATION_CURRENT_MAX;
  motor_control_dmc_q90.torque_max = TORQUE_MAX; 
  motor_control_dmc_q90.speed_max = SPEED_MAX;

  // set max torque, speed kelly_pmac
  motor_control_kelly_pmac.torque_max = TORQUE_MAX; 
  motor_control_kelly_pmac.speed_max = SPEED_MAX;

  // set PID Parameter DMC_q90
  motor_control_dmc_q90.kp_speed = DMC_Q90_KP_SPEED;
  motor_control_dmc_q90.ki_speed = DMC_Q90_KI_SPEED;
  motor_control_dmc_q90.kd_speed = DMC_Q90_KD_SPEED;

  motor_control_dmc_q90.kp_torque = DMC_Q90_KP_TORQUE;
  motor_control_dmc_q90.ki_torque = DMC_Q90_KI_TORQUE;
  motor_control_dmc_q90.kd_torque = DMC_Q90_KD_TORQUE;

  motor_control_dmc_q90.kp_excitation_current = DMC_Q90_KP_EXCITATION_CURRENT;
  motor_control_dmc_q90.ki_excitation_current = DMC_Q90_KI_EXCITATION_CURRENT;
  motor_control_dmc_q90.kd_excitation_current = DMC_Q90_KD_EXCITATION_CURRENT;

  // set PID Parameter Kelly_PMAC
  motor_control_kelly_pmac.kp_speed = KELLY_PMAC_KP_SPEED;
  motor_control_kelly_pmac.ki_speed = KELLY_PMAC_KI_SPEED;
  motor_control_kelly_pmac.kd_speed = KELLY_PMAC_KD_SPEED;

  motor_control_kelly_pmac.kp_torque = KELLY_PMAC_KP_TORQUE;
  motor_control_kelly_pmac.ki_torque = KELLY_PMAC_KI_TORQUE;
  motor_control_kelly_pmac.kd_torque = KELLY_PMAC_KD_TORQUE;

  // initialize pid controllers
  if (motor_control_dmc_q90.control_mode){ // 0 = speed controlled , 1 = torque controlled    
    dmc_q90_torque_pid.SetOutputLimits(-double(motor_control_dmc_q90.torque_max),0);
    dmc_q90_torque_pid.SetMode(AUTOMATIC);
    dmc_q90_torque_pid.SetTunings(motor_control_dmc_q90.kp_torque, motor_control_dmc_q90.ki_torque, motor_control_dmc_q90.kd_torque);
  }else{
    dmc_q90_speed_pid.SetOutputLimits(0, double(motor_control_dmc_q90.speed_max));
    dmc_q90_speed_pid.SetMode(AUTOMATIC);
    dmc_q90_speed_pid.SetTunings(motor_control_dmc_q90.kp_speed, motor_control_dmc_q90.ki_speed, motor_control_dmc_q90.kd_speed);
  } 
  excitation_current_pid.SetOutputLimits(0, double(motor_control_dmc_q90.excitation_current_max));
  excitation_current_pid.SetMode(AUTOMATIC);
  excitation_current_pid.SetTunings(motor_control_dmc_q90.kp_excitation_current, motor_control_dmc_q90.ki_excitation_current, motor_control_dmc_q90.kd_excitation_current);

  if (motor_control_kelly_pmac.control_mode){ // 0 = speed controlled , 1 = torque controlled
    kelly_pmac_torque_pid.SetOutputLimits(0, double(motor_control_kelly_pmac.torque_max));
    kelly_pmac_torque_pid.SetMode(AUTOMATIC);
    kelly_pmac_torque_pid.SetTunings(motor_control_kelly_pmac.kp_torque, motor_control_kelly_pmac.ki_torque, motor_control_kelly_pmac.kd_torque);
  }else{
    kelly_pmac_speed_pid.SetOutputLimits(0, double(motor_control_kelly_pmac.speed_max));
    kelly_pmac_speed_pid.SetMode(AUTOMATIC);
    kelly_pmac_speed_pid.SetTunings(motor_control_kelly_pmac.kp_speed, motor_control_kelly_pmac.ki_speed, motor_control_kelly_pmac.kd_speed);
  }
  DEBUG_PRINT(">fcn_init_controllers:"); DEBUG_PRINTLN(0); //debug print 1:start task 0:stop task
}

// setup function
void setup() {
  Serial.begin(SERIAL_BAUD_RATE,SERIAL_8N1); // initialize serial communication
  // execute uC Setup functions
  init_screen_touchscreen();
  init_dacs();
  init_input_output_pins();
  init_adcs();
  init_measuring_shaft();
  init_current_sensors();
  init_controllers();
  send_data_task_setup_tp(&q90_test_bench,&power_supply,&motor_control_dmc_q90,&motor_control_kelly_pmac,&measuring_shaft);
}

// loop function
void loop() {
  #ifdef LOOP_TIME_MEASUREMENT // activate/ deactivate in main.h
    loop_time = millis(); //needed for loop time measurment
  #endif
  
  //tasks that have a max frequency and are not crucial for the controllers (set frequ in main.h)
  test_bench_task(&q90_test_bench,&motor_control_dmc_q90,&motor_control_kelly_pmac, measuring_cycle_table, MEASURING_CYCLE_TABLE_SIZE);
  touch_task(&q90_test_bench);
  screen_task(&motor_control_dmc_q90,&motor_control_kelly_pmac,&power_supply,&measuring_shaft,&q90_test_bench);
  
  // tasks that are executed each loop for controller performance
  measurement_task(&measuring_shaft);
  dmc_q90_control_task(&motor_control_dmc_q90,&measuring_shaft,&power_supply);
  kelly_pmac_control_task(&motor_control_kelly_pmac,&measuring_shaft,&power_supply);
  vehicle_task(&power_supply);
  send_data_task_loop_tp(&q90_test_bench,&power_supply,&motor_control_dmc_q90,&motor_control_kelly_pmac,&measuring_shaft);
  
  #ifdef LOOP_TIME_MEASUREMENT
    Serial.print(">loop_time_ms:");Serial.println(millis()-loop_time);
  #endif
}
  