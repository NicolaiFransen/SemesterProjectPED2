clear all;
clc;
disp('Building...  Please wait !');
disp(' ');
disp('Sensored FOC for SPMSM');

% INVERTER PARAMETERS

fs=5e3;                            % switching frequency [Hz]
Ts=1/fs;                            % switching period      [s] 


% ENCODER PARAMETERS

Tenc = Ts;                           % encoder counter reading period [s]
E_line = 2048;                    % number of pulses/revolution


% PROTECTIONS

i_maxim_PM=35;                % maximum current of PMSM [A]
i_maxim_IM=8;                   % maximum current of SCIM  [A]
n_maxim =1800;                 % maximum speed                [rpm]
Udc_min_PM=400;              % minimum dc-voltage           [V]
Udc_max_PM=650;             %maximum dc-voltage          [V]
Udc_min_IM=400;               % minimum dc-voltage           [V]


Vdq_limit=300;
Speed_limit=100;
T_PM_limit=14;

lim_v_IM=230*sqrt(2);
lim_T_IM=14.7;
lim_speed_error_IM=80;


% PMSM AND CONTROL PARAMETERS
                             
R_pm=0.53;                     % machine phase resistance [Ohm]
L_pm=0.002;                   % synchronous inductance [H]
lambda_m=0.123;            % rotor peak flux linkage [Wb*turn]
J_pm=0.00048;                % machine moment of inertia [kg*m^2]
npp_PM=4;                      % number of pole pairs per phase

Ld=2e-3;
Lq=2e-3;

Td=1.5*1/5000;  % delay! switching freq is 5 kHz 

Kp_current_d = 3.9;         %proportional factor for current PI d-axis (PMSM)
Ki_current_d = 90*0;          %integrator factor for current PI d-axis (PMSM)
Ka_current_d = 170;         %anti-windup gain for current PI d-axis (PMSM)

Kp_current_q = 3.9*0;                      %proportional factor for current PI q-axis (PMSM)
Ki_current_q = 90*0;                       %integrator factor for current PI q-axis (PMSM)
Ka_current_q = 170;                      %anti-windup gain for current PI q-axis (PMSM)

Kp_speed = 0.13*0;         %proportional factor for speed PI (PMSM)
Ki_speed = 2.2*0;          %integrator factor for speed PI (PMSM)
Ka_speed = 160;               %anti-windup gain for speed PI (PMSM)


Kpe          =200;
Kie           = 5000;
    %Bw (rad/s)
    %1800    900     500    100
    %1.5e3; %767;   %426;  %85;    
    %2.6e5; %6.5e4; %2e4;  %807;
    
Kpc          = 4;  %10;
Kic           = 20;   %2;



% IM AND CONTROL PARAMETERS

npp_IM=2;                          %number of pole pairs
Lm=0.285;                        %magnetizing inductance [H]


% SCALING FACTORS FOR PMSM AND SCIM

Ia_tr_PMSM=1/1000;
Ib_tr_PMSM=1/1000;
Ic_tr_PMSM=1/1000;

Rm_a_PMSM=220;
Rm_b_PMSM=220;
Rm_c_PMSM=220;


Ia_tr_IM=5/1000;
Ib_tr_IM=5/1000;
Ic_tr_IM=5/1000;

Rm_a_IM=220;
Rm_b_IM=220;
Rm_c_IM=220;


Udc_tr_PMSM=25e-3/800;
Rm_Udc_PMSM=220;

Udc_tr_IM=25e-3/800;
Rm_Udc_IM=220;