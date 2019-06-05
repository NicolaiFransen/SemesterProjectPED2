%% Relibilty sample exam set 2019
clear
clc
%% Exercise 1
L_N = 3000;
T_N = 90;
T_acc = 125;
m = 4.75;

L_acc = L_N * (T_acc/T_N)^-m;

%% Exercise 2
% A) Draw the RBD of the system. See paper.

% B) Calculate the system reliabilty at 1 month and 1 year
t = 24*365;
% Sub component A
% Exponential
% mean_life_A = 10^6;
lambda_A = 20/10^6;
R_A_sub = exp(-lambda_A*t);

% Total component A
R_A = R_A_sub;

% Sub component B
% Weibull
eta_B = 30000;
beta_B = 1.5;
R_B_sub = exp(-(t/eta_B)^beta_B);

% Component B
R_B = 1-((1-R_B_sub*R_B_sub) * (1-R_B_sub*R_B_sub));


% Sub component C
% Normal
mean_C = 20000;
sd_C = 3000;

f_C = @(x) 1/(sd_C*sqrt(2*pi)) * exp(-(x-mean_C).^2/(2*sd_C^2));
R_C_sub = integral(f_C, t, Inf);

R_C = 1 - ((1-R_C_sub)^3 + 3*R_C_sub*(1-R_C_sub)^2);

% Sub component D
% Lognormal
mean_D = 9;
sd_D = 4;

f_D = @(x) 1./(sd_D.*x.*sqrt(2.*pi)) .* exp(-(log(x)-mean_D).^2./(2.*sd_D^2));
R_D_sub = integral(f_D, t(1), Inf);

R_D = R_D_sub * R_D_sub

% Sub component F
% Exponential
% mean_life_A = 10^6;
lambda_F = 175/10^6;
R_F_sub = exp(-lambda_F*t);

% Total component F
R_F = 1-((1-R_F_sub) * (1-R_F_sub));

R = R_A * R_B * R_C * R_D * R_F;

%% Exercise 3A
% No overhanging structure tells us no mean stress applied.

% Calculate B0:
CTF = 10000;
delta_sigma = 12;      
delta_elastic = 0;
m = 3.5;

B0 = CTF/((delta_sigma - delta_elastic)^(-m));

delta_sigma = 5;      

CTF_no_offset = B0 * (delta_sigma - delta_elastic)^(-m);

% Exercise 3B
% With overhanging structure tells us no mean stress applied.

sigma_mean      = 1.8;
sigma_TS        = delta_sigma + sigma_mean;

CTF_with_offset = B0 * (((delta_sigma/(1-(sigma_mean/sigma_TS))) - delta_elastic)^(-m));

%% Exercise 4
% A
cycleRate = 1000;

N = [0.5 0.3 0.15 0.05] * cycleRate;        % Number of cycles (Proportion)
NF = [10.9 4.5 0.76 0.23] * 10^6;             % Number of cycles to failure

TCL_A = sum(N./NF);
TTF_hours_A = 1/TCL_A;        % Hours

%% Exercise 5
% Weilbull plotting

%% Exercise 6
t = 300;

% Product A
MTBF = 1000;
lambda_A = 1/MTBF;
R_A = exp(-lambda_A*t)


% Sub component B
% Weibull
eta_B = 1000;
beta_B = 3;
R_B = exp(-(t/eta_B)^beta_B)

%% Exercise 7

data = [0 50 20 40 25 35 22 50 28 48 42 40 35 40 25 60 40 20 30];

% Rainflow
[c,hist,edges,rmm,idx] = rainflow(data,1);

T = array2table(c,'VariableNames',{'Count','Range','Mean','Start','End'});

N = transpose(table2array(T(:,1)));                 % Cycle count

delta_T = transpose(table2array(T(:,2)));   
N_F = 6.25*10^12 .*(delta_T).^(-4.5);               % Cycles to failure

TCL = sum(N./N_F);                                  % Miner's rule

TTF = 1/(TCL/19);                