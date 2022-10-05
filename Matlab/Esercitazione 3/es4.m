clear all
clc

n=100;
p=30;
A=rand(n);
[L, U, P] = lu(A);

b = sum(A, 2)
x = zeros(n,p);

for i=1:p
    y=L\(P*b);
    x(:1) = U\y;
    b=x(i,i);
end