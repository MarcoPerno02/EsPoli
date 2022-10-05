clc
clear all

aus = 6*ones(18,1);
diag_centrale = diag(aus);
aus = 3*ones(17,1);
diag_up = diag(aus, 1);
diag_down = diag(aus, -1);
A = diag_centrale + diag_down + diag_up;
b = linspace(5,8, 18)';
autoval = eigs(A);
R = chol(A); % R'*Rx = b
y = R'\b;
x = R\y;
norm(x+y, 1)