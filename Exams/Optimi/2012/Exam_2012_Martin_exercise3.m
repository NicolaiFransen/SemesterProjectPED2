clc
clear all 
close all
syms x1 x2 d1 d2
f=-x1^2+3*x2^2+x1*x2-3;%ecuación de partida 
g=gradient(f)
g1=1/x1-2*x2
g1_grad=gradient(g1)
g2=x1-2*x2^3
g2_grad=gradient(g2)
g3=-x1+0*x2
g3_grad=gradient(g3)
g4=-x2+0*x1
g4_grad=gradient(g4)
A=[-1 1 -1 0;-2 -6 0 -1]
Atras=A'
d=[d1;d2]
produc=Atras*d
