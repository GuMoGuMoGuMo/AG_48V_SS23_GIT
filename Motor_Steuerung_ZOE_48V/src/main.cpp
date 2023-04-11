#include "main.h"

// Setup Funktionen
void init_potentiometer(){
  pinMode(U_POTI,INPUT); // initialize iputs/outputs
}

void init_erregerstrom_pwm(){
    pinMode(PWM_ERREGUNG,OUTPUT); // initialize iputs/outputs
    digitalWrite(PWM_ERREGUNG, LOW);  // PWM_ERREGUNG Pin ausschalten
}

void init_erregerstrom_sensor(){
    pinMode(I_ERREGUNG_SENS,INPUT); // initialize iputs/outputs
    digitalWrite(PWM_ERREGUNG, LOW);  // PWM_ERREGUNG Pin ausschalten
    ACS.autoMidPoint(); // Strom Sensor Nullpunkt setzten
}

void init_erregerstrom_pid(){
  //turn the PID on
  erregerstrom_pid.SetOutputLimits(0, I_Erregung_MAX);
  erregerstrom_pid.SetMode(AUTOMATIC);
}

void init_messung_u_batt_traktion(){
    pinMode(U_BATT_TRAKTION,INPUT);
    u_batt_traktion = analogRead(U_BATT_TRAKTION); // gemessen über Spannungsteiler
    u_batt_traktion = u_batt_traktion/255.0*5.0; // umrechnung analoger Wert in V über Spannungsteiler
    u_batt_traktion = u_batt_traktion*R1_span_teil/(R1_span_teil+R2_span_teil); // // Spanung Traktions Batterie berechnen
    // 
}

void init_dac_(Adafruit_MCP4725& DAC, int adresse){
  DAC.begin(adresse);
  DAC.setVoltage(0,false);
}


// Loop Funktionen
void loop_erregerstrom_sollwert(){
  av_R_poti = analogRead(U_POTI); // responds with value between 0..1023 
  r_poti = av_R_poti/1024.0*R_POT100;
  DEBUG_PRINT(">R_Poti: ");DEBUG_PRINT(r_poti);DEBUG_PRINTLN(" Ohm"); // calculates R
  erregerstrom_soll = av_R_poti/1024.0*I_Erregung_MAX;
  
  //erregerstrom_soll = 0.5*sin(millis()/1000.0)+0.5; //A
  
  DEBUG_PRINT(">Erregerstrom_soll: ");DEBUG_PRINT(erregerstrom_soll);DEBUG_PRINTLN(" A"); // debug print sollwert erregerstrom
}

void loop_erregerstrom_sensor(){
  int mA = ACS.mA_DC(); // Messung Erregerstrom
  DEBUG_PRINT(">Strom: ");DEBUG_PRINT(mA/1000.0);DEBUG_PRINTLN(" A"); //Debug Print Erregerstrom
  
  erreger_strom_mov_avg.addValue(mA/1000.0); // mov avg filter
  DEBUG_PRINT(">Erregerstrom_Sensor_mov_AVG: ");DEBUG_PRINT(erreger_strom_mov_avg.getAverage());DEBUG_PRINTLN(" A"); // debug print
  
  
  erreger_strom_low_pass += weight * (mA - erreger_strom_low_pass);  // low pass filtering
  DEBUG_PRINT(">Erregerstrom_Sensor_lowpass: ");DEBUG_PRINT(erreger_strom_low_pass/1000.0);DEBUG_PRINTLN(" A"); // debug print

  float value_we_avg_Filter1 = we_avg_Filter1.filter(mA); // exp mov avg filter
  DEBUG_PRINT(">Erregerstrom_Sensor_we_mvavg1: ");DEBUG_PRINT(value_we_avg_Filter1/1000.0);DEBUG_PRINTLN(" A"); // debug print

  float value_we_avg_Filter2 = we_avg_Filter2.filter(mA); // exp mov avg filter
  DEBUG_PRINT(">Erregerstrom_Sensor_we_mvavg2: ");DEBUG_PRINT(value_we_avg_Filter2/1000.0);DEBUG_PRINTLN(" A"); // debug print

  erregerstrom_sensor = erreger_strom_mov_avg.getAverage(); // Ist Wert Erregerstrom
}

void loop_erregerstrom_pid(){
  erregerstrom_pid.Compute();
  DEBUG_PRINT(">Erregerstrom_stell: ");DEBUG_PRINT(erregerstrom_stell);DEBUG_PRINTLN(" A");
}

void loop_erregerstrom_pwm(){   
  //dc_pwm = constrain(erregerstrom_stell/I_Erregung_MAX,0,1);
  dc_pwm = 0.1;
  analogWrite(PWM_ERREGUNG,dc_pwm*255.0); // frequ= 980 Hz Value = DC 0...255
  DEBUG_PRINT(">DC_PWM: ");DEBUG_PRINT(dc_pwm);DEBUG_PRINTLN(" %");
}

void loop_dac(int prozent,Adafruit_MCP4725& DAC){ 
  uint16_t output = round(prozent/100.0*4096.0); // Prozent 0..100
  DAC.setVoltage(output,false);
}

// uC Funktionen
void setup(){
  Serial.begin(9600);
  init_dac(DAC1,adresse_dac1);
  //init_erregerstrom_pwm();
  //init_potentiometer();
  //init_erregerstrom_sensor();
  //init_erregerstrom_pid();

  //erreger_strom_mov_avg.clear();
  

  
}

void loop(){
  loop_dac(10,DAC1);
  //loop_erregerstrom_sollwert();
  //loop_erregerstrom_sensor();
  //loop_erregerstrom_pid();
  //loop_erregerstrom_pwm();
}