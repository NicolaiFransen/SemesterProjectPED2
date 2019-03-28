t = 0:0.02/1002:0.02;

sinewave = 0.5+(sin(100*pi*t)/2);
sine_round = 1000 * round(sinewave, 3)
plot(t, sinewave);