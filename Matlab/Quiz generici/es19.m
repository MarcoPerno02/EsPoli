clc
clear all
x = linspace(1, 2, 6);
A = vander(x);
[U, S, V] = svd(A);
An = zeros(6,6);
for k=1:4
    An = An+S(k,k)*U(:,k)*V(:,k)';
end
norm(An, inf)