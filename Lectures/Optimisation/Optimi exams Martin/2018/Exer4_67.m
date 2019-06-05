% Optimization course, Aalborg University, by Erik Lund & Henrik Clemmensen Pedersen
% Solution for Arora Exercise 4.67

% Clear variables, screen and figures
% 'clear all' clears everything but decreases performance, so only 'clear' is used
clear; clc; close all;

% Initial guess for {x1, x2, u1, u2, s1, s2}^T:
x0 = [1 1 1 1 1 1]';
% Increase maximum number of function evaluations in fsolve
MyOptions=optimset('MaxFunEvals',1000);
% Solve the KKT conditions defined in function KKTSystem:
x = fsolve(@KKTSystem, x0, MyOptions)
% Write the value of the objective function
f = (x(1) + 2)^2 + (x(2) + 2)^2

% The function KKTSystem returns current values of the KKT system
function c = KKTSystem(x)
  % Input: x(1)=x1, x(2)=x2, x(3)=u1, x(4)=u2, x(5)=s1, and x(6)=s2
  % Output: the KKT system (gradients of Lagrangian L)

  c(1) = 2*x(1) +4 -x(3);
  c(2) = 2*x(2) +4 -x(3);
  c(3) = -x(1) -x(2) +2 +x(4)^2;
  c(4) = 2*x(3)*x(4);

end