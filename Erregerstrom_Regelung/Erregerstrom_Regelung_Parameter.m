SAMPLE_TIME = 5e-5; %s

% Parameter Erregerstromkreis

R_ROTOR = 8; %Ohm - zunächst als konstant angenommen, kann z.B. im Setup mit einem 100% DC vermessen werden
L_ROTOR = 0.4; %H Messung von Herr Zirn 03.2022
U_BATT_TRAKTION = 48; %V

PWM_FREQUENCY = 1000; %Hz

I_Erregung_MAX = U_BATT_TRAKTION/R_ROTOR; %A zunächst als konstant angenommen