%%
%Exercise2 a)
clc
clear all
close all
%function
syms x1 x2 a
f=(x1-1)^2+2*x2^2;%ecuación de partida  
%gradient
c=gradient(f,[x1,x2])
%f(alfa)
f_alfa=((3-4*a)-1)^2+2*((1-4*a))^2
f_alfa=simplify(f_alfa)
f_alfa_deriv=diff(f_alfa)
alfa=solve(f_alfa_deriv)

%new design
X0=[3;1]
d=[-4;-4]
X1=X0+alfa*d

%%
%Exercise2 b)
clc
clear all
close all
syms x1 x2 
f=(x1-1)^2+2*x2^2;%ecuación de partida 
h=hessian(f)
invH=inv(h)
lambda=eig(h)
c=[4;4]
d=-h^(-1)*c
c'*d



