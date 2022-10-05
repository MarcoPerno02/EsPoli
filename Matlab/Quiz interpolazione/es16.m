clc
clear all

a=0;
b=1;
f = @(x) x.*exp(x);

n = 4;
i = linspace(1,n+1, n+1);
t = -cos(((i-1)*pi)/n);
x_5 = (b-a)/2.*t+(b+a)/2;
y_5 = f(x_5);

n = 8;
i = linspace(1,n+1, n+1);
t = -cos(((i-1)*pi)/n);
x_9 = (b-a)/2.*t+(b+a)/2;
y_9 = f(x_9);

c_4 = polyfit(x_5, y_5, 4);
c_8 = polyfit(x_9, y_9, 8);

x = linspace(0,1,100);
norm(polyval(c_8, x)-f(x), "inf")/norm(polyval(c_4, x)-f(x), "inf")