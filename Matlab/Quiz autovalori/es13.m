% Generare la matrice A tridiagonale di ordine 30 con gli elementi
%tutti uguali a -4 sulla diagonale principale e uguali a
%3 e a -3 sulle codiagonali superiore e inferiore, rispettivamente.
%Successivamente, generare il vettore termine noto con le componenti equispaziate
%in [0,1] e risolvere il sistema lineare Ax=b, utilizzando la decomposizione ai valori singolari della matrice A.
%Indicata con y la soluzione del sistema lineare associato alla matrice S dei valori singolari
%e all'algoritmo richiesto, la quantita' ||x||_2+||y||_2 vale all'incirca:
clc
clear all


n = 30;
A = zeros(n, n);
diag_help = ones(n, 1) * (-4);
diag_centrale = diag(diag_help);
diag_help = ones(n-1, 1) * (3);
diag_up = diag(diag_help, 1);
diag_help = ones(n-1, 1) * (-3);
diag_down = diag(diag_help, -1);
A = diag_centrale + diag_up + diag_down;

b = linspace(0, 1, n);
b = b';
[U S V] = svd(A); %Ax = U*S*V'*x = b
y = (U*S) \ b;
x = V'\y;
norm(x, 2) + norm(y, 2)