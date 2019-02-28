%% Interface board calculations
clc
clear
close all

%% Voltage divider for 24V measuring
Vin = 5;
Vout = 0.75;
R1 = 61.9e3;

syms R2
eq = Vout == (R2/(R1+R2))*Vin;
solve(eq, R2)

%% Current amplifier transfer function

R1 = 10e3;
R2 = R1;
R3 = (61.9e3);
R4 = 12.1e3;
Rin = 9.09;

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

R1 = 21.5e3;
R2 = 1e3;

R1_1 = 10e3;
R3 = 16.2e3;

Vdc = 45;
Vin = (R2/(R1+R2)) * Vdc;

Vout = R3/R1_1 * Vin
%Vout = 3;
%R3 = Vout*R3 / (Vin);

%% Voltage sensor filtering

c = 10e-9;
R1 = 21.5e3;
f = 1/(2*pi*R1*c)


%%
V1 = 2;
Vdc = 40;
R1 = 1e3;
syms R
eq = V1 == (R1/(R+R1)) * Vdc;
solve(eq, R)

%% Voltage divider for 24V measuring
Vin = 30;
Vout = 3.3;
R2 = 1e3;

syms R1
eq = Vout == (R2/(R1+R2))*Vin;
solve(eq, R1)

R1 = 8.25e3;
(R2/(R1+R2))*Vin

%% Encoder calculations
Vin = 5;

R1 = 1e3;
R2 = 1.78e3;

(R2/(R1+R2))*Vin

%% LEDs
Iled = 20e-3;

Vin = [3.3 5 12 15 24 36];

R_led = (Vin-2)/Iled;

led = [Vin;R_led];

