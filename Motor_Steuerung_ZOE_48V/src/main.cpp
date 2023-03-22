#include "main.h"

// Setup Funktionen
void init_potentiometer(){
  pinMode(U_POTI,INPUT); // initialize iputs/outputs
}

void init_pwm_i_erregung(){
    pinMode(PWM_ERREGUNG,OUTPUT); // initialize iputs/outputs
}

void init_strom_sensor(){
    pinMode(U_I_ERREGUNG_SENS,INPUT); // initialize iputs/outputs
}

void init_messung_u_batt_traktion(){
    pinMode(U_BATT_TRAKTION,INPUT);
    u_batt_traktion = analogRead(U_BATT_TRAKTION); 
}


// Loop Funktionen
void loop_potentiometer(){
  av_R_poti = analogRead(U_POTI); // responds with value between 0..1023 
  r_poti = av_R_poti/1024.0*R_POT100;
  DEBUG_PRINT(">R_Poti: ");DEBUG_PRINT(r_poti);DEBUG_PRINTLN(" Ohm"); // calculates R
  erregerstrom_soll = av_R_poti/1024.0*I_Erregung_MAX;
  DEBUG_PRINT(">Erregerstrom_soll: ");DEBUG_PRINT(erregerstrom_soll);DEBUG_PRINTLN(" A"); // calculates R  
}

void loop_pwm_i_erregung(){   
    //dc_pwm = constrain(erregerstrom_stell/I_Erregung_MAX,0,1);
    dc_pwm = 0.1;
    analogWrite(PWM_ERREGUNG,dc_pwm*255.0); // frequ= 980 Hz Value = DC 0...255
    DEBUG_PRINT(">DC_PWM: ");DEBUG_PRINT(dc_pwm);DEBUG_PRINTLN(" %");
}

movingAvg strom_movingAvg(10);

Ewma we_avg_Filter1(0.2);   // Less smoothing - faster to detect changes, but more prone to noise
Ewma we_avg_Filter2(0.01);  // More smoothing - less prone to noise, but slower to detect changes

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  init_potentiometer();
  //init_strom_sensor();
  init_pwm_i_erregung();

  strom_movingAvg.begin();
  ACS.autoMidPoint();

  erreger_strom_avg.clear(); // explicitly start clean

  Input = 0;
  Setpoint = 0;

  //turn the PID on
  erregerstrom_pid.SetOutputLimits(0, I_Erregung_MAX);
  erregerstrom_pid.SetMode(AUTOMATIC);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  loop_potentiometer();
  //erregerstrom_soll = 0.5*sin(millis()/1000.0)+0.5; //A
  //DEBUG_PRINT(">Erregerstrom_soll: ");DEBUG_PRINT(erregerstrom_soll);DEBUG_PRINTLN(" A");

  int mA = ACS.mA_DC();
  DEBUG_PRINT(">Strom: ");DEBUG_PRINT(mA/1000.0);DEBUG_PRINTLN(" A");
  erreger_strom_avg.addValue(mA/1000.0);
  DEBUG_PRINT(">Erregerstrom_Sensor_mov_AVG: ");DEBUG_PRINT(erreger_strom_avg.getAverage());DEBUG_PRINTLN(" A");
  
  float weight = 0.2;
  value_low_pass += weight * (mA - value_low_pass);  // low pass filtering
  DEBUG_PRINT(">Erregerstrom_Sensor_lowpass: ");DEBUG_PRINT(value_low_pass/1000.0);DEBUG_PRINTLN(" A");

  float value_we_avg_Filter1 = we_avg_Filter1.filter(mA);
  DEBUG_PRINT(">Erregerstrom_Sensor_we_mvavg1: ");DEBUG_PRINT(value_we_avg_Filter1/1000.0);DEBUG_PRINTLN(" A");

  float value_we_avg_Filter2 = we_avg_Filter2.filter(mA);
  DEBUG_PRINT(">Erregerstrom_Sensor_we_mvavg2: ");DEBUG_PRINT(value_we_avg_Filter2/1000.0);DEBUG_PRINTLN(" A");

  Setpoint = erregerstrom_soll;
  Input = erreger_strom_avg.getAverage();
  erregerstrom_pid.Compute();
  erregerstrom_stell = Output;
  DEBUG_PRINT(">Erregerstrom_stell: ");DEBUG_PRINT(erregerstrom_stell);DEBUG_PRINTLN(" A");
  loop_pwm_i_erregung();
}