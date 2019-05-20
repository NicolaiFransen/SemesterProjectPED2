%% Calculations regarding IM model
%% Validating Power Factor

Tn = 1/fn;

delta_T = 2e-3;

phi_deg = 360/Tn * delta_T;
phi_rad = phi_deg * pi/180;
PF = cos(phi_rad);

%% Slip calculation
ns = fn*60/p;

s = (ns-nn)/ns * 100;        % Slip in %

figure(1)
plot(slip,'Linewidth',1);
legend('Rotor mechanical speed', 'Synchronous speed')
xlabel('Time [s]','fontsize',12)
ylabel('Speed [rpm]','fontsize',12)
ylim([0 2500])
title(' ')

%% Plot of PF validation
figure(2)
plot(powerfactor,'Linewidth',1);
xlim([0.8 0.8+3*Tn])
ylim([-1.5 1.5])
legend('Voltage gain', 'Current gain')
xlabel('Time [s]','fontsize',12)
ylabel('Gain [-]','fontsize',12)
title(' ')


%% Plot abc currents 

figure(3)
subplot(2,1,1)
plot(currents, 'Linewidth',1);
legend('Ia', 'Ib','Ic')
xlabel('Time [s]','fontsize',12)
ylabel('Currents [A]','fontsize',12)
title(' ')
subplot(2,1,2)
plot(currents, 'Linewidth',1);
legend('Ia', 'Ib','Ic')
xlabel('Time [s]','fontsize',12)
ylabel('Currents [A]','fontsize',12)
xlim([0.9 1])
ylim([-350 350])
title(' ')
%% Plot electromagnetic torque vs load torque 

figure(4)
plot(torque,'Linewidth',1);
legend('Electromagnetic torque', 'Load torque')
xlabel('Time [s]','fontsize',12)
ylabel('Torques [Nm]','fontsize',12)
ylim([-40 60])
title(' ')