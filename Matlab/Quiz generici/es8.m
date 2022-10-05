clc
clear all
format longG
H = hilb(7);
I = eye(7,7);
A = H + 0.001*I;
x = zeros(7,1);
aus = 2;
for i=1:7
    x(i) = aus;
    aus = aus+2;
end
b = A*x;
x_gauss = A\b;
norm(abs(x-x_gauss), inf)