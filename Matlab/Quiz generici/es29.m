clc
clear all

A = hilb(12);
lambda = 0;
z = ones(12,1);
w = z/norm(z);

for i = 1:7
    z = A*w;
    lambda = w'*z;
    w = z/norm(z);
end
autoval = max(abs(eigs(A)));
abs(lambda-autoval)/autoval