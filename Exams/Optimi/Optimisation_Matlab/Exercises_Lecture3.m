
%% Lecture 3

%% Example 10.4
x = [1, 0];
syms x1 x2
f = x1^2 + +x2^2 - 2*x1*x2;
c = gradient(f);

c_mag = subs(c, {x1, x2}, x); 


%% Exercise 10.4

d = [-3, 10, -12];
x = [1, 2, 3];
syms x1 x2 x3
f = x1^2 + 2*x2^2 + 2*x3^2 + 2*x1*x2 + 2*x2*x3;
c = gradient(f);                    % Calculates the gradient of the function

c_num = subs(c, {x1, x2, x3}, x);   % Substitute the initial starting point

sum(transpose(c_num).*d)            % Taking the dot product between the gradient and the direction

% As this is (-50<0) negative the direction is of decent 

%% Exercise 10.22
d = [-4, -6];
x = [4, 4];

syms x1 x2 alpha1
f = (x1-2)^2 + (x2-1)^2;
c = gradient(f);

c_num = subs(c, {x1, x2}, x);   % Substitute the initial starting point
sum(transpose(c_num).*d)            % Taking the dot product between the gradient and the direction
% As this is (-52<0) negative the direction is of decent 

x_new = x + alpha1*d;
f_1 = subs(f, {x1, x2}, x_new);

df_new = diff(f_1, alpha1);
alpha = solve(df_new, alpha1);

x_1 = x + alpha*d;


%% Exercise 10.32

alpha = 0;      % Start at alpha = 0
delta = 0.05;
f_old = subs(f_1, alpha1, alpha);
alpha = alpha + delta;

f_new = subs(f_1, alpha1, alpha);

while f_new < f_old        % We are in this while until we find a minimum. And then it takes one extra step.
   f_old = f_new;
   alpha = alpha + delta;
   f_new = subs(f_1, alpha1, alpha); 
end

% This means that the upper limit is what we found and the alpha, and the
% lower limit is 2*delta before the upper limit:
alpha_u = alpha
alpha_l = alpha - 2*delta

%% Exercise 10.42

i = 1;
delta = 0.05;
alpha(i) = delta;      % Start at alpha = 0
f_old = subs(f_1, alpha1, alpha(i));

i = i + 1;
q = 1;
alpha(i) = alpha + 1.618*delta;
f_new = subs(f_1, alpha1, alpha(i));

while f_new < f_old        % We are in this while until we find a minimum. And then it takes one extra step.
   f_old = f_new;
   q = q + 1;
   i = i + 1;
   alpha(i) = alpha(i-1) + (1.618^q)*delta;
   f_new = subs(f_1, alpha1, alpha(i)); 
end

% This means that the upper limit is what we found and the alpha, and the
% lower limit is 2*delta before the upper limit:
alpha_u = double(alpha(i))
alpha_l = double(alpha(i-2))% - (1.618^(q-2))*delta)

% Phase II
I = alpha_u - alpha_l;
iteration_numbers = 2;

alpha_a = alpha_l + 0.382*I;
alpha_b = alpha_l + 0.618*I;

f_a = subs(f_1, alpha1, alpha_a);
f_b = subs(f_1, alpha1, alpha_b);
exit = 0;
for j = 1:iteration_numbers-1
while f_a == f_b
    alpha_l = alpha_a;
    alpha_u = alpha_b;
        
    alpha_a = alpha_l + 0.382*I;
    alpha_b = alpha_l + 0.618*I;

    f_a = subs(f_1, alpha1, alpha_a);
    f_b = subs(f_1, alpha1, alpha_b);
end
    
if f_a < f_b
    alpha_l = alpha_l;
    alpha_u = alpha_b;
    alpha_b = alpha_a;
    alpha_a = alpha_l + 0.382*(alpha_u-alpha_l);
    f_a = subs(f_1, alpha1, alpha_a);
end
if f_a > f_b
    alpha_l = alpha_a;
    alpha_u = alpha_u;
    alpha_a = alpha_b;
    alpha_b = alpha_l + 0.618*(alpha_u-alpha_l);
    f_b = subs(f_1, alpha1, alpha_b);
end

end
alpha_u
alpha_l
% I = alpha_u - alpha_l;
% if I < epsilon
%     alpha_star = (alpha_u + alpha_l)/2
        

%% Exercise 10.52
numberOfIterations = 2;

x = [1, 1];
syms x1 x2 alpha
f = x1^2 + 2*x2^2 - 4*x1 - 2*x1*x2;


for i = 1:numberOfIterations
c = subs(gradient(f), {x1, x2}, x);
d = -c;
%c_mag = norm(c); 

x_new = x + alpha*double(transpose(d));
f1 = subs(f, {x1, x2}, x_new);

df_new = diff(f1, alpha);
alpha1(i) = solve(df_new, alpha);

x = double(subs(x_new, alpha, alpha1(i)));
end


f1 = subs(f, {x1, x2}, x)