
%% Exercise 10.67

x_0 = [1, 1];
syms x1 x2 alpha
f = x1^2 + 2*x2^2 - 4*x1 - 2*x1*x2;                % The equation

c = gradient(f);                 % Determining the gradient c
c_0 = subs(c, {x1, x2}, x_0);
c_0_mag = norm(c_0);
d = -c_0;

x_new = x_0 + alpha*double(transpose(d));
f_alpha = subs(f, {x1, x2}, x_new);

df_alpha = diff(f_alpha, alpha);
alpha_0 = solve(df_alpha, alpha);

x_1 = x_0 + alpha_0*double(transpose(d));

% Next iteration:
% Step 2:
c_1 = subs(c, {x1, x2}, x_1);
f_x1 = subs(f, {x1, x2}, x_1);

% Step 3
c_1_mag = norm(c_1);

% Step 4
beta_1 = (double(c_1_mag/c_0_mag))^2;
d_1 = -double(transpose(c_1)) + beta_1*double(transpose(d));

% Step 5
x_new = x_1 + alpha*d_1;
f_alpha_1 = subs(f, {x1, x2}, x_new)

df_alpha = diff(f_alpha_1, alpha);
alpha_1 = solve(df_alpha, alpha);

% Step 6
x_2 = double(x_1 + alpha_1*d_1);

f_x2 = subs(f, {x1, x2}, x_2);


%% Exercise 11.10
% Using the modified newtons method
syms x1 x2 alpha
f = x1^2 + 2*x2^2 - 4*x1 - 2*x1*x2;                % The equation

% Step 1
x_0 = [1, 1];

% Step 2
c = gradient(f);                 % Determining the gradient c
c_0 = subs(c, {x1, x2}, x_0);
c_0_mag = double(norm(c_0))

% Step 3
H = hessian(f)

% Step 4
d_0 = -H^-1 * c_0;

% Step 5
x_1 = transpose(x_0) + alpha*d_0;
f_x1 = simplify(subs(f, {x1, x2}, transpose(x_1)));

%% Exercise 11.22
syms x1 x2 alpha
f = x1^2 + 2*x2^2 - 4*x1 - 2*x1*x2;                % The equation

% Step 1
x_0 = [1 1];
A_0 = [1 0; 0 1];
c = gradient(f);                 % Determining the gradient c
c_0 = subs(c, {x1, x2}, x_0);

% Step 2
c_0_mag = double(norm(c_0));

% Step 3
d_0 = -c_0;

% Step 4
x_1 = transpose(x_0) + alpha*d_0;
f_alpha = simplify(subs(f, {x1, x2}, transpose(x_1)));

df_alpha = diff(f_alpha, alpha);
alpha_0 = solve(df_alpha, alpha);

% Step 5
x_1 = x_0 + alpha_0*double(transpose(d_0));

% Step 6
s_0 = alpha_0 * d_0;
c_1 = subs(c, {x1, x2}, x_1);
y_0 = c_1 - c_0;
z_0 = y_0;

B_0 = double(s_0*transpose(s_0) / dot(s_0, y_0));
C_0 = -double(z_0*transpose(z_0) / dot(y_0, z_0));

A_1 = A_0 + B_0 + C_0;

% Iteration 2:
% Step 2
c_1_mag = double(norm(c_1))

% Step 3
d_1 = double(-A_1*c_1);
% 
% % Step 4
x_2 = transpose(x_1) + alpha*d_1;
f_alpha = simplify(subs(f, {x1, x2}, transpose(x_2)))

df_alpha = diff(f_alpha, alpha);
alpha_1 = solve(df_alpha, alpha);

% Step 5
x_2 = x_1 + alpha_1*double(transpose(d_1));

% Step 6
s_1 = alpha_1 * d_1;
c_2 = subs(c, {x1, x2}, x_2);
y_1 = c_2 - c_1;
z_1 = A_1*y_1;

B_1 = double(s_1*transpose(s_1) / dot(s_1, y_1))
C_1 = -double(z_1*transpose(z_1) / dot(y_1, z_1))

A_2 = A_1 + B_1 + C_1;