%% Interface board calculations
clc
clear
close all

%% Current amplifier transfer function

R1 = 10e3;
R2 = R1;
R3 = (62e3 + 330);
R4 = 11e3;
Rin = 5;

Iin = -300:1:300;
Vref = 5;
Vin = (Iin/2000) * Rin;

Vb = (R4/(R3+R4)) * Vref;
G = -R2/R1;

Vo = G*Vin + (1-G)*Vb;

figure
plot(Iin, Vo)

%% Rin calculation
Voutmax = 3;
Vinmin = (Voutmax-(1-G)*Vb)/G;

Imin = -300/2000;
Rin = Vinmin/Imin;

Vin = (Iin/2000) * Rin;
Vout = G*Vin + (1-G)*Vb;

figure
plot(Iin, Vout)
xlabel('Measured current')
ylabel('Output voltage')

%% Voltage sensor Amplification
clear
close all

R1 = 20e3;
R2 = 1e3;

R1_1 = 10e3;
R3 = 16e3;

Vdc = 40;
Vin = (R2/(R1+R2)) * Vdc;

Vout = R3/R1_1 * Vin
%Vout = 3;
%R3 = Vout*R3 / (Vin);

%% Voltage sensor filtering

f = 1000;

c = 1/(2*pi*f*R1)


%%
V1 = 2;
Vdc = 40;
R1 = 1e3;
syms R
eq = V1 == (R1/(R+R1)) * Vdc;
solve(eq, R)
