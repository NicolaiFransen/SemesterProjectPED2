% Motor Parameters
% Sauer-Danfoss TSA170-210-038

clear

s = tf('s');

% % Induction motor constant parameters
% 
Lm = 0.38e-3;                           % magnetizing inductivity [H]%
Lds = 31.16e-6;                         % stator leakage inductivity [H]%
Ldr = 31.16e-6;                         % rotor leakage inductivity [H]%
Ls = Lm + Lds;                          % stator total inductivity [H]%
Lr = Lm + Ldr;                          % rotor total inductivity [H]%
Rs = 2.5e-3;                            % stator resistance [ohms]%
Rr = 2.69e-3;                           % rotor resistance [ohms]%
p = 2.0;                                % number of pole-pairs %
J=0.0151;                               % rotor inertia moment [Nm^2]

% Induction motor nameplate
Pn = 5300;                              % nominal power [W]
Un = 24/sqrt(3);                        % nominal phase voltage RMS[V]
In = 189;                               % nominal current RMS[A]
fn = 58;                                % nominal frequency [Hz]
PF = 0.76;                              % nominal power factor [pu]
nn = 1685;                              % nominal shaft speed
Omegae = 2*pi*fn;                       % nominal electrical angular speed [rad]
T_rated = Pn/(2*pi*nn/60);              % nominal Torque [Nm]

% ____________________________________________________________________________________________

Udc=36;  % DC-link voltage
fs               = 10000;
Ts=1/fs;

% PI current controllers id, iq 

Kp_q= 2.5834;
Ki_q= 15.708;


Kp_d= 2.5834; %0.8223;
Ki_d= 15.708;  %6.0804;


Kp_speed = 2; 
Ki_speed=2; 

landa_r = 0.0567;  %need to be checked
ids=(1/Lm)*landa_r;

G = 1/(Ls*s+Rs);  %Plant's transfer function
figure(1)
margin(G)

Gc = ((Kp_d*Ki_d)*(1+s/Ki_d))/s
G_PI= Kp_d + Ki_d/s

G_total = G_PI*G
G_series = Gc*G

figure(2)
margin(G_total)

figure(3)
margin(G_series)

tau_r=Lr/Rr;
TF_speed= (tau_r)*ids/(1+s*tau_r)
