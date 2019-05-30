% Optimization course, Aalborg University, by Erik Lund & Henrik Clemmensen Pedersen
% Graphical solution for Arora Exercise 4.67

% Clear variables, screen and figures
% 'clear all' clears everything but decreases performance, so only 'clear' is used
clear; clc; close all;

[x] = Exer4_67_func()  % Get the solution

[x1,x2] = meshgrid(-5:0.05:3, -5:0.05:2); % % Create a grid 
% Compute the functions for the minimization problem
f = (x1 + 2).^2 + (x2 + 2).^2; % Important: element-by-element operation indicated by "dot": .
g1 = -x1 - x2 + 2;


cla reset                     % Initialization statements; these do not need to end by a semicolon
axis auto                     % Minimum and maximum values for axes are determined automatically
xlabel('x_1'), ylabel('x_2')  % Specifies labels for x- and y-axes
title ('Arora exercise 4.67') % Display a title for the problem
hold on                       % Retains the current plot and axes properties for all subsequent plots

% Use the "contour" command to plot cost and constraint functions
cv1 = [0 0];                 % Specifies two equal contour values
const1 = contour(x1,x2,g1,cv1,'k', 'linewidth',2);  % Plots the specified contours of g1; k = black color
text(2.2,2.1,'g_1')          % Writes g1 at the location (2.2,2.1)

% const2 = contour(x1,x2,g2,cv1,'k', 'linewidth',2);  
% text(1.75,-0.5,'g_2')        % Writes g2 at the location (1.75,-0.5)

text(2.2,0.5,'Feasible Region')

v = [0, 0.25, 0.5, 1, 2, 4, 8];       % Contour levels
[fs, fh] = contour(x1,x2,f,v,'r');    % 'r' specifies red lines for cost function contours
clabel(fs, fh)                        % Automatically puts the contour value on the graph

% We draw a circle at the optimum point (x(1),x(2)).
plot(x(1),x(2),'bo','linewidth',2);

% Finally, we plot the constraint functions minus a small number in order
% to indicate the feasible domain clearly on the plot - add shadings
contour(x1,x2,g1-0.06,cv1,'Color',[.8 .8 .8], 'linewidth',3);  % Plots g1-0.06 in order to indicate feasible space
% contour(x1,x2,g2-0.03,cv1,'Color',[.8 .8 .8], 'linewidth',3);  % Plots g2-0.03 in order to indicate feasible space

% Replot the optimum (the shadings hide the point...)
plot(x(1),x(2),'bo','linewidth',2);

% Add legends to the plot
legend('g_1(x)','g_2(x)', 'f(x)', 'Optimum'); 

hold off                             % Indicates end of this plotting sequence
                                     % Subsequent plots will appear in separate windows
