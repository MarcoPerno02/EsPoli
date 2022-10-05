clc
clear all

n=100;
A=zeros(n,n);

for i=1:n
    for j=1:n
        A(i,j) = i*max([i,j]);
    end
end

A_INV = inv(A);

condizionamento = cond(A, inf)
[L, U, P] = lu(A);
A_INV_1 = inv(U) * inv(L) * P;
err_rel = norm(A_INV_1-A_INV, inf)/norm(A_INV, inf)