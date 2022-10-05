clc
clear all
x = linspace(-1,1, 7);
f = @(x) exp(x)./(x.^2+1);
y = f(x);
c = polyfit(x, y, 6);
x_test = linspace(-1,1, 100);
y_test = f(x_test);
y_p = polyval(c, x_test);
norm(abs(y_test-y_p), "inf")