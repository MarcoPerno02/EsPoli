clc
clear all

x = linspace(-1, 1, 9);
f = @(x) exp(-x.^2);
y = f(x);
c = polyfit(x, y, 8);
x_eval = linspace(-1, 1, 300);
max(abs(polyval(c, x_eval)-f(x_eval)))