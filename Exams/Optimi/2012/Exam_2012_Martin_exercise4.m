clc
clear all
close all
x1=[4 4 4 4 4 4 4]
x2=[4:0.5:7]
f1=(x1-4).^2+(x2-2).^2
f2=(x1-4).^2+(x2-8).^2
plot(f1,f2)