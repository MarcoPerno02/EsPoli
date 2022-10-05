clear all
clc

m_max = 100;
tol = 1.0e-10;
z = ones(3,1);
p = 0.5;
A = [0 -2 0; 0 1 0; 1 1 3];
[lambda_p, w, m] = potenze_inverse(A, p, z, tol, m_max);
plot(1:m+1, lambda_p, 'b+-', LineWidth=3)

autovalore_p = lambda_p(end)
autovalori_tutti = eig(A)
autovalore_eigs = eigs(A,1,p) %Autovalore più vicino a p