clc
clear all
close all
x1=1
x2=1
f=10*x1^4-20*x1^2*x2+10*x2^2+x1^2-2*x1+5

%%
clear all
syms x2
syms x1

f=10*x1^4-20*x1^2*x2+10*x2^2+x1^2-2*x1+5
c=gradient(f,[x1,x2])


%%
clear all
syms x2
syms x1
f=10*x1^4-20*x1^2*x2+10*x2^2+x1^2-2*x1+5
H=hessian(f,[x1,x2])

%%
%the exact and approximate values of f(x) are computed at x=(1.2 0.8)

f=4+[0 0]*[1.2-1; 0.8-1]+0.5*[1.2-1 0.8-1]*[82 -40;-40 20]*[1.2-1;0.8-1]


%%
%exercise 4.10 determine the nature of the following quadratic forms
clear all
syms x2
syms x1
f=2*x1^2+2*x2^2-5*x1*x2
H=hessian(f,[x1,x2])
lambda=eig(H)
%%
%exercise 4.22 determine the nature of the following quadratic forms
clear all
syms x2
syms x1
f=3*x1^2+2*x1*x2+2*x2^2+7
c=gradient(f,[x1,x2])
%%
%exercise 4.45
clear all
syms x2 x1 v
f=(x1-2)^2+(x2+1)^2+v*(2*x1+3*x2-4)
deriv1=diff(f,x1)
deriv2=diff(f,x2)
derivv=diff(f,v)
%%
%exercise 4.67
clear all
syms x2 x1 u1 u2 s1 s2
f=(x1-1)^2+(x2-1)^2+u1*(x1+x2-4+s1^2)+u2*(2-x1+s2^2)
deriv1=diff(f,x1)
deriv2=diff(f,x2)
derivs1=diff(f,s1)
derivs2=diff(f,s2)
derivu1=diff(f,u1)
derivu2=diff(f,u2)
%%
%exercise 10.4
clc
clear all
close all
syms x2 x1 x3
f=x1^2+2*x2^2+2*x3^2+2*x1*x2+2*x2*x3
c=gradient(f,[x1,x2,x3])
descend_Cond=[6 16 16]*[-3;10;-12]

%%
%exercise 10.52
clc
clear all
close all
syms x2 x1 
f=x1^2+2*x2^2-4*x1-2*x1*x2
c=gradient(f,[x1,x2])
%% 
%10.52....
syms a
f=simplify((1+4*a)^2+2*(1-2*a)^2-4*(1+4*a)-2*(1+4*a)*(1-2*a))
%% 
%10.52....
x1=2
x2=0.5
f=x1^2+2*x2^2-4*x1-2*x1*x2

%% 
%10.52....
syms a
f=simplify((2+a)^2+2*(0.5+2*a)^2-4*(2+a)-2*(2+a)*(0.5+2*a))
x=[2 ;0.5]+0.5*[1 ; 2]
%%
%10.68
clear all
syms x2
syms x1
f=x1^2+2*x2^2-4*x1-2*x1*x2
c=gradient(f,[x1,x2])
%% 
%10.52....
clc
clear all
syms a
f=simplify((2+a)^2+2*(0.5+2*a)^2-4*(2+a)-2*(2+a)*(0.5+2*a))
x=[1 ; 1]+0.25*[4 ; -2]

%% 
%11.9....
clc
clear all
syms x2
syms x1
f=x1^2+2*x2^2-4*x1-2*x1*x2
h=hessian(f,[x1,x2])
eigen=simplify(eig(h))
d=-h^-1*[-4;2]
%%
%11.9....

syms a
f=simplify((1+3*a)^2+2*(1+a)^2-4*(1+3*a)-2*(1+3*a)*(1+a))
%%
[1 1]*[1 0;0 1]
%%
%11.9
clc
clear all
B=([1;-0.5]*[1;-0.5]')/([1;-0.5]'*[3;-4])
C=(-[3;-4]*[3;-4]')/([3;-4]'*[3;-4])
d1=-[0.84 0.38; 0.38 0.41]*[-1;-2]