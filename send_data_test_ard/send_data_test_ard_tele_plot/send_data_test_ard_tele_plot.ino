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
struct motor_control_def motor_control_dmc;
struct motor_control_def motor_control_kelly;
struct measurement_def measuring_shaft;


void send_test_bench_data_tp(test_bench_def* test_bench) {
  Serial.print(">tb_mode:");
  Serial.println(test_bench->mode);
  
  Serial.print(">tb_start:");
  Serial.println(test_bench->start);
  
  Serial.print(">tb_measuring_cycle_start_time:");
  Serial.println(test_bench->measuring_cycle_start_time);
  
  Serial.print(">tb_time:");
  Serial.println(test_bench->time);
  
  Serial.print(">tb_stop:");
  Serial.println(test_bench->stop);
  
  Serial.print(">tb_measuring_cycle:");
  Serial.println(test_bench->measuring_cycle);
}

void send_vehicle_data_tp(vehicle_def* vehicle) {
  Serial.print(">vehicle_battery_voltage:");
  Serial.println(vehicle->battery_voltage);

  Serial.print(">vehicle_battery_current:");
  Serial.println(vehicle->battery_current);
}

void send_motor_control_data_dmc_tp(motor_control_def* motor_control) {
  Serial.print(">dmc_control_mode:");
  Serial.println(motor_control->control_mode);

  Serial.print(">dmc_excitation_current_max:");
  Serial.println(motor_control->excitation_current_max);

  Serial.print(">dmc_torque_max:");
  Serial.println(motor_control->torque_max);

  Serial.print(">dmc_speed_max:");
  Serial.println(motor_control->speed_max);

  Serial.print(">dmc_throttle_poti_sensor:");
  Serial.println(motor_control->throttle_poti_sensor);

  Serial.print(">dmc_brake_poti_sensor:");
  Serial.println(motor_control->brake_poti_sensor);

  Serial.print(">dmc_excitation_current_poti_sensor:");
  Serial.println(motor_control->excitation_current_poti_sensor);

  Serial.print(">dmc_speed_setpoint:");
  Serial.println(motor_control->speed_setpoint);

  Serial.print(">dmc_torque_setpoint:");
  Serial.println(motor_control->torque_setpoint);

  Serial.print(">dmc_speed_sensor:");
  Serial.println(motor_control->speed_sensor);

  Serial.print(">dmc_torque_sensor:");
  Serial.println(motor_control->torque_sensor);

  Serial.print(">dmc_speed_output:");
  Serial.println(motor_control->speed_output);

  Serial.print(">dmc_torque_output:");
  Serial.println(motor_control->torque_output);

  Serial.print(">dmc_excitation_current_sensor:");
  Serial.println(motor_control->excitation_current_sensor);

  Serial.print(">dmc_excitation_current_output:");
  Serial.println(motor_control->excitation_current_output);

  Serial.print(">dmc_excitation_current_setpoint:");
  Serial.println(motor_control->exication_current_setpoint);

  Serial.print(">dmc_kp_speed:");
  Serial.println(motor_control->kp_speed);

  Serial.print(">dmc_ki_speed:");
  Serial.println(motor_control->ki_speed);

  Serial.print(">dmc_kd_speed:");
  Serial.println(motor_control->kd_speed);

  Serial.print(">dmc_kp_torque:");
  Serial.println(motor_control->kp_torque);

  Serial.print(">dmc_ki_torque:");
  Serial.println(motor_control->ki_torque);

  Serial.print(">dmc_kd_torque:");
  Serial.println(motor_control->kd_torque);

  Serial.print(">dmc_kp_excitation_current:");
  Serial.println(motor_control->kp_excitation_current);

  Serial.print(">dmc_ki_excitation_current:");
  Serial.println(motor_control->ki_excitation_current);

  Serial.print(">dmc_kd_excitation_current:");
  Serial.println(motor_control->kd_excitation_current);

  Serial.print(">dmc_state_foot_switch:");
  Serial.println(motor_control->state_foot_switch);

  Serial.print(">dmc_state_brake_switch:");
  Serial.println(motor_control->state_brake_switch);
}

void send_motor_control_data_kelly_tp(motor_control_def* motor_control) {
  Serial.print(">kelly_control_mode:");
  Serial.println(motor_control->control_mode);

  Serial.print(">kelly_excitation_current_max:");
  Serial.println(motor_control->excitation_current_max);

  Serial.print(">kelly_torque_max:");
  Serial.println(motor_control->torque_max);

  Serial.print(">kelly_speed_max:");
  Serial.println(motor_control->speed_max);

  Serial.print(">kelly_throttle_poti_sensor:");
  Serial.println(motor_control->throttle_poti_sensor);

  Serial.print(">kelly_brake_poti_sensor:");
  Serial.println(motor_control->brake_poti_sensor);

  Serial.print(">kelly_excitation_current_poti_sensor:");
  Serial.println(motor_control->excitation_current_poti_sensor);

  Serial.print(">kelly_speed_setpoint:");
  Serial.println(motor_control->speed_setpoint);

  Serial.print(">kelly_torque_setpoint:");
  Serial.println(motor_control->torque_setpoint);

  Serial.print(">kelly_speed_sensor:");
  Serial.println(motor_control->speed_sensor);

  Serial.print(">kelly_torque_sensor:");
  Serial.println(motor_control->torque_sensor);

  Serial.print(">kelly_speed_output:");
  Serial.println(motor_control->speed_output);

  Serial.print(">kelly_torque_output:");
  Serial.println(motor_control->torque_output);

  Serial.print(">kelly_excitation_current_sensor:");
  Serial.println(motor_control->excitation_current_sensor);

  Serial.print(">kelly_excitation_current_output:");
  Serial.println(motor_control->excitation_current_output);

  Serial.print(">kelly_excitation_current_setpoint:");
  Serial.println(motor_control->exication_current_setpoint);

  Serial.print(">kelly_kp_speed:");
  Serial.println(motor_control->kp_speed);

  Serial.print(">kelly_ki_speed:");
  Serial.println(motor_control->ki_speed);

  Serial.print(">kelly_kd_speed:");
  Serial.println(motor_control->kd_speed);

  Serial.print(">kelly_kp_torque:");
  Serial.println(motor_control->kp_torque);

  Serial.print(">kelly_ki_torque:");
  Serial.println(motor_control->ki_torque);

  Serial.print(">kelly_kd_torque:");
  Serial.println(motor_control->kd_torque);

  Serial.print(">kelly_kp_excitation_current:");
  Serial.println(motor_control->kp_excitation_current);

  Serial.print(">kelly_ki_excitation_current:");
  Serial.println(motor_control->ki_excitation_current);

  Serial.print(">kelly_kd_excitation_current:");
  Serial.println(motor_control->kd_excitation_current);

  Serial.print(">kelly_state_foot_switch:");
  Serial.println(motor_control->state_foot_switch);

  Serial.print(">kelly_state_brake_switch:");
  Serial.println(motor_control->state_brake_switch);
}

void send_measurement_data_tp(measurement_def* measurement) {
  Serial.print(">measurement_torque_measuring_shaft_sensor:");
  Serial.println(measurement->torque_measuring_shaft_sensor);

  Serial.print(">measurement_speed_measuring_shaft_sensor:");
  Serial.println(measurement->speed_measuring_shaft_sensor);
}

void send_data_task_tp(test_bench_def* test_bench, vehicle_def* vehicle, motor_control_def* motor_control_dmc, motor_control_def* motor_control_kelly, measurement_def* measurement){
  send_test_bench_data_tp(test_bench);
  send_vehicle_data_tp(vehicle);
  send_motor_control_data_dmc_tp(motor_control_dmc);
  send_motor_control_data_kelly_tp(motor_control_kelly);
  send_measurement_data_tp(measurement);
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
  send_data_task_tp(&zoe_test_bench,&power_supply,&motor_control_dmc,&motor_control_kelly,&measuring_shaft);
  Serial.print("message_end: ");Serial.println(micros());
  delay(100);
}