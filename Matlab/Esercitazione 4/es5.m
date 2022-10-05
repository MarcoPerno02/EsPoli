format longE
clear all
clc

n = 100;
x = 10 * ones(n,1);
cs = 5 * ones(n-1, 1);
ci = -5 * ones(n-1, 1);
B = diag(x) + diag(ci, -1) + diag(cs, 1);

A = B'*B;

eig(A);

R = chol(A);

R1 = inv(R);
inversa = R1*R1';
inversa_matlab = inv(A);
err_rel = norm(inversa-inversa_matlab, "inf")/norm(inversa_matlab);
%%%%%%%%%%%%%%%%%%% Risolviamo il sistema lineare
b = sum(A, 2)
y = R'\b;
x = R\y;
x_matlab = A\b;
err_rel2 = norm(x-x_matlab, inf)/norm(x_matlab, inf)



