% Exercises Arora chapter 10 for Lecture 3

clear; clc; close all;

%% Ex. 10.4 Determine if the the direction d = (-3, 10, -12) is that of descent
clear; clc; close all;
syms x1 x2 x3

f = x1^2 + 2*x2^2 + 2*x3^2 + 2*x1*x2 + 2*x2*x3

g_f = gradient(f)
d = [-3; 10; -12] 

%Substitute in the gradient function the point x=(1,2,3)
x1=1;
x2=2;
x3=3;
g_f_sol = subs(g_f)

condition = transpose(g_f_sol) * d  % as the product is negative (-50) it's a direction of descent. 

%% Ex. 10.22 Derive f(alpha) and solve for optimal step size using analytical approach (f'(alpha)=0)
clear; clc; close all;
syms x1 x2 alpha

f = (x1-2)^2 + (x2 - 1)^2 

x_0 = [4; 4]
d_0 = [-4; -6]

x = x_0 + alpha*d_0
x1 = x(1)
x2 = x(2)
f_alpha = subs(f)  %f(alpha)

%The optimal size is found as f'(alpha=0):
g_f_alpha = gradient(f_alpha)
solve(g_f_alpha)  %Optimal step size -> alpha=0.5

% Ex.10.32 is to find the initial interval of uncertainty for the equal-interval search with delta = 0.05 for Ex.10.22:

alpha=0; %initialize search 
f_old = subs(f_alpha)
delta = 0.05; 
alpha = alpha + delta; 
f_new = subs(f_alpha)

% Continue until function increases: 
 while f_new < f_old
     f_old = f_new;
     alpha = alpha + delta;
     f_new = subs(f_alpha)
 end; 
 
 %Save upper and lowe values of the initial interval of uncertainty 
 alpha_u = alpha %upper limit 
 alpha_l = alpha - 2*delta %lower limit
     
%% Ex. 10.42 Calculate the intial interval of uncertainty using the Golden section search with delta = 0.05.
%Complete two iterations of the phase II of the method.  
clear; clc; close all;
%Teacher's code 
epsilonGS = 0.001; % Convergence criteria in golden section (GS) search
delta = 0.05;      % Initial value for delta in golden section search
nMaxGSIter = 100;  % Maximum number of iterations to use in golden section search
global nFuncEval;  % We count the number of function evaluations.
nFuncEval = 0;     % It is stored as a global variable - dirty trick...

[alpha, f_alpha, iter] = GoldenSection(@Exer10_32_f_alpha, delta, epsilonGS, nMaxGSIter)



nFuncEval          % Display the number of function evaluations


%% Ex. 10.52 Complete two itrations of the steepest-descent method 
clear; clc; close all;
syms x1 x2 alpha

f = x1^2 + 2*x2^2 - 4*x1 - 2*x1*x2

%Step 1: 
x0 = [1;1]; 
k=0; 
epsilon = 0.001; 

%Step 2: 
c = gradient(f)
c0 = subs(f)

%Step 3: 
module_c = sqrt(c(1)^2 + c(2)^2) 

%Step 4: d0 = -c0
d0 = [4; -2]

%Step 5: 
x = x0 + alpha*d0
x1 = x(1)
x2 = x(2)
f_alpha = subs(f)  
f_alpha = simplify(f_alpha)

% f'(x) = 0 (can also be solved using Golden section)
deriv_f_alpha = diff(f_alpha)
alpha = solve(deriv_f_alpha)

iter = 0;
for k = 1:100 
    iter = iter+1; 
     c(:,k)=gradient(f) %Step 2
     norm_c(k) = norm(c(:,k)); %Step 3 
     
        if (norm_c(k) < epsilon) %if stop criterion has been reached:
            disp('Optimization successful')
            sprintf('Used %d iterations and %d function evaluations', k-1, nFuncEval)
          
            f_alpha
          
        end 
     d0(:,k) = -c(:,k);     % Step 4:
       
     [alpha(k), f_alpha, iter] = GoldenSection(@Exer10_52_f_alpha, delta, epsilonGS, nMaxGSIter); %Step 5 
     %Step 5 can also be done as f'(alpha)=0:
     deriv_f_alpha = diff(f_alpha)
     alpha2 = solve(deriv_f_alpha)
  % Step 6:
  x(:,k+1) = x(:,k) + alpha(k)*d(:,k);
end


%% TEACHER'S SOLUTION:
% All vectors and matrices used could also be preallocated to maximum size 
% in order to increase computational efficiency. 
global x;
global d;
global IterNo;
global nFuncEval;

epsilonGS = 0.001; % Convergence criteria in golden section (GS) search
delta = 0.05;      % Initial value for delta in golden section search
nMaxGSIter = 100;  % Maximum number of iterations to use in golden section search
epsilon = 0.001;   % Convergence criteria for the norm of the gradient of f
nMaxIter = 1000;   % Maximum number of outer iterations
nFuncEval = 0;     % We count the number of function evaluations
% Step 1:
x(:,1) = [1; 1];  % Initial design point
% Loop for each k design iteration
for k = 1:nMaxIter
  IterNo = k; % We store the current iteration number in IterNo
  % Step 2:
  c(:,k) = Exer10_52_grad_f_x(x(:,k));
  % Step 3:
  norm_c(k) = norm(c(:,k));
  if (norm_c(k) < epsilon)
    disp('Optimization successful')
    sprintf('Used %d iterations and %d function evaluations', k-1, nFuncEval)
    f_alpha
    x(:,k)
    break;
  end
  % Step 4:
  d(:,k) = -c(:,k);
  % Step 5:
  [alpha(k), f_alpha] = GoldenSection(@Exer10_52_f_alpha, delta, epsilonGS, nMaxGSIter);
  % Step 6:
  x(:,k+1) = x(:,k) + alpha(k)*d(:,k);
end
