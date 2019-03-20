t = 0:0.0005:0.02;

sinewave = sin(100*pi*t)
sine_round = round(sinewave, 3)
plot(t, sinewave)