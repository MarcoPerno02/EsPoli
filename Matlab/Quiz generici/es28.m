clc
clear all

A = pascal(6);
p = 2;
lambda = 2;
[L, U, P] = lu(A-p*eye(6));
z = ones(6,1);
w = z/norm(z);
for i = 1:4
    y = L\(P*w);
    z = U\y;
    lambda = p+1/(w'*z);
    w = z/norm(z);
end

autoval = eigs(A, 1, 2);
err_ass = abs(autoval-lambda)
