%  partire dal vettore unitario, eseguire 4 iterazioni del metodo delle potenze inverse applicato alla matrice generata con il comando A=pascal(6) di ordine 6. L'errore assoluto associato all'approssimazione dell'autovalore più vicino a p=2 (si prenda come valore di riferimento quello ottenuto con il comando eig), vale all'incirca:
A = pascal(6);
[X, D]  = eigs(A, 1, 2,	'MaxIterations',4)
autovalori = eig(A);
autovalori(4)
err = abs(autovalori(4)-D);
D;
