clear all
clc

n = 100;
p = n:-1:1;
A = p(ones(n,1),:) - diag(ones(n-1, 1),-1);
A1 = triu(A, -1);

% S1 è un matrice che ha sulle colonne gli autovettori di Ai
% lambda1 è una matrice diagonale i cui elementi sono gli autovalori
[S1, lambda1] = eig(A1);

A1p = A1;
A1p(n,:) = A1(n,:) + 1.0e-10;
lambda1p = eig(A1p); % lamda1p è un vettore

e=diag(lambda1);

a=sort(e);
b=sort(lambda1p);

err_max = max(abs(a-b));

K1 = cond(S1);
M1 = K1*norm(A1-A1p);

%plot(real(e), imag(e), 'r*', real(lambda1p), imag(lambda1p), 'bo', 'LineWidth', 3);

%%%%%%%%%%%%%%%%%%%%%%%

A2 = triu(A1) + triu(A1, 1)';
[S2, lambda2] = eig(A2);
A2p = A2;
A2p(n,:) = A2(n,:)+1.0e-10;

lambda2p = eig(A2p);
e2 = diag(lambda2);

a2 = sort(e2);
b2 = sort(lambda2p);

err2max=max(abs(a2-b2));
err2max

K2 = cond(S2)
M2 = K2*norm(A2-A2p)
plot(real(e2), imag(e2), 'r*', real(lambda2p), imag(lambda2p), 'bo', 'LineWidth', 3);
