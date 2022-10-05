clear all
clc
format longE

for n=5:5:15
    A = hilb(n);
    condizionamento = cond(A, inf)
    b = sum(A, 2);
    x = A \ b;
    x_corretto = ones(n, 1);
    err_rel = norm(abs(x-x_corretto), inf)/norm(x_corretto, inf)
end