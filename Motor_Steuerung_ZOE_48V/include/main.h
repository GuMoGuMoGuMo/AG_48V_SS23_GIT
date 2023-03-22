
// include
#include <Arduino.h>
#include "ACS712.h"
#include <PID_v1.h>
#include <movingAvg.h>
#include <Ewma.h>


// Pinning
#define PWM_ERREGUNG 13
#define U_I_ERREGUNG_SENS A0
#define U_POTI A1
#define U_BATT_TRAKTION A2

// Potentiometer
#define R_POT100 4700 // Ohm
unsigned short av_R_poti;
float r_poti;

// Motordaten
float R_ROTOR = 8;//8; //Ohm - zunächst als konstant angenommen, kann z.B. im Setup mit einem 100% DC vermessen werden
float L_ROTOR = 0.4; //H Messung von Herr Zirn 03.2022
float u_batt_traktion = 13; //V
float I_Erregung_MAX = u_batt_traktion/R_ROTOR; //A zunächst als konstant angenommen

// PWM Signal Erregerstrom
float dc_pwm;

// PID Erregerstrom
double Setpoint;
double Input;
double Output;
double Kp=6;
double Ki=2; 
double Kd=0.001;
PID erregerstrom_pid(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

float erregerstrom_stell,erregerstrom_sensor,erregerstrom_soll;

// Stromsensor
#define VCC_STROM_SENSOR 5.00 // Volt
#define FAKTOR_STROM_SENSOR 0.02 // 20mV/A Umrechungsfaktor
ACS712  ACS(A0, 5.0, 1023, 20);

float value_low_pass=0;


//average filter

RunningAverage erreger_strom_avg(10);

// Debug Optionen

#define DEBUG_PRINTS

#ifdef DEBUG_PRINTS
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINTLN(x) Serial.println(x)
#else
  #define DEBUG_PRINTLN(x)
  #define DEBUG_PRINT(x) 
#endif