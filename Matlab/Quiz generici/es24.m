clc
clear all

A = magic(765) + 10*eye(765);
x = ones(765,1);
b = A*x;
x_gauss = A\b;
norm(b-A*x_gauss, inf)