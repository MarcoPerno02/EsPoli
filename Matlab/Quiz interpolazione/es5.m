clc
clear all
close all

f = @(x) (log(x));
n = 25;
a = 1;
b = 2;

x = linspace(a, b, 25);
y = f(x);
z = linspace(a, b, 1000);
fz = f(z);
s = spline(x, y, z);

errmax = max(abs(fz - s))
