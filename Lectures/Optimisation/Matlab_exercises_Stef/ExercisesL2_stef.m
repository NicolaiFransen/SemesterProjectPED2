% Exercises Arora chapter 4 for Lecture 2

clear; clc; close all;

%% Exercise 4.8 
clear; clc; close all;

 % First define the symbolic variables used
  syms x1 x2 x1d x2d

  %The function:
  f = 10*x1^4 - 20*x1^2*x2 + 10*x2^2 + x1^2 - 2*x1 +5 
  
  %d = x-x*
  d = [x1d-x1; x2d-x2]
  
  %Gradient: 
  g_f = gradient(f,[x1 x2]) 
  
  %Hessian:
  %H_f = [diff(grad_f(1),x1) diff(grad_f(2),x1); diff(grad_f(2),x2) diff(grad_f(1),x2)]
  H_f = hessian(f, [x1 x2]) %other way much simpler
  
  % Taylor approximation:
  x1=1;
  x2=1;
  f_taylor = subs(f + transpose(g_f)* d + 0.5*transpose(d)*H_f*d)
  
  
  %Substitute the symbolic variables: x1 = 1 and x2 = 1
  x1d=1.2;
  x2d=0.8; 
  
  f_taylor_final = subs(f_taylor) % The exact value is 8.136 and the approximated is 7.64
  
  %% 4.10 determine the nature of the following quadratic form: 
  clear; clc; close all;
  syms x1 x2 
  
  f = 2*x1^2 + 2*x2^2 - 5 *x1*x2
  
  g_f = gradient(f, [x1 x2])
  h_f = hessian(f, [x1 x2])
  
  A=h_f 
  eigen_values = eig(A)  %As the eigen values are -1 and 9 then the hessian is indefinite
  
%% 4.22 Optimality conditions and stationary points. Local max, local min and inflection points 
clear; clc; close all;
syms x1 x2 
  
  f = 3*x1^2 + 2*x1*x2 + 2*x2^2 + 7
  
fsurf(f)

g_f = gradient(f, [x1 x2])
  
% First order necessary condition for local minimum --> g_f=0 
eqn1 = 6*x1 + 2*x2 == 0;
eqn2 = 2*x1 + 4*x2 == 0;
[A,B] = equationsToMatrix([eqn1, eqn2], [x1, x2])
X = linsolve(A,B)  %[x1 x2] = [0 0]

h_f = hessian(f, [x1 x2])

eigen_values = eig(h_f)  %As the eigen values are -1 and 9 then the hessian is indefinite

  
%% 4.45 Equality constrained problem. Find the optimum point using graphical method. 
% Another way of solving this exercises in the solution .m 
clear; clc; close all;
syms x1 x2 v

f = (x1 - 2).^2 + (x2 +1).^2 
h = 2*x1 + 3*x2 -4

L = f + v*h
g_L = gradient(L, [x1 x2 v])

eqn1 = 2*v + 2*x1 - 4 == 0;     %g_L(1,1)
eqn2 = 3*v + 2*x2 + 2 == 0;     %g_L(2,1)
eqn3 =  2*x1 + 3*x2 - 4 == 0;   %g_L(3,1)
[A,B] = equationsToMatrix([eqn1, eqn2, eqn3], [x1, x2, v])
X = linsolve(A,B)  %[x1 x2 v] = [2.4615 -0.3077 -0.4615]

% The candidate point and the lagrange multiplier are: 
% x1=2.4615;
% x2=-0.3077;
% v = -0.4615; 

f_min = subs(f)  %The objective function is minimized to 0.6923

%Check if the solution is indeed an optimum point by solving the problem graphically:

[x]=X
[x1,x2] = meshgrid(0.0:0.05:4.0, -2.0:0.05:2.0); % % Create a grid 

f = (x1 - 2).^2 + (x2 +1).^2 
h = 2*x1 + 3*x2 -4

cla reset                     % Initialization statements; these do not need to end by a semicolon
axis auto                     % Minimum and maximum values for axes are determined automatically
xlabel('x_1'), ylabel('x_2')  % Specifies labels for x- and y-axes
title ('Arora exercise 4.45') % Display a title for the problem
hold on                       % Retains the current plot and axes properties for all subsequent plots

% Use the "contour" command to plot cost and constraint functions
cv1 = [0 0];                 % Specifies two equal contour values
const1 = contour(x1,x2,h,cv1,'k', 'linewidth',2);  % Plots the specified contours of h1; k = black color
text(1.3,0.65,'h_1');        % Writes h1 at the location (1.3,0.65)

v = [0, 0.25, 0.5, 1, 2, 4, 8];       % Contour levels
[fs, fh] = contour(x1,x2,f,v,'r');    % 'r' specifies red lines for cost function contours
clabel(fs, fh)                        % Automatically puts the contour value on the graph

% We draw a circle at the optimum point (x(1),x(2)).
plot(X(1),X(2),'bo','linewidth',3);

% Add legends to the plot
legend('h(x)','f(x)', 'Optimum','AutoUpdate','off'); 

hold off                             % Indicates end of this plotting sequence
                                     % Subsequent plots will appear in separate windows
                                     
%% 4.67 Inequality constrained problem (KKT necessary  conditions). Find the optimum point using graphical method. 
% Another way of solving this exercises in the solution .m 
clear; clc; close all;
syms x1 x2 u1 u2 s1 s2

f = (x1 - 1)^2 + (x2 - 1)^2 
g1 = x1 + x2 - 4
g2 = 2- x1

L = f + u1*(g1 + s1^2) + u2*(g2 + s2^2)
g_L = gradient(L)

[s1 s2 u1 u2 x1 x2] = solve(g_L)
L=subs(L)       % There are 7 solutions for the Lagrange function and we need to find the minimum. It's found to be (1,2)

% eqn1 =  u1 - u2 + 2*x1 - 2 == 0;      %g_L(1,1)
% eqn2 =  u1 + 2*x2 - 2 == 0;           %g_L(2,1)
% eqn3 =  s1^2 + x1 + x2 - 4 == 0;      %g_L(3,1)
% eqn4 =  s2^2 - x1 + 2 == 0;           %g_L(4,1)
% eqn5 =  2*s1*u1 == 0;                  %g_L(5,1)
% eqn6 =  2*s2*u2 == 0;                  %g_L(6,1)

% [A,B] = equationsToMatrix([eqn1, eqn2, eqn3, eqn4, eqn5, eqn6], [x1, x2, u1, u2, s1, s2])
% X = fsolve(A,B)  %[x1 x2 v] = [2.4615 -0.3077 -0.4615]
% sol = fsolve([eqn1, eqn2, eqn3, eqn4, eqn5, eqn6], [x1, x2, u1, u2, s1, s2])

