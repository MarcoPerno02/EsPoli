clc
clear all

A = hilb(14);
z = ones(14,1);
w = z/norm(z);
lambda = 0;

for  i=1:7
    z = A*w;
    lambda = w'*z;
    w = z/norm(z);
end
raggio = max(abs(eigs(A)))
err_rel = abs(lambda-raggio)/raggio