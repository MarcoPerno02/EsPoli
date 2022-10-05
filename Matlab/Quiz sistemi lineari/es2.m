%Sia Ax=b un sistema lineare di ordine 18, ove A e' simmetrica e tridiagonale con tutti gli elementi uguali a 6 sulla diagonale principale e uguali a 3 sulle codiagonali superiore e inferiore e b ha elementi equispaziati in [5,8]. Calcolare gli autovalori della matrice A e, in base alla proprieta' di quest'ultimi, risolvere il sistema lineare Ax=b mediante la risoluzione di due sistemi triangolari, utilizzando la fattorizzazione di
%A piu' efficiente in termini di costo computazionale. La norma 1 del vettore ottenuto come somma del vettore soluzione del sistema triangolare inferiore associato al metodo e del vettore soluzione del sistema triangolare superiore, vale all'incirca:

n = 18;
diag_centrale = 3 * ones(n, 1);
diag_centrale = diag(diag_centrale);
A = 3*ones(n,n);
A = A + diag_centrale;

b = linspace(5, 8, 18)';
autoval = eig(A);
[L, U, P] = lu(A);
x3 = A \ b;

y = L \ b;
x = U \ y;

x1 = L \ b;
x2 = U \ b;
err = norm((x+y), 1)
%[U,S,V] = svd(A);
%y = S \ (U'*b);
%x1= V*y;
%x2 = A\b;
%err = norm(x1+x2, 1)

%???????????????????????