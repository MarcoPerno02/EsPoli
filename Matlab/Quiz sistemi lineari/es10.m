clc
clear all
n = 18;
A = zeros(n,n);
aus = ones(n,1)*6;
diag_centrale = diag(aus);
aus = ones(n-1,1)*3;
codiag1 = diag(aus, 1);
codiag2 = diag(aus, -1);
A = diag_centrale + codiag1 + codiag2;
b = linspace(5, 8, n);
b = b';
autoval = eigs(A); % Definita posistiva
R = chol(A); % R'*RX = b ---> 
y = R'\b;
x = R\y;
norm(y, 1) + norm(x, 1)