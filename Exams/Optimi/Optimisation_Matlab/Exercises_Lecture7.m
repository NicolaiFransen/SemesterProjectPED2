%% Optimisation - Lecture 7

%% Exercise 12.51

syms d1 d2 s1 s2 s3 v u1 u2 u3
g1 = d1/20 + d2/10 + s1^2;
g2 = -d1 - 4 + s2^2;
g3 = -d2 - 8 + s3^2;
h1 = 8*pi/75*d1 + 2*pi/75*d2 - (75-16*pi)/75;
f = 15079.6*d1 + 5026.6*d2 + 0.5*(d1^2+d2^2);

L = f + v*h1 + u1*g1 + u2*g2 + u3*g3;

L_d_d1 = diff(L, d1);
L_d_d2 = diff(L, d2);
L_d_v = diff(L, v);
L_d_u1 = diff(L, u1);
L_d_u2 = diff(L, u2);
L_d_u3 = diff(L, u3);

d_2 = solve(subs(L_d_u3, s3, 0), d2);
d_1 = double(solve(subs(L_d_v, d2, d_2)));

u_1 = 0;
u_2 = 0;

v_1 = double(solve(subs(L_d_d1, {d1, u1, u2}, {d_1, u_1, u_2})));
u_3 = double(solve(subs(L_d_d2, {d2, u1, v}, {d_2, u_1, v_1})));

%% Exercise 13.11

gamma = 0.5;
x_0 = [4 8];

% From the exercise above:
syms D H
f = 400*(pi* (D^2/2) + pi*D*H);
h_1 = pi*D^2/600 * H - 1;
g_1 = H/10 + D/20 - 1;

f_0 = 16000*pi;
d_0 = [2.9842 -8];

u = [0 0 1248];
v = -45008.9;

R = sum(abs(v)) + sum(u);
beta_0 = gamma * norm(d_0)^2;

V_0 = 0.3298;

Phi_0 = f_0 + R*V_0;

t_0 = 1;
x_1_0 = x_0 + t_0*d_0;

f_1_x1 = double(subs(f, {D, H}, x_1_0));
g_1_x1 = double(subs(g_1, {D, H}, x_1_0));
h_1_x1 = double(subs(h_1, {D, H}, x_1_0));

V_1_0 = 1;
Phi_1_0 = f_1_x1 + R*V_1_0;

Phi_1_0 + t_0*beta_0;

t_1 = 0.5;
x_1_1 = x_0 + t_1*d_0;

f_1_1 = double(subs(f, {D, H}, x_1_1));
g_1_1 = double(subs(g_1, {D, H}, x_1_1));
h_1_1 = double(subs(h_1, {D, H}, x_1_1));

V_1_1 = 0.3683;
Phi_1_1 = f_1_1 + R*V_1_1;

Phi_1_1 + t_1*beta_0;


%% Branch and bound method
syms x1 x2
f = -3*x1 - 8*x2;
g_1 = -0.5*x1 + x2 - 6;
g_2 = 2*x1 + x2 -20;
g_3 = 4*x1 - x2 - 20;

x_c = [5.6 8.8];
f_c = double(subs(f, {x1, x2}, x_c));

% First iteration:
x_1_1 = [5 8.5];        % Trying x1 = 5, and adapting x2 to be inside the constraints.
f_1_1 = double(subs(f, {x1, x2}, x_1_1));

x_1_2 = [6 8];          % Trying x1 = 6
f_1_2 = double(subs(f, {x1, x2}, x_1_2));

% Second iteration:
x_2_1 = [5 8];        % Trying x2 = 8, and adapting x2 to be inside the constraints.
f_2_1 = double(subs(f, {x1, x2}, x_2_1))

x_2_2 = [5 9];          % Trying x2 = 9, This is outside the constraints, so not relevant.
f_2_2 = double(subs(f, {x1, x2}, x_2_2));