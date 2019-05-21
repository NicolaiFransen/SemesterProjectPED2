%% Plots for simulation results FOC 

%% Torque, speed and current
figure(1)
subplot(3,1,1)
plot(torques,'Linewidth',1);
%xlim([0.8 0.8+3*Tn])
ylim([-20 40])
legend('T_e', 'T_L')
xlabel('Time [s]','fontsize',12)
ylabel('Torques [Nm]','fontsize',12)
title(' ')
subplot(3,1,2)
plot(speed_ref,'Linewidth',1);
%xlim([0.8 0.8+3*Tn])
ylim([0 500])
legend('w_{ref}','w_r')
xlabel('Time [s]','fontsize',12)
ylabel('Rotor speed [rpm]','fontsize',12)
title(' ')
subplot(3,1,3)
plot(currents,'Linewidth',1);
%xlim([0.8 0.8+3*Tn])
ylim([-300 400])
legend('I_a', 'I_b', 'I_c')
xlabel('Time [s]','fontsize',12)
ylabel('Currents [A]','fontsize',12)
title(' ')

%% Id and Iq current

figure(2)
plot(id,'Linewidth',1)
legend('I_d,ref', 'I_d')
xlabel('Time [s]','fontsize',12)
ylabel('Direct current [A]','fontsize',12)
ylim([0 181])
title(' ')

figure(3)
plot(iq,'Linewidth',1)
legend('I_q,ref','I_q')
xlabel('Time [s]','fontsize',12)
ylabel('Quadrature current [A]','fontsize',12)
ylim([-210 210])
title(' ')

%% Torques 

figure(4)
plot(Te,'Linewidth',1)
legend('T_e,ref','T_e')
xlabel('Time [s]','fontsize',12)
ylabel('Electromagnetic torque [Nm]','fontsize',12)
ylim([-20 20])
title(' ')

figure(5)
subplot(2,1,1)
plot(id,'Linewidth',1)
%xlim([0.8 0.8+3*Tn])
ylim([-10 180])
legend('Id_{ref}','I_d')
xlabel('Time [s]','fontsize',12)
ylabel('Direct current [A]','fontsize',12)
title(' ')
subplot(2,1,2)
plot(iq,'Linewidth',1);
%xlim([0.8 0.8+3*Tn])
ylim([-110 220])
legend('Iq_{ref}', 'I_q')
xlabel('Time [s]','fontsize',12)
ylabel('Quadrature current [A]','fontsize',12)
title(' ')
