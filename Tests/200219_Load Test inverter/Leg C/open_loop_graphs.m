close all;
clc;

%% Inverter test
data = csvread('36V.csv');

t = data(:,1);
vin = data(:, 2);
vds = data(:, 3);
iload = data(:, 4);

figure(2)
%plot(t, vin, 'b', 'Linewidth', 1.5)
hold on
plot(t, vds, 'r', 'Linewidth', 1.5)
plot(t, iload, 'b', 'Linewidth', 1.5)
%xlim([0.2, 0.5]);
%ylim([0, 30]);
title('Drain Source Voltage (Low Side @ 36V)')
xlabel('Time[s]');
ylabel('Current[A], Voltage[V]');
legend('V_{out}');

