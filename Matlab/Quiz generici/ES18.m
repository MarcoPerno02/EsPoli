clc
clear all

H = hilb(10);
I = eye(10);
A = H+0.001*I;

x = zeros(10,1);
aus = -2;
for i=1:10
    x(i) = aus;
    aus = aus-2;
end
b = A*x;
x_gauss = A\b;
norm(x_gauss- x, inf)