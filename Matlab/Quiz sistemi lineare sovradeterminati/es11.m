%Si costruisca la matrice B=M+I, dove M e' ottenuta tramite il comando magic(20) e I e' la matrice identita'. Si estragga successivamente da B la sottomatrice A costituita dalle prime 10 colonne di B e si consideri il sistema sovradeterminato Ax=b con b costruito in modo che il vettore con tutti elementi uguali a 1 sia soluzione.

%Si risolva il sistema lineare usando la fattorizzazione QR, e sia x^{QR} la soluzione ottenuta. Si calcoli inoltre la soluzione x^{BS} ottenuta con il comando backslash di MATLAB. Si calcolino per entrambe le soluzioni gli errori relativi in norma 2 rispetto alla soluzione esatta, indicandoli e^{QR} ed e^{BS}.

%Si ha...

B = magic(20) + eye(20);
A = B(:,1:10)
x = ones(10, 1);
b = A*x;

[Q, R] = qr(A) % QRx = b
x_qr = (Q*R)\b;
e_qr = norm(abs(x_qr - x)/x, 2)

x_guass = A\b;
e_gauss = norm(abs(x_guass - x)/x, 2)