% Generare la matrice A di Hilbert di ordine n=12 e applicare ad essa 7 iterazioni del metodo delle potenze per determinare un'approssimazione del raggio spettrale \rho(A),
% a partire dal vettore unitario. Successivamente, utilizzare la definizione \rho(A)=\max_i|\lambda_i|, con \lambda_i
% autovalore di A, per calcolare il valore di riferimento ''esatto''. L'errore relativo associato all'approssimazione del raggio spettrale determinata con il metodo delle potenze vale all'incirca:
n = 12;
A = hilb(n);

z = ones(n,1);
m_max=7;

w = z/norm(z);
lambda = 0;
for m = 1:m_max
    z = A*w;
    lambda_max = w'*z ;
    w = z/norm(z);
    lambda = lambda_max;
end
raggio_corretto = max(abs(eig(A)));
err_rel = abs(raggio_corretto-lambda)/raggio_corretto