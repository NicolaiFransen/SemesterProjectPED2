%% Calculations regarding IM model
close all
clc

Motor_parameters_project
%% Validating Power Factor

Tn = 1/fn;

delta_T = 2e-3;

phi_deg = 360/Tn * delta_T;
phi_rad = phi_deg * pi/180;
PF = cos(phi_rad);

%% Slip calculation
ns = fn*60/p;

s = (ns-nn)/ns * 100;        % Slip in %

figure
plot(slip);
legend('Rotor speed', 'Synchronous speed')
xlabel('Time [s]')
ylabel('Speed [rpm]')
title('Speed')

%% Plot of PF validation
figure
plot(PF_validation);
xlim([0.8 0.8+3*Tn])
ylim([-1.2 1.2])
legend('Voltage gain', 'Current gain')
xlabel('Time [s]')
ylabel('Gain [-]')
title('PF validation')