%% Optimisation - Lecture 2

%% Exercise 4.8

syms x1_star x2_star
f = 10*x1_star^4 - 20*x1_star^2*x2_star + 10*x2_star^2 + x1_star^2 - 2*x1_star + 5;                % The equation

x_star = [1 1];
c = gradient(f);                 % Determining the gradient c
c_0 = subs(c, {x1_star, x2_star}, x_star);

H = hessian(f);
H_x = subs(H, {x1_star, x2_star}, x_star);
f_x_star = subs(f, {x1_star, x2_star}, x_star);

syms x1 x2
d = [x1 - 1; x2 - 1];

f_taylor = f_x_star + transpose(c_0)*d + 0.5*transpose(d)*H_x*d;
simplify(f_taylor)

x = [1.2 0.8];
f_x = double(subs(f, {x1_star, x2_star}, x));

f_taylor_x = double(subs(f_taylor, {x1, x2}, x));

%% Exercise 4.10
P = [2 -5; 0 2];

A = 2* 0.5 * (P + transpose(P));
lambda = eig(A);

%% Exercise 4.22
syms x1 x2
f = 3*x1^2 + 2*x1*x2 + 2*x2^2 + 7;

c = gradient(f);

f_dx1 = diff(f, x1);
f_dx2 = diff(f, x2);

eqs = [f_dx1 == 0, f_dx2 == 0];
[solx1, solx2] = solve(eqs, [x1 x2]);

H = hessian(f);
lambda = double(eig(H))

%% Exercise 4.45

syms x1 x2 v
f_x = (x1 - 2)^2 + (x2 + 1)^2;
h_x = 2*x1 + 3*x2 - 4;

L = f_x + v * h_x;
L_dx1 = diff(L, x1);
L_dx2 = diff(L, x2);
L_dv = diff(L, v);

eqs = [L_dx1 == 0, L_dx2 == 0, L_dv == 0];
[solx1, solx2, solv] = solve(eqs, [x1 x2 v]);

f_x_sol = double(subs(f_x, {x1, x2}, {solx1, solx2}));

%% Exercise 4.67

syms x1 x2 u1 u2 s1 s2

f = (x1-1)^2 + (x2-1)^2;
g1 = x1+x2-4;
g2 = 2-x1;

L = f + u1*(g1 + s1^2) + u2*(g2 + s2^2);

L_dx1 = diff(L, x1);
L_dx2 = diff(L, x2);
L_du1 = diff(L, u1);
L_du2 = diff(L, u2);
L_ds1 = diff(L, s1);
L_ds2 = diff(L, s2);

eqs = [L_dx1 == 0, L_dx2 == 0, L_du1 == 0, L_du2 == 0, L_ds1 == 0, L_ds2 == 0];
[solx1, solx2, solu1, solu2, sols1, sols2] = solve(eqs, [x1 x2 u1 u2 s1 s2])