#include "main.h"



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  init_potentiometer();
  init_pwm_i_erregung();
  init_strom_sensor();
  init_erregerstrom_regelung();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  loop_potentiometer();
  loop_strom_sensor();
  loop_erregerstrom_regelung();
  loop_pwm_i_erregung();
}