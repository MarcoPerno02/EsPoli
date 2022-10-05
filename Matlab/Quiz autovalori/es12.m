%A partire dal vettore unitario, eseguire 4 iterazioni del metodo delle potenze inverse applicato alla matrice generata con il comando A=pascal(6) di ordine 6. L'errore assoluto associato all'approssimazione dell'autovalore più vicino a p=2 (si prenda come valore di riferimento quello ottenuto con il comando eig), vale all'incirca:

A = pascal(6);
n = size(A)
m_max = 4;
z = ones(6,1);
w = z/norm(z);
p=2;
lambda = 2;
[L,U,P] = lu(A-p*eye(n));
for m = 1:m_max
    y = L\(P*w);
    z = U\y;
    lambda_p = p+1/(w'*z);
    w = z/norm(z);
    lambda = lambda_p;
end
autoval = eigs(A)
abs(autoval(3)-lambda)
    