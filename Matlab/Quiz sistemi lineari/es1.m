
%Sia A una matrice simmetrica tridiagonale di ordine 18 con gli elementi della diagonale principale uguali a 6 e quelli delle codiagonali (inferiore e superiore) uguali a 3. Sia B una matrice di ordine 18\times 3, il cui j-esimo vettore colonna b^{(j)} e' definito da elementi equispaziati in [0,j], j=1,2,3. Risolvere i sistemi Ax^{(j)}=b^{(j)}. La norma 2 del vettore \sum_{j=1}^{3}x^{(j)} vale all'incirca:
n = 18;
diag_centrale = 6 * ones(n, 1);
diag_centrale = diag(diag_centrale);
diag_up_down = 3 * ones(n-1, 1);
diag_up = diag(diag_up_down, -1);
diag_down = diag(diag_up_down, 1);
A = diag_centrale + diag_up + diag_down;
b = zeros(18, 3);
x = zeros(18,3)
for j=1:3
    b(1:18,j) = linspace(0,j,18);
    x(1:18, j) = A \ b(1:18,j);
end
errore = norm(x(1:18, 1)+x(1:18, 2)+x(1:18, 3), 2)