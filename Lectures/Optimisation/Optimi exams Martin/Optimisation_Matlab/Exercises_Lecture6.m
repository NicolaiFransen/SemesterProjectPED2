%% Optimisation - Lecture 6

%% Exercise 5.14

syms x1 x2 u1
f = 4*x1^2 + 3*x2^2 - 5*x1*x2 - 8;
g = x1 + x2 -4;
L = f + u1*g;

L_dx1 = diff(L, x1);
L_dx2 = diff(L, x2);

eqs = [L_dx1 == 0, L_dx2 == 0];
[solx1, solx2] = solve(eqs, {x1, x2});

eqs = [L_dx1 == 0, L_dx2 == 0, g == 0];
[solx1, solx2, solu1] = solve(eqs, {x1, x2, u1});

H = [8 -5; -5 6];
lambda = double(eig(H));

%% Exercise 12.15
syms P1 P2
f = 2 + 0.6*P2 - P1 + P1^2 + P2^2;

P_0 = [2 1];
f_0 = subs(f, {P1 P2}, P_0);

c = gradient(f);
c_0 = subs(c, {P1 P2}, P_0);



%% Exercise 12.26
syms D H
x_0 = [4 8];

f = 400*(pi* (D^2/2) + pi*D*H);
h_1 = pi*D^2/600 * H - 1;
g_1 = H/10 + D/20 - 1;

f_x0 = subs(f, {D, H}, x_0);
g_1_x0 = subs(g_1, {D, H}, x_0);
h_1_x0 = double(subs(h_1, {D, H}, x_0));

c = gradient(f);
c_0 = double(subs(c, {D, H}, x_0));

h_1_d = gradient(h_1);
h_1_d_0 = subs(h_1_d, {D, H}, x_0);

g_1_d = gradient(g_1);
g_1_d_0 = subs(g_1_d, {D, H}, x_0);


A_T = [1/20 1/10; -1 0; 0 -1];
b = [0; 4; 8];
N_T = [8*pi/75 2*pi/75];
e = 0.3298;
lb = [-2; -4];
ub = [2; 4];
d0 = [0; 0];

d_0 = linprog(c_0, A_T, b, N_T, e, lb, ub, d0);
d_0_mag = norm(d_0);

