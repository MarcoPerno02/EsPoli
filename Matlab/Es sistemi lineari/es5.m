clc
clear all

n=100;
diag_centrale = 10*(ones(n, 1));
diag_centrale = diag(diag_centrale);
diag_up = 5*(ones(n-1, 1));
diag_up = diag(diag_up, 1);
diag_down = -5*(ones(n-1, 1));
diag_down = diag(diag_down, -1);
B = diag_centrale + diag_down + diag_up;
A = B'*B;

R = chol(A);
A_inv_chol = inv(R)*(inv(R))';
err_inv = norm(abs(A_inv_chol - inv(A)), "inf")/norm(inv(A), "inf")

b = sum(A, 2);
y = R' \ b;
X_chol = R \ y;
X = A \ b;
err_sist = norm(abs(X_chol - ones(n, 1)), "inf")/norm(ones(n, 1), "inf")