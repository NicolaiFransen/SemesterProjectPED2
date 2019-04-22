close all

t = 0:0.02/1002:0.02;

phaseShift = [0 2*pi/3 -2*pi/3]
sinewaveA = 0.5+(sin(100*pi*t + phaseShift(1))/2);
sinewaveB = 0.5+(sin(100*pi*t + phaseShift(2))/2);
sinewaveC = 0.5+(sin(100*pi*t + phaseShift(3))/2);
sine_roundA = round(sinewaveA, 2);
sine_roundB = round(sinewaveB, 2);
sine_roundC = round(sinewaveC, 2);
plot(t, sine_roundA);
hold on
plot(t, sine_roundB);
plot(t, sine_roundC);
hold off