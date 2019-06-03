%% Optimisation exam 2018
clear
clc

%% Exercise 1

syms x1 x2 u1 s1
f = (x1+2)^2 + (x2+2)^2;
g = 2-x1-x2+s1^2;

L = f + u1*g;

L_dx1 = diff(L, x1);
L_dx2 = diff(L, x2);
L_du1 = diff(L, u1);
L_ds1 = diff(L, s1);


% Case 1
u = 0;

eqs = [subs(L_dx1, u1, u) == 0, subs(L_dx2, u1, u) == 0];
[solx1, solx2] = solve(eqs, [x1 x2]);
sols1 = solve(subs(g, {x1, x2}, {solx1, solx2}), s1);
f_x = subs(f, {x1 x2}, {solx1, solx2});

% Case 2
s = 0;

eqs = [L_dx1 == 0, L_dx2 == 0, subs(g, s1, s) == 0];
[solx1, solx2, solu1] = solve(eqs, [x1 x2 u1]);
f_x = subs(f, {x1 x2}, {solx1, solx2});



% eqs = [L_dx1 == 0, L_dx2 == 0, subs(L_du1, s1, s) == 0, subs(L_ds1, s1, s) == 0];
% [solx1, solx2, solu1] = solve(eqs, [x1 x2 u1])

%% Exercise 2
% a) Complete the first iteration of the steepest descent method for the function

syms x1 x2 alpha
f = 5*(x1^2-x2) + (x2-1)^2 - 2*x1 + 3;

% Step 1
x_0 = [3 4];
k = 1;
epsilon = 0.0001;
f_x0 = double(subs(f, {x1, x2}, x_0));

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

df_x1 = diff(f1, alpha);
alpha_0 = double(solve(df_x1, alpha));

% Step 6
x = double(subs(x_1, alpha, alpha_0));

f_x1 = double(subs(f, {x1, x2}, x));

%%%% b) Complete the first iteration of the modified newtons method for the function

syms x1 x2 alpha
f = 5*(x1^2-x2) + (x2-1)^2 - 2*x1 + 3;

% Step 1
x_0 = [3 4];

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
f_1 = double(subs(f, {x1, x2}, x));


%% Exercise 3
% Calculate the step size using the inexact line search procedure 
% (approximate step size procedure) and determine the new design variables

syms x1 x2
f = 10*x1^4 + 2*x2^2 - 2*x1^2*x2 - 5*x1 - x2;
g1 = x2 - 10;
g2 = 2*x1 + 4*x2 - 10;
g3 = x1 -x2 - 1;

gamma = 0.5;
x_0 = [0 1];


f_0 = double(subs(f, {x1, x2}, x_0));
d_0 = [1.5 0.5];

u = [0 0 3.5];
% v = -45008.9; No equality constraints

R = sum(u);
beta_0 = gamma * norm(d_0)^2;

V_0 = 0;

Phi_0 = f_0 + R*V_0;

t_0 = 1;
x_1_0 = x_0 + t_0*d_0;

f_1_x1 = double(subs(f, {x1, x2}, x_1_0));
g_1_x1 = double(subs(g1, {x1, x2}, x_1_0));
g_2_x1 = double(subs(g2, {x1, x2}, x_1_0));
g_3_x1 = double(subs(g3, {x1, x2}, x_1_0));


V_1_0 = 0;
Phi_1_0 = f_1_x1 + R*V_1_0;

Phi_1_0 + t_0*beta_0;

t_1 = 0.5;
x_1_1 = x_0 + t_1*d_0;

f_1_1 = double(subs(f, {x1, x2}, x_1_1));
g_1_1 = double(subs(g1, {x1, x2}, x_1_1));
g_2_1 = double(subs(g2, {x1, x2}, x_1_1));
g_3_1 = double(subs(g3, {x1, x2}, x_1_1));

V_1_1 = 0;
Phi_1_1 = f_1_1 + R*V_1_1;

Phi_1_1 + t_1*beta_0;

%% Exercise 4

syms x1 x2
f1 = (x1-2)^2 + (x2-8)^2 + 6;
f2 = (x1-10)^2 + (x2-4)^2 + 2;

w1 = 2; w2 = 1;

U = w1*f1 + w2*f2;

c = gradient(U);

eqs = [c(1) == 0, c(2) == 0];
[solx1, solx2] = solve(eqs, {x1, x2});

