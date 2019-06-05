%%
clear all
syms x2 x1 v
f=(x1 - 1)^2 + (x2 - 1)^2+v*(x1+x2-4)
deriv1=diff(f,x1)
deriv2=diff(f,x2)
derivv=diff(f,v)