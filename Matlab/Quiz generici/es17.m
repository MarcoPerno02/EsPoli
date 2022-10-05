clc
clear all
format longE

f = @(x) exp(x.^2);
fd = @(x) exp(x.^2) .* 2.*x;
f1 = fd(0);
fn = fd(1);
x = linspace(0, 1, 7);
y = f(x);
x_test = linspace(0,1,100);
y_eval = f(x_test);
y_test = spline(x, [f1 y fn], x_test);
max(abs(y_eval-y_test))