% Eseguire 6 iterazioni del metodo QR applicato alla matrice di Hilbert A di ordine 18. Denotati con \bar{\lambda}_i le approssimazioni degli autovalori di A e con \lambda_i gli autovalori ottenuti con il comando eig, il max errore massimo assoluto \max_i|\bar{\lambda}_i-\lambda_i| vale all'incirca:

A = hilb(18);
m_max=6;

autovalori = eig(A);
for m = 1:m_max
    [Q,R] = qr(A);
    A = R*Q;
end
d = diag(A);
max(abs(sort(d)-sort(autovalori)))
