
clc
clear all
close all
x1=[10 8 6 5]
x2=[10 12 14 15]
f1=(x1-5).^2+(x2-15).^2
f2=(x1-15).^2+(x2-5).^2
plot(f1,f2)

% S = solve(eqn,var)

% syms x1 x2
% f1=(x1-5).^2+(x2-15).^2 == 49;
% f2=(x1-15).^2+(x2-5).^2 == 49;
% 
% sol = solve([f1, f2], [x1, x2]);
% x1Sol = sol.x1
% x2Sol = sol.x2
%%
% Optimization course, Aalborg University, by Erik Lund & Henrik Clemmensen Pedersen
% Solution for Arora Exercise 4.45 (similar to Exercise 4.46 in Arora (2004)).

% Clear variables, screen and figures
% 'clear all' clears everything but decreases performance, so only 'clear' is used
clear; clc; close all;

% Initial guess for {x1, x2, v}^T:
x0 = [10 10 10]';
% Increase maximum number of function evaluations in fsolve
MyOptions=optimset('MaxFunEvals',1000);
% Solve the KKT conditions defined in function KKTSystem:
x = fsolve(@KKTSystem, x0, MyOptions)
% Write the value of the objective function
f = 2*((x(1) - 5)^2 + (x(2) - 15)^2)+(x(1) - 15)^2 + (x(2) - 5)^2

%%
%f
f=@(x,y) 3*x^2+3*y^2-50*x-70*y+750;
fcontour(f)

% The function KKTSystem returns current values of the KKT system
function c = KKTSystem(x)
  % Input: x(1)=x1, x(2)=x2, and x(3)=v
  % Output: the KKT system (gradients of Lagrangian L)

  c(1) = 6*(x(1))+x(3)-50;
  c(2) = 6*(x(2))-70;
  c(3) = x(1)-10;
end


