% Sia x un vettore costituito da 10 elementi equispaziati in [0,1] e sia A la matrice generata con il comando A=vander(x).
% Determinare la matrice A_n di rango 7 piu' vicina in norma 2 ad A. La norma \inf di A_n vale all'incirca:
x = linspace(0, 1, 10);
A = vander(x);
[U,S,V] = svd(A);
An = zeros(10,10);
An = S(:,1:7)*U(1:7,1:7)*V(:,1:7)';
norm(An, inf)