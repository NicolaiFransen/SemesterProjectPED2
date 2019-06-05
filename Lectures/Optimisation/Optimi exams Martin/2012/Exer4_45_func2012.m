% Optimization course, Aalborg University, by Erik Lund & Henrik Clemmensen Pedersen
% Solution for Arora Exercise 4.45 (similar to Exercise 4.46 in Arora (2004)).
% Made as function to be called from Exer4_45_Graph_code.m

function x = Exer4_45()

% Initial guess for {x1, x2, v}^T:
x0 = [10 10 10]';
% Increase maximum number of function evaluations in fsolve
MyOptions=optimset('MaxFunEvals',1000);
% Solve the KKT conditions defined in function KKTSystem:
x = fsolve(@KKTSystem, x0, MyOptions);
% Write the value of the objective function
f = (x(1) - 1)^2 + (x(2) - 1)^2 

% The function KKTSystem returns current values of the KKT system
function c = KKTSystem(x)
  % Input: x(1)=x1, x(2)=x2, and x(3)=v
  % Output: the KKT system (gradients of Lagrangian L)

  c(1) = (x(1)-4)+x(2);
  c(2) = 2*(x(1)-1)+x(3);
  c(3) = 2*x(2)+x(3)-2;
end

end
