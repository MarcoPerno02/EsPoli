% Si costruisca la matrice C=M+I, dove M e' ottenuta tramite il comando pascal(15) e I e' la matrice identita'. Si estragga successivamente da C la sottomatrice A costituita dalle prime 10 colonne di C e si consideri il sistema sovradeterminato Ax=b con b costruito in modo che il vettore con tutti elementi uguali a 1 sia soluzione.

% Si risolva il sistema lineare usando la fattorizzazione QR, e sia x^{QR} la soluzione ottenuta. Si calcoli inoltre la soluzione x^{EN} ottenuta risolvendo il sistema delle equazioni normali A^TAx=A^Tb, usando la fattorizzazione di Cholesky. Si calcolino per entrambe le soluzioni gli errori relativi in norma 2 rispetto alla soluzione esatta, indicandoli e^{QR} ed e^{EN}.

% Si ha...

format long
clc
clear all

n = 15;
M = pascal(n);
I = eye(n);
C = M + I;
A = C(:,1:10);
x = ones(10,1);
b = A*x;
[Q,R] = qr(A);
x_qr = (Q*R)\b
e_qr = norm(abs(x_qr - x)/x, 2) % circa 10^-11
%x_chol = (A'*A)\(A'*b);
b_aus = A'*b;
R = chol(A'*A);
x_chol = (R'*R)\b_aus;
e_chol = norm(abs(x_chol - x)/x, 2)