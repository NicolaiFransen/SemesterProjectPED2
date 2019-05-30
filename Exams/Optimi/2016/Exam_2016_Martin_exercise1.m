clc
clear all
close all
syms x1 x2 v
f=(3-x1)^2+(x2+2)^2
h=-x1-x2+2
L=f+v*(h)
ALx1=diff(L,x1)
ALx2=diff(L,x2)
ALv=diff(L,v)
%%
syms x1 x2
f1=2*x1-v-6;
f2=2*x2+4-v;
f3=-x1-x2+2

sol = solve([f1, f2, f3], [x1, x2, v]);
x1Sol = sol.x1
x2Sol = sol.x2
vSol = sol.v
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
f = (3-x(1))^2 + (x(2) + 2)^2

% The function KKTSystem returns current values of the KKT system
function c = KKTSystem(x)
  % Input: x(1)=x1, x(2)=x2, and x(3)=v
  % Output: the KKT system (gradients of Lagrangian L)

  c(1) = 2*x(1)-6-x(3);
  c(2) = 2*(x(2)+2)-x(3);
  c(3) = -x(1)-x(2)+2;
end
