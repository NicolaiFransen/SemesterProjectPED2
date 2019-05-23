% Motor Parameters
% Sauer-Danfoss TSA170-210-038

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

Udc=36;          % DC-link voltage
fs = 10000;
Ts=1/fs;

%Parameters for mechanical model: (values from report 2017)
Rw = 0.1375;                            %meters Radius of the wheel 
density = 1.2041;                        %kg/m^3 air density
Cd = 0.804;                               %Aerodynamic drag coefficient 
Af = 0.5784;                               %m^2 Kart's approx. front area assuming the kart is a prismatic body
Mcar = 233;                                %kg Mass including motor, chasis and driver 
%Cr = 0.013;                             %Consider putting it as a function of speed                       
                                        %Tire rolling resistance coefficient. http://eprints.lancs.ac.uk/84708/1/ISIE2016_KR_FInalSubmission_CJT_v3.pdf
Gr = 1.6666;                            %Transmission gearbox ratio
g=9.81;           
Mw =  20;                               %Mass of the 4 wheels (to be weighted)
Jw = 0.5*(Rw/Gr)^2*Mw;                  %Moment of inertia corresponding to the 4 wheels

%Rotor flux position determination
landa_r = 0.0567;  
ids=(1/Lm)*landa_r;


%PI current controllers id, iq  

R = 0.02*0.15;
Kp_q= 1.12; %0.7088; %1.12; %  %0.26;
Ki_q= 6.81; %4.31; %  %15.7;
 
Kp_d= 1.12; %0.7088; %2.0153;  %0.26;
Ki_d= 6.81; %4.31; %12.25;  %12.25;  %15.7; 

G_p = 1/(Ls*s+Rs);  %Plant's TF

G_PI= Kp_d + Ki_d/s;

G_ol= G_PI*G_p;

G_cl = G_ol/(1+G_ol);

figure(1)
bode(G_cl)

%Current controller including time delay:
Td = 0.5*Ts;
Gp = (1/(Ls*s+Rs))*(1/(Td*s+1));
Kp = 1.12; %2.0153; %1.00051;
Ki = 6.81; %12.25; %6.0838;
GPI = Kp + Ki/s;
Gol = GPI*Gp;
Gcl = Gol/(1+Gol);
figure(5)
margin(Gcl)


syms phi 
eqn = (1/(2*phi*Td))*sqrt((1-2*phi^2)+sqrt(4*phi^4-4*phi^2+2)) == 2*pi*500;
sol_phi = solve(eqn, phi)

%Speed controller: 

% Kp_speed = 0.94; %0.8;  %4.2; 
% Ki_speed= 0.094; %5;  %30; 

Kp_w = 3.5002; %8.7; 
Ki_w = 0.35002; %0.87;
k = (3/2)*p*(Lm/Lr)*landa_r;
B= 0.00151; %0.00151; %B/J = 0.1 (to be checked) 
Tc = 1.4e-3; %150.25e-6; %time constant current controller

G_s = (1/(Tc*s+1))*(1/(J*s+B))

Gol_speed = (Kp_w + Ki_w/s)*(1/(Tc*s+1))*(1/(J*s+B))

Gcl_speed = Gol_speed/(1 + Gol_speed)

syms phi_w 
eqn_w = (1/(2*phi_w*Tc))*sqrt((1-2*phi_w^2)+sqrt(4*phi_w^4-4*phi_w^2+2)) == 2*pi*50;
sol_phi_w = solve(eqn_w, phi_w)

alldatacursors = findall(gcf,'type','hggroup')
set(alldatacursors,'FontSize',12)
set(alldatacursors,'FontName','Times')
set(alldatacursors, 'FontWeight', 'bold')

figure(2)
margin(G_s)

figure(3)
margin(Gol_speed)

figure(4)
margin(Gcl_speed)
