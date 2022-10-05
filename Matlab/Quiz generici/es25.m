clc
clear all

x = linspace(4, 6, 8);
A = vander(x);
[U, S, V] = svd(A);
An = zeros(8,8);
for k=1:5
    An = An + S(k,k) * U(:,k) * V(:,k)';
end
norm(An, 1)