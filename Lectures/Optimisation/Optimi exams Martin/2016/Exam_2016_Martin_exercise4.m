clc
clear all
close all
x1=[2 7]
x2=[7 1]
f1=(x1-2).^2+(x2-6).^2+5
f2=(x1-7).^2+(x2-1).^2+8
syms R
r=[3;0]*[1-R]^3
r2=[3;1]*[1-R]^2
r+r2