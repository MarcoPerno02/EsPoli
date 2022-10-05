clc
clear all


f = @(x) x.^3.*cos(x);
fd = @(x) 3.*x.^2*cos(x)-x.^2*sin(x);
fd1 = fd(0);
fdn = fd(1);
x = linspace(0, 1, 25);
x_eval = linspace(0,1,100);
y = f(x);
y_eval = spline(x, [fd1 y fdn], x_eval);
max(abs(f(x_eval)-y_eval))