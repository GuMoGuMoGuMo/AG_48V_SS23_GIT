
// include
#include <Arduino.h> // Arduino standard lib

// Pinning
#define PWM_ERREGUNG 13
#define I_ERREGUNG_SENS A0
#define U_POTI A1
#define U_BATT_TRAKTION A2

// Digital-Analog Converter
#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac1;
int adresse_dac1 = 0x60;

// Analog-Digital Converter ADS1115
#include <Adafruit_ADS1X15.h>
Adafruit_ADS1015 ads1;

// Potentiometer
#define R_POT100 4700 // Ohm
unsigned short av_R_poti;
float r_poti;

//Messschaltung
#define R1_span_teil 100 // Ohm
#define R2_span_teil 100 // Ohm

// Motordaten
float R_ROTOR = 8;//8; //Ohm - zunächst als konstant angenommen, kann z.B. im Setup mit einem 100% DC vermessen werden
float L_ROTOR = 0.4; //H Messung von Herr Zirn 03.2022
float u_batt_traktion = 13; //V
float I_Erregung_MAX = u_batt_traktion/R_ROTOR; //A zunächst als konstant angenommen

// PWM Signal Erregerstrom
float dc_pwm;

// PID Erregerstrom
#include <PID_v1.h> // PID Regler lib
double Kp_erregerstrom = 6;
double Ki_erregerstrom = 2; 
double Kd_erregerstrom = 0.001;
double erregerstrom_stell,erregerstrom_sensor,erregerstrom_soll;
PID erregerstrom_pid(&erregerstrom_sensor, &erregerstrom_stell, &erregerstrom_soll, Kp_erregerstrom, Ki_erregerstrom, Kd_erregerstrom, DIRECT); //init PID Objekt


// Stromsensor
#include <ACS712.h> // Stromsensor lib

ACS712  ACS(I_ERREGUNG_SENS, 5.0, 1023,66); // init Stomsensor Objekt: PIN, VCC, ADC Auflösung, 66mV/A

// Filter
#include <Ewma.h> // exp weighted moving avg filter liv
#include <RunningAverage.h> // moving avg filter lib

RunningAverage erreger_strom_mov_avg(10); // init moving average filter, 10 = Anzahl der Messungen für Filter
Ewma we_avg_Filter1(0.2);   // Less smoothing - faster to detect changes, but more prone to noise
Ewma we_avg_Filter2(0.01);  // More smoothing - less prone to noise, but slower to detect changes
float erreger_strom_low_pass=0; // init TP filter
float weight = 0.2; // Gewichtung TP filter


// Debug Optionen

#define DEBUG_PRINTS

#ifdef DEBUG_PRINTS
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINTLN(x) Serial.println(x)
#else
  #define DEBUG_PRINTLN(x)
  #define DEBUG_PRINT(x) 
#endif