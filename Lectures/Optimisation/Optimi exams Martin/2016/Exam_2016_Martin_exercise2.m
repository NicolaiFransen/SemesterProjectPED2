clc
clear all 
close all
syms x1 x2
f=1.5*x1^2+x1^2-6*x1+x1*x2+0.5*x2^2+3;
c=gradient(f)
h=hessian(f)
invh=inv(h)
eig(h)
c=[0;2]
d=-1*(invh)*c