clc
clear all

n=100;
A = zeros(n, n);
for i=1:n
    for j=1:n
        A(i,j) = cos(max(i,j));
    end
end
cond(A, 1)