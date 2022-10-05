% Eseguire 8 iterazioni del metodo QR applicato alla matrice di Hilbert di ordine 12. Posto A_0=A, l'elemento A_{8}(3,3) è dato da
A = hilb(12);
for i=1:8
    [Q, R] = qr(A);
    A = R*Q;
end
A(3,3)