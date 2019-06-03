%% Optimisation - Lecture 5

%% Exercise 8.55

% Cost coefficient vector
c = [-1 ; -2];

% Equality coefficients
Ah = [0 0];
bh = [0];

% Inequality coefficients
A = [-1 3; 1 1; 1 -1; -1 -3; -1 0; 0 -1];
b = [10; 6; 2; -6; 0; 0];

% Setting boundaries
lb = [0 0];
ub = [inf inf];
x0 = [0 0];

% Solve by using linprog
[x_opt, fval] = linprog(c, A, b, Ah, bh, lb, ub, x0);