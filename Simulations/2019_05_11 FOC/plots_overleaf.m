%% Plots for simulation results FOC 

alldatacursors = findall(gcf,'type','hggroup')
set(alldatacursors,'FontSize',12)
set(alldatacursors,'FontName','Times')
set(alldatacursors, 'FontWeight', 'bold')

%% Torque, speed and current
figure(1)
subplot(3,1,1)
plot(torques,'Linewidth',1);
%xlim([0.8 0.8+3*Tn])
ylim([0 40])
legend('T_e', 'T_L','fontsize',14)
xlabel('Time [s]','fontsize',12)
ylabel('Torques [Nm]','fontsize',12)
title(' ')
subplot(3,1,2)
plot(speed_ref,'Linewidth',1);
%xlim([0.8 0.8+3*Tn])
ylim([0 1700])
legend('w_{ref}','w_r','fontsize',14)
xlabel('Time [s]','fontsize',12)
ylabel('Rotor speed [rpm]','fontsize',12)
title(' ')
subplot(3,1,3)
plot(currents,'Linewidth',1);
%xlim([0.8 0.8+3*Tn])
ylim([-300 400])
legend('I_a', 'I_b', 'I_c','fontsize',14)
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

%% Id and Iq in subplot
figure(5)
subplot(2,1,1)
plot(id,'Linewidth',1)
%xlim([0.8 0.8+3*Tn])
ylim([-10 180])
legend('Id_{ref}','I_d','fontsize',14)
xlabel('Time [s]','fontsize',12)
ylabel('Direct current [A]','fontsize',12)
title(' ')
subplot(2,1,2)
plot(iq,'Linewidth',1);
%xlim([0.8 0.8+3*Tn])
ylim([-5 220])
legend('Iq_{ref}', 'I_q','fontsize',14)
xlabel('Time [s]','fontsize',12)
ylabel('Quadrature current [A]','fontsize',12)
title(' ')

%% Torques and currents  subplot 

figure(6)
subplot(2,1,1)
plot(Te_ref, 'Linewidth',1)
hold on
plot(torques,'Linewidth',1);
%xlim([0.8 0.8+3*Tn])
ylim([-5 40])
legend('Te_{ref}','T_e', 'T_L','fontsize',14)
xlabel('Time [s]','fontsize',12)
ylabel('Torques [Nm]','fontsize',12)
title(' ')
subplot(2,1,2)
plot(currents,'Linewidth',1);
%xlim([0.8 0.8+3*Tn])
ylim([-300 400])
legend('I_a', 'I_b', 'I_c','fontsize',14)
xlabel('Time [s]','fontsize',12)
ylabel('Currents [A]','fontsize',12)
title(' ')