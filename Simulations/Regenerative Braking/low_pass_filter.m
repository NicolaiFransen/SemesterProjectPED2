lp1 = tf(1, [1.13*10^-4 1]);
bode(lp1);

hold on;
lp2 = tf(1, [1.13*10^-3 1]);
bode(lp2);
legend;
