clc
clear all
f = @(x) x.^2.*exp(x);
fd = @(x) 2.*x.*exp(x) + x.^2.*exp(x);
fd1 = fd(0);
fdn = fd(1);
x = linspace(0, 1, 9);
y = f(x);
x_eval = linspace(0,1,100);
y_eval = spline(x, [fd1 y fdn], x_eval);
max(abs(f(x_eval)-y_eval))