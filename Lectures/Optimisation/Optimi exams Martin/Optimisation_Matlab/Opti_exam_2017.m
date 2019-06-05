%% Optimisation exam - 2017

%% Exercise 1
% Create optimisation problem

%% Exercise 2 - A
% a) Complete the first iteration of the steepest descent method for the function

syms x1 x2 alpha
f = (x1-1)^2 + 2*x2^2;

% Step 1
x_0 = [3 1];
k = 1;
epsilon = 0.0001;


% Step 2
c = gradient(f);
c_0 = double(subs(c, {x1, x2}, x_0));

% Step 3
c_norm = norm(c_0);
% c_norm is greater than epsilon, then continue

% Step 4
d = -c_0;

% Step 5
x_1 = x_0 + alpha*transpose(d);
f1 = subs(f, {x1, x2}, x_1);

df_x1 = diff(f1, alpha)
alpha_0 = double(solve(df_x1, alpha));

% Step 6
x = double(subs(x_1, alpha, alpha_0));

f_x1 = subs(f, {x1, x2}, x);

%% Exercise 2 - B
% a) Complete the first iteration of the modified newtons method for the function

syms x1 x2 alpha
f = (x1-1)^2 + 2*x2^2;

% Step 1
x_0 = [3 1];

% Step 2
c = gradient(f);                 % Determining the gradient c
c_0 = subs(c, {x1, x2}, x_0);
c_0_norm = double(norm(c_0));

% Step 3
H_0 = double(hessian(f));

% Step 4
d_0 = -H_0^-1 * c_0;

% Step 5
x_1 = x_0 + alpha*transpose(d_0);
f_x1 = simplify(subs(f, {x1, x2}, x_1));

df_x1 = diff(f_x1, alpha);
alpha_0 = double(solve(df_x1, alpha));

x = double(subs(x_1, alpha, alpha_0));

% Step 6
f_1 = subs(f, {x1, x2}, x);


%% Exercise 3
clc
row1_v0 = [-1 1 1 0 10];
row2_v0 = [2 -1 0 1 20];
cost_v0 = [-5 -2 0 0 0];

row1_v1 = row1_v0 * -1;
row2_v1 = row2_v0 - row1_v1*2;
cost_v1 = cost_v0 + row1_v1*5;

row1_v2 = row1_v1 * -1
row2_v2 = row2_v1 + row1_v1
cost_v2 = cost_v1 + row1_v2*7

%% Exercise 4

syms x1 x2
f1 = (x1-5)^2 + (x2-15)^2;
f2 = (x1-15)^2 + (x2-5)^2;

% b)
x_1 = [5 15];
x_2 = [10 10];
x_3 = [10 5];

f1_x1 = double(subs(f1, {x1, x2}, x_1));
f2_x1 = double(subs(f2, {x1, x2}, x_1));

f1_x2 = double(subs(f1, {x1, x2}, x_2));
f2_x2 = double(subs(f2, {x1, x2}, x_2));

f1_x3 = double(subs(f1, {x1, x2}, x_3));
f2_x3 = double(subs(f2, {x1, x2}, x_3));

%% Exercise 7
t = 2000;

% Component M1
% Weibull
eta_1 = 3000;
beta_1 = 0.5;
R_1 = exp(-(t/eta_1)^beta_1);

% Component M2
% Exponential
mean_life_2 = 2500;
lambda_2 = mean_life_2^-1;
R_2 = exp(-lambda_2*t);

% Total reliability
R = 1-((1-R_1) * (1-R_2));
