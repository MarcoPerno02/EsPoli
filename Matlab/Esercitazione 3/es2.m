clear all
clc

n = 100;
A=zeros(n,n);

for i=1:n
    for j=1:n
        A(i,j) = max([i,j]);
    end
end

b = sum(A,2);
condizionamento = cond(A, inf)
[L, U, P] = lu(A);
y=L\(P*b);
x=U\y;

err_rel = norm(ones(n,1)-x, inf)/norm(ones(n,1), inf)