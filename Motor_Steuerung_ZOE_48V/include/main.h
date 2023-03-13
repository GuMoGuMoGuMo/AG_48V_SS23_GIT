
// include
#include <Arduino.h>

// Pinning
#define PWM_ERREGUNG 13
#define U_I_ERREGUNG_SENS A0
#define U_POTI A1

// Globale Variablen
unsigned short av_R_poti;

float R_ROTOR = 8; //Ohm - zunächst als konstant angenommen, kann z.B. im Setup mit einem 100% DC vermessen werden
float L_ROTOR = 0.4; //H Messung von Herr Zirn 03.2022
float U_BATT_TRAKTION_48V = 48; //V
float I_Erregung_MAX = U_BATT_TRAKTION_48V/R_ROTOR; //A zunächst als konstant angenommen

unsigned short dc_pwm;

unsigned long last_time;
float regeldifferenz_alt;
float erregerstrom_sensor;
float erregerstrom_soll;
float erregerstrom_stell;
float integral_erregerstrom_regelung = 0;


// Konstanten
#define R_POT100 4700 // Ohm
#define VCC_STROM_SENSOR 5.00 // Volt
#define FAKTOR_STROM_SENSOR 0.02 // 20mV/A Umrechungsfaktor

#define Erregerstrom_Regelung_KP 50
#define Erregerstrom_Regelung_KI 10
#define Erregerstrom_Regelung_KD 0

// Debug Optionen

#define DEBUG_PRINTS

#ifdef DEBUG_PRINTS
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINTLN(x) Serial.println(x)
#else
  #define DEBUG_PRINTLN(x)
  #define DEBUG_PRINT(x) 
#endif

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

void init_erregerstrom_regelung(){
    last_time = micros();
}

// Loop Funktionen
void loop_potentiometer(){
  av_R_poti = analogRead(U_POTI); // responds with value between 0..1023 
  DEBUG_PRINT("R_Poti= ");DEBUG_PRINT(av_R_poti/1024.0*R_POT100);DEBUG_PRINTLN(" Ohm"); // calculates R
  erregerstrom_soll = av_R_poti/1024.0*I_Erregung_MAX;
}

void loop_pwm_i_erregung(){
    //dc_pwm = round(av_R_poti/1024.0*100); //calculates analog value to percent    
    dc_pwm = round(erregerstrom_stell/I_Erregung_MAX);
    analogWrite(PWM_ERREGUNG,dc_pwm*255.0/100); // frequ= 980 Hz Value = DC 0...255
    DEBUG_PRINT("DC_PWM= ");DEBUG_PRINT(dc_pwm);DEBUG_PRINTLN(" %");
}

void loop_strom_sensor(){
    float u_erregerstrom_sensor;
    u_erregerstrom_sensor = (5.0/1023.0)*analogRead(U_I_ERREGUNG_SENS); // Spannungssignal einlesen
    u_erregerstrom_sensor = u_erregerstrom_sensor - (VCC_STROM_SENSOR * 0.5) + 0.007 ;// 0.007 Wert um Spannug 0 zu setzen wenn I Errergung = 0 ist
    erregerstrom_sensor = u_erregerstrom_sensor/FAKTOR_STROM_SENSOR; // Umrechnung in Strom
    DEBUG_PRINT("Erregerstrom_Sensor: ");DEBUG_PRINT(erregerstrom_sensor);DEBUG_PRINTLN(" A");
}

void loop_erregerstrom_regelung(){
    float regelanteil_p;
    float regelanteil_i;
    float regelanteil_d;
    
    float fuehrungsgroesse = erregerstrom_soll;
    float regelgroesse = erregerstrom_sensor; 
    float stellgroesse = erregerstrom_stell;

    float regeldifferenz;
    float delta_regeldifferenz;
    
    float integral = integral_erregerstrom_regelung;
    float ableitung;
    
    unsigned long delta_t;

    delta_t = micros()-last_time;
    last_time = micros();
    
    regeldifferenz = fuehrungsgroesse - regelgroesse;
    
    delta_regeldifferenz = regeldifferenz - regeldifferenz_alt;
    regeldifferenz_alt = regeldifferenz;
    integral += regeldifferenz * delta_t;
    ableitung = delta_regeldifferenz / delta_t;

    regelanteil_p = Erregerstrom_Regelung_KP * regeldifferenz;
    regelanteil_i = Erregerstrom_Regelung_KI * integral;
    regelanteil_d = Erregerstrom_Regelung_KD * ableitung;
    
    stellgroesse = regelanteil_p + regelanteil_i + regelanteil_d;
    
    erregerstrom_stell = constrain(stellgroesse,0,I_Erregung_MAX);
    DEBUG_PRINT("Erregerstrom_Stell: ");DEBUG_PRINT(erregerstrom_stell);DEBUG_PRINTLN(" A");
}