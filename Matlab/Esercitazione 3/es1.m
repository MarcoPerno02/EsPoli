clc
clear all

format long e

n=15;
A=hilb(n);
condizionamento = cond(A, inf)
b = sum(A, 2);


%soluzione = matrice_dei_coeff \ vettore_termini_noti
x = A \ b;

err_rel = norm(ones(n,1)-x, inf)/norm(ones(n,1), inf)
