%%
%Exercise2 a)
clc
clear all
close all
%function
syms x1 x2 a
f=(1-x1)^2+(x2-2)^2+2*x1;%ecuación de partida  
%gradient
c=gradient(f,[x1,x2])
%f(alfa)
f_alfa=(1-(3-6*a))^2+((1+2*a)-2)^2+2*(3-6*a)
f_alfa=simplify(f_alfa)
f_alfa_deriv=diff(f_alfa)
alfa=solve(f_alfa_deriv)
%new design
X0=[3;1]
d=[-6;2]
X1=X0+alfa*d
%%
%Exercise2 b)
clc
clear all
close all
syms x1 x2 
f=(1-x1)^2+(x2-2)^2+2*x1;%ecuación de partida  
h=hessian(f)
lambda=eig(h)
c=[6;-2]
d=-h^(-1)*c
c'*d