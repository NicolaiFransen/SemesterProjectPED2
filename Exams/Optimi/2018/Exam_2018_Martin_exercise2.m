%%
%Exercise2 a)
clc
clear all
close all
%function

syms x1 x2 a
f=5*(x1^2-x2)+(x2-1)^2-2*x1+3 %ecuación de partida  

%gradient
c=gradient(f,[x1,x2])

%f(alfa)
f_alfa=5*((3-28*a)^2-(4-a))+(4-a-1)^2-2*(3-28*a)+3
f_alfa=simplify(f_alfa)

f_alfa_deriv=diff(f_alfa)

alfa=solve(f_alfa_deriv)

%new design
X0=[3;4]
d=[-28;-1]
X1=X0+alfa*d
%%
x1=0.2
x2=3.9
f=5*(x1^2-x2)+(x2-1)^2-2*x1+3 %ecuación de partida
%%
%Exercise2 b)
clc
clear all
close all
syms x1 x2 
f=5*(x1^2-x2)+(x2-1)^2-2*x1+3;%ecuación de partida  
h=hessian(f)
lambda=eig(h)
c=[28;1]
d=-h^(-1)*c
c'*d

%%
clc
clear all
syms x1 x2
f=10*x1^4+2*x2^2-2*x2*x1^2-5*x1-x2
g1=x2-10;
g2=2*x1+4*x2-10;
g3=x1-x2-1;
f_grad=gradient(f)
g1_grad=gradient(g1)
g2_grad=gradient(g2)
g3_grad=gradient(g3)
%%
syms D H
f=400*((pi*D^2)/2+(pi*D*H))
f_deriv=gradient(f)
%%
%exercise 4
clc
clear all
close all

%%
x1=[2 10]
x2=[8 4]
f1=(x1-2).^2+(x2-8).^2+6
f2=(x1-10).^2+(x2-4).^2+2
%%
syms x1 x2
w1=2
w2=1
f1=(x1-2)^2+(x2-8)^2+6
f2=(x1-10)^2+(x2-4)^2+2
u=w1*f1+w2*f2
u=simplify(u)
derivx1=diff(u,x1)
derivx2=diff(u,x2)
%%
clear all
x1=14/3
x2=20/3
w1=2
w2=1
f1=(x1-2)^2+(x2-8)^2+6
f2=(x1-10)^2+(x2-4)^2+2
u=w1*f1+w2*f2
%%
clc
clear all
x1=5
x2=6.96
f=2*x1-5*x2

%%
syms x1 x2 t
f1=exp(-(t/75000)^1.6)+exp(-0.00001*t)==0.9

sol = solve(f1)

%%
syms x
a=2*x+1==90
sol = solve(a)

