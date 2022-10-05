%Sia A una matrice quadrata di dimensione n=100 che ha coefficienti pari a 4 sulla diagonale principale, coefficienti pari a -1 sulla prima sovra e sotto diagonale e coefficienti pari a -2 sulla decima sovra e sotto diagonale. Si calcoli il numero di condizionamento di A in norma infinito, approssimando alla prima cifra decimale.
n = 100;
diag_centrale = 4*ones(n, 1);
diag_centrale = diag(diag_centrale);

diag_up_down = -1*ones(n-1, 1);
diag_up = diag(diag_up_down, 1);
diag_down = diag(diag_up_down, -1);

diag_up_down1 = -2*ones(n-10, 1);
diag_up1 = diag(diag_up_down1, 10);
diag_down1 = diag(diag_up_down1, -10);

A = diag_centrale + diag_up + diag_down + diag_down1 + diag_up1;
err = cond(A, "inf")