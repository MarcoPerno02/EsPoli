A = [6*pi, 3, 7; 6, 9, -1; -3, -2, 7];
b = [log(2), 6, -2*pi]';
x = A \ b;
A = [1,0;2,-1];
x=[7;-1];
aa = (x'*A*x)/(x'*x);
A = [1 -2 4; -5 2 0; 1 0 3];
[L U P] = lu(A);

% Primo modo (Con matrice di passaggio da B' a B)
N = [1,0,0; 1,1,1; 0,0,2];
A = [1,0,1; 1,0,2; 0,0,0];
bbb = N*A*inv(N)

% Secondo modo (Con matrice di passaggio da B a B') Danno gli stessi
% risultati con formule cambiate ovviamente. Teoricamente era questo quello
% che cercavo per arrivare alla base canonica
N = inv(N);
A = [1,0,1; 1,0,2; 0,0,0];
bbb = inv(N)*A*N