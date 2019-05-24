%% Plots for simulation results FOC 

%% Torque, speed and current
figure(1)
subplot(2,1,1)
plot(Torque,'Linewidth',1);
%xlim([0.8 0.8+3*Tn])
ylim([-40 50])
legend('T_e', 'T_L', 'T_{ref}','fontsize', 14)
xlabel('Time [s]','fontsize',15)
ylabel('Torque [Nm]','fontsize',15)
title(' ')
subplot(2,1,2)
plot(speed,'Linewidth',1);
%xlim([0.8 0.8+3*Tn])
ylim([0 1300])
legend('w_{ref}','w_r', 'fontsize', 14)
xlabel('Time [s]','fontsize',15)
ylabel('Rotor speed [rpm]','fontsize',15)
%%
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
subplot(3,1,1)
plot(id,'Linewidth',1)
legend('I_d,ref', 'I_d', 'fontsize', 14)
xlabel('Time [s]','fontsize',15)
ylabel('Direct current [A]','fontsize',15)
ylim([0 181])
title(' ')

subplot(3,1,2)
plot(iq,'Linewidth',1)
legend('I_q,ref','I_q', 'fontsize', 14)
xlabel('Time [s]','fontsize',15)
ylabel('Quadrature current [A]','fontsize',15)
ylim([-210 210])
title(' ')

subplot(3,1,3)
plot(idc,'Linewidth',1)
legend('I_{DC}', 'fontsize', 14)
xlabel('Time [s]','fontsize',15)
ylabel('DC Link current [A]','fontsize',15)
ylim([-100 100])
title(' ')

%% Torques 

figure(4)
plot(Te,'Linewidth',1)
legend('T_e,ref','T_e')
xlabel('Time [s]','fontsize',12)
ylabel('Electromagnetic torque [Nm]','fontsize',12)
ylim([-20 20])
title(' ')
