%Exam 2018
clc
clear all
close all
syms x1 x2 u1 s1
f=(x1+2)^2+(x2+2)^2
g=2-x1-x2
L=f+u1*(g+s1^2)
derivX1=diff(L,x1)
derivX2=diff(L,x2)
derivu1=diff(L,u1)
derivs1=diff(L,s1)

syms x1 x2
f1=2*x1+4-u1;
f2=2*x2+4-u1;
f3=2-x1-x2+s1^2;
f4=2*u1*s1;

sol = solve([f1, f2, f3, f4], [x1, x2, u1,s1]);
x1Sol = sol.x1
x2Sol = sol.x2
u1Sol = sol.u1
s1Sol = sol.s1