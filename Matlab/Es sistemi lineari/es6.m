clc
clear all
tempo1 = 0;
tempo2 = 0;
for n=100:100:1000
    A=rand(n);
    b = sum(A, 2);
    tic
    [Q, R] = qr(A);
    x = R \ (Q'*b);
    tempo1 = tempo1 + toc;
    tic
    x = A \ b;
    tempo2 = tempo2 + toc;
end

tempo1
tempo2