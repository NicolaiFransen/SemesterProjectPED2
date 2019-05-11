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

%Parameters for mechanical model: (values from report 2017)
Rw = 0.1375;                            %meters Radius of the wheel 
density = 1.225;                        %kg/m^3 air density
Cd = 0.8;                               %Aerodynamic drag coefficient 
Af = 0.5;                               %m^2 Kart's approx. front area assuming the kart is a prismatic body
Mcar = 233;                             %kg Mass including motor, chasis and driver 
%Cr = 0.013;                             %Consider putting it as a function of speed                       
                                        %Tire rolling resistance coefficient. http://eprints.lancs.ac.uk/84708/1/ISIE2016_KR_FInalSubmission_CJT_v3.pdf
Gr = 1.6666;                            %Transmission gearbox ratio
g=9.81;           
Mw =  20;                               %Mass of the 4 wheels (to be weighted)
Jw = 0.5*(Rw/Gr)^2*Mw;                  %Moment of inertia corresponding to the 4 wheels
% ____________________________________________________________________________________________

Udc=36;          % DC-link voltage
fs = 10000;
Ts=1/fs;


Kp_q=  2.5834;  
Ki_q=  50;   
 
Kp_d= 2.5834; 
Ki_d= 50; 

Kp_speed = 0.8; %0.8; 
Ki_speed= 5;   %5;  

%Rotor flux calculation for id,ref
landa_r = 0.0567;  
ids=(1/Lm)*landa_r;

%Limit iq,ref:
iqmax = (2/3)*(Lr*T_rated)/(p*Lm*landa_r);


G_p = 1/(Ls*s+Rs);  %Plant's transfer function
figure(1)
margin(G_p)

G_PI= Kp_d + Ki_d/s

G_ol= G_PI*G_p
figure(2)
margin(G_ol)

sigma = 1-Lm^2/(Ls*Lr); %leakage factor

