close all


n50 = [34 97 125 230 327]; %530 620 750 850 1000 1160 1224 1400 1500],
T50 = [0.7 1.5 1.7 2.6 3 ];%3.4 3.4 3.2 3.2 3.1 3 2.2 2.1 2.1];

n100 = [30 75 135 200 400];
T100 = [1.7 3.3 5.8 7.5 9.2];

n150 = [45 108 162 211 240 300];
T150 = [4.1 9.3 13 15.5 17 18.5];

plot(n50, T50, 'LineWidth',5,'MarkerSize',10)
hold on
plot(n100, T100,  'LineWidth',5,'MarkerSize',1)
hold on
plot(n150, T150, 'LineWidth',5,'MarkerSize',1)
title({'{\bf\fontsize{14} Load machine testing}'; '{\itR_{EXT} = 1.8 \Omega} '},'FontWeight','Normal')
%({'Load machine testing',' R_{EXT} = 1.8 Ohm'})
xlabel('Speed (RPM)')
ylabel('Torque (Nm)')
legend('V_{exc} = 50 V', 'V_{exc} = 100 V', 'V_{exc} = 150 V')
hold off
