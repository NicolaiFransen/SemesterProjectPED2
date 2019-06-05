% Optimization course, Aalborg University, by Erik Lund & Henrik Clemmensen Pedersen
% Graphical solution for Arora Exercise 4.45 (similar to Exercise 4.46 in Arora (2004))

% Clear variables, screen and figures
% 'clear all' clears everything but decreases performance, so only 'clear' is used
clear; clc; close all;

[x] = Exer4_45_func2016()  % Get the solution

[x1,x2] = meshgrid(0.0:0.05:6, -5:0.05:2.0); % % Create a grid 
% Compute the functions for the minimization problem
f = (3-x1).^2 + (x2 + 2).^2 % Important: element-by-element operation indicated by "dot": .
h1 = -x1 -x2 +2;

cla reset                     % Initialization statements; these do not need to end by a semicolon
axis auto                     % Minimum and maximum values for axes are determined automatically
xlabel('x_1'), ylabel('x_2')  % Specifies labels for x- and y-axes
title ('Arora exercise 4.45') % Display a title for the problem
hold on                       % Retains the current plot and axes properties for all subsequent plots

% Use the "contour" command to plot cost and constraint functions
cv1 = [0 0];                 % Specifies two equal contour values
const1 = contour(x1,x2,h1,cv1,'k', 'linewidth',2);  % Plots the specified contours of h1; k = black color
text(1.3,0.65,'h_1');        % Writes h1 at the location (1.3,0.65)

v = [0, 0.25, 0.5, 1, 2, 4, 8];       % Contour levels
[fs, fh] = contour(x1,x2,f,v,'r');    % 'r' specifies red lines for cost function contours
clabel(fs, fh)                        % Automatically puts the contour value on the graph

% We draw a circle at the optimum point (x(1),x(2)).
plot(x(1),x(2),'bo','linewidth',2);

% Add legends to the plot
legend('h_1(x)','f(x)', 'Optimum'); 

hold off                             % Indicates end of this plotting sequence
                                     % Subsequent plots will appear in separate windows
