struct test_bench_def {  
  bool mode = false; // 1:automatik 0:manuell
  bool start = false; // 1: ja 0: nein
  uint16_t measuring_cycle_start_time = 0;
  uint16_t time;
  bool stop = true; // 1: ja 0: nein
  bool measuring_cycle = true; // 0: deactivated 1:activated
};

struct vehicle_def {
  double battery_voltage = 48;
  double battery_current = 15;
};

struct motor_control_def {
  bool control_mode = 0;  // 0 = speed controlled , 1 = torque controlled

  int excitation_current_max = 1;
  int torque_max = 2;
  int speed_max = 3;

  int throttle_poti_sensor = 0;

  int brake_poti_sensor = 0;

  int excitation_current_poti_sensor= 1;

  double speed_setpoint =10;
  double torque_setpoint=10;
  double speed_sensor=10;
  double torque_sensor=10;

  double speed_output=10;
  double torque_output=10;
  
  double excitation_current_sensor=10;
  double excitation_current_output=10;
  double exication_current_setpoint=10; 

  double kp_speed=10;
  double ki_speed=10;
  double kd_speed=10;

  double kp_torque=11;
  double ki_torque=11;
  double kd_torque=11;

  double kp_excitation_current=12;
  double ki_excitation_current=12;
  double kd_excitation_current=12;

  bool state_foot_switch=0; // 0: open 1:closed
  bool state_brake_switch=1; // 0: open 1:closed
};

struct measurement_def {
  double torque_measuring_shaft_sensor = 10;
  double speed_measuring_shaft_sensor = 20;
};


struct test_bench_def zoe_test_bench;
struct vehicle_def power_supply;
struct motor_control_def motor_control_dmc_zoe;
struct motor_control_def motor_control_kelly_pmac;
struct measurement_def measuring_shaft;


String data_string_test_bench (test_bench_def* test_bench){
    String test_bench_data = (String("tb ") + \
                test_bench->mode + " " + \
                test_bench->start + " " + \
                test_bench->stop + " " + \
                test_bench->measuring_cycle + " " + \
                test_bench->time + " " + \
                test_bench->measuring_cycle_start_time)+ " ";
  return test_bench_data;
}

String data_string_vehicle (vehicle_def* vehicle){
    String vehicle_data = (String("vh ") + \
                vehicle->battery_current + " " + \
                vehicle->battery_voltage)+ " " ;
  return vehicle_data;
}

String data_string_motor_control_dmc_zoe(motor_control_def* motor_control) {
    String motor_control_dmc_zoe_data = (String("dmc ") +
                 motor_control->control_mode + " " +
                 motor_control->excitation_current_max + " " +
                 motor_control->torque_max + " " +
                 motor_control->speed_max + " " +
                 motor_control->throttle_poti_sensor + " " +
                 motor_control->brake_poti_sensor + " " +
                 motor_control->excitation_current_poti_sensor + " " +
                 motor_control->speed_setpoint + " " +
                 motor_control->torque_setpoint + " " +
                 motor_control->speed_sensor + " " +
                 motor_control->torque_sensor + " " +
                 motor_control->speed_output + " " +
                 motor_control->torque_output + " " +
                 motor_control->excitation_current_sensor + " " +
                 motor_control->excitation_current_output + " " +
                 motor_control->exication_current_setpoint + " " +
                 motor_control->kp_speed + " " +
                 motor_control->ki_speed + " " +
                 motor_control->kd_speed + " " +
                 motor_control->kp_torque + " " +
                 motor_control->ki_torque + " " +
                 motor_control->kd_torque + " " +
                 motor_control->kp_excitation_current + " " +
                 motor_control->ki_excitation_current + " " +
                 motor_control->kd_excitation_current + " " +
                 motor_control->state_foot_switch + " " +
                 motor_control->state_brake_switch)+ " " ;
  return motor_control_dmc_zoe_data;
}

String data_string_motor_control_kelly_pmac (motor_control_def* motor_control){
    String motor_control_kelly_pmac_data = (String("kelly ") + \
                motor_control->control_mode + " " + \
                motor_control->excitation_current_max + " " + \
                motor_control->torque_max + " " + \
                motor_control->speed_max + " " + \
                motor_control->throttle_poti_sensor + " " + \
                motor_control->brake_poti_sensor + " " + \
                motor_control->excitation_current_poti_sensor + " " + \
                motor_control->speed_setpoint + " " + \
                motor_control->torque_setpoint + " " + \
                motor_control->speed_sensor + " " + \
                motor_control->torque_sensor + " " + \
                motor_control->speed_output + " " + \
                motor_control->torque_output + " " + \
                motor_control->excitation_current_sensor + " " + \
                motor_control->excitation_current_output + " " + \
                motor_control->exication_current_setpoint + " " + \
                motor_control->kp_speed + " " + \
                motor_control->ki_speed + " " + \
                motor_control->kd_speed + " " + \
                motor_control->kp_torque + " " + \
                motor_control->ki_torque + " " + \
                motor_control->kd_torque + " " + \
                motor_control->kp_excitation_current + " " + \
                motor_control->ki_excitation_current + " " + \
                motor_control->kd_excitation_current + " " + \
                motor_control->state_foot_switch + " " + \
                motor_control->state_brake_switch)+ " " ;
  return motor_control_kelly_pmac_data;
}

String data_string_measurement (measurement_def* measurement){
    String measurement_data = (String("msr ") + \
                measurement->torque_measuring_shaft_sensor + " " + \
                measurement->speed_measuring_shaft_sensor)+ " " ;
  return measurement_data;
}

void send_data_task(test_bench_def* test_bench, vehicle_def* vehicle, motor_control_def* motor_control_dmc_zoe, motor_control_def* motor_control_kelly_pmac, measurement_def* measurement){
  Serial.print(data_string_test_bench(test_bench) + data_string_vehicle(vehicle) + data_string_motor_control_dmc_zoe(motor_control_dmc_zoe) + data_string_motor_control_kelly_pmac(motor_control_kelly_pmac) + data_string_measurement(measurement));
  Serial.write(13);
  Serial.write(10);
}


// The setup routine runs once when you press reset:
void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  //Serial.println(String("Moin"));
}

// The loop routine runs over and over again forever:
void loop() {
  zoe_test_bench.time = millis();
  Serial.print("message_start: ");Serial.println(micros());
  send_data_task(&zoe_test_bench,&power_supply,&motor_control_dmc_zoe,&motor_control_kelly_pmac,&measuring_shaft);
  Serial.print("message_end: ");Serial.println(micros());

  delay(100);
}