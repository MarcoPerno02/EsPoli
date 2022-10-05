clc
clear all

x = linspace(0, pi/2, 30);
f = @(x) x.*sin(x);
y= f(x);
c =polyfit(x, y, 2)