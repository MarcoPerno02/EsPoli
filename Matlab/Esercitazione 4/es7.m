clear all
clc

A = [1 2 3 4;
    -1 0 4 1;
    3 5 1 0;
    2 -1 0 1;
    1 1 -1 1;
    2 -1 0 3];
b = (1:6)';

rank(A);
[Q, R] = qr(A);
R_tilde = R(1:4, 1:4);
c = Q'*b;
c1 = c(1:4);

x_star = R_tilde \ c1
x = A\b