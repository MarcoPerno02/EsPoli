clc
clear all
close all
s = tf('s');

% Calcolare y(t) Sapendo condizioni iniziali e A B C D
% A = [0, -1; 3 ,-2];
% B = [1;1];
% C = [1,1];
% D = 0;
% U = 5/s;
% % Risposta forzata
% risp_forzata = (C*inv(s*eye(size(A)) - A)*B+D)*U;
% % Calcolo come scriverla con il teorema dei residui
% risp_forzata = minreal(zpk(risp_forzata), 0.5) % Semplifico la risposta forzata
% [numY, demY] = tfdata(risp_forzata, 'v');
% [R, P] = residue(numY, demY)
% % se necessario abs(R(1));angle(R1)
% % Risposta Libera
% X0 = [0; 0];
% risp_libera = C*inv(s*eye(size(A)) - A)*X0;
% risp_libera = minreal(zpk(risp_libera)) % Semplifico la risposta libera
% [numY, demY] = tfdata(risp_libera, 'v');
% [R, P] = residue(numY, demY)


% Determinare i guadagni K per retroazione statica
% A = [0, -1; 3 ,-2];
% B = [1;1];
% C = [1,1];
% D = 0;
% lambda1 = 20;
% lambda2 = -10;
% sys = ss(A,B,C,D);
% rank(obsv(sys)); % Deve essere uguale rank(A) -> Sistema completamnete controllabile 
%                  % con autovalori miei
% pk = [lambda1; lambda2];
% K = place(A, B, pk)
% 
% 
% Linearizzazione sistemi dinamici per dire se è stabile
% syms x1 x2 u;
% f1 = x2^2 - x1^3 - x1 + u;
% f2 = -x1*x2;
% 
% A = jacobian([f1, f2], [x1, x2]);
% A = subs(A, [x1, x2, u], [0, 0, 0]);
% eig(A)
% A = [-1 ,0; 0, 0];
% A1 = minreal(zpk(inv(s*eye(2) - A))) % Polinomio minimo trovo minimo comune divisore di elem in A1
% 
% BIBO stabile
% A = [-1, 1; 0, 2];
% B = [1;0];
% C = [1, 0];
% D = 0;
% system = ss(A, B, C, D);
% tf(system) % tutti i poli parte reale minore di 0
% 
% Controllo matrice obvs
% A = [-5, -2; 0, -3];
% C = [1, 1];
% rank(obsv(A, C))
% 
% Progettare L
% A = [0, -1; 3, 2];
% B = [0; 0];
% C = [1, 1];
% D = 0;
% sys = ss(A, B, C, D);
% rank(obvs(A))
% pl = [-20; -10];
% L = place(A', C', pl)'
% 
% Progettare K 
% A = [2, 0; 0, 1];
% B = [1; 5];
% C = [0, 1];
% D = 0;
% sys = ss(A, B, C, D);
% rank(ctrb(sys));
% pk = [0.1, 0.2];
% K = place(A, B, pk);
% 
% 
% Stabilità per sistema discreto
% A = [0.1, -2; 0, 1];
% eig(A)
% A1 = minreal(zpk(inv(s*eye(2) - A)));
% 
% Linearizzazione sistema lineare
% syms x1 x2 u;
% f1 = -x1^3 + x1 + x2 + u + 1;
% f2 = x1 + x2 + u;
% y = x1 + x2;
% u0 = -1;
% x0 = [1;0];
% 
% A = jacobian([f1 f2], [x1 x2]);
% B = jacobian([f1 f2], [u]);
% C = jacobian([y], [x1 x2]);
% D = jacobian([y], [u]);
% 
% A = subs(A, [x1, x2, u], [x0(1), x0(2), u0]);
% B = subs(B, [x1, x2, u], [x0(1), x0(2), u0]);
% C = subs(C, [x1, x2, u], [x0(1), x0(2), u0]);
% D = subs(D, [x1, x2, u], [x0(1), x0(2), u0]);
% 
% Calcola asintotica stabilità sapendo K 
% A = [3, 2; 0, -5];
% B = [1;0];
% K = [4, 0];
% eig(A - B*K)
% 
% Calcolo risposta a regime permanente tempo discereto
% A = [3, 0; 0, 0.7];
% B = [1; 1];
% C = [0, 3];
% D = 0;
% H = C * inv(s*eye(2) - A) * B + D;
% H = minreal(zpk(H), 0.5)
% [numY, demY] = tfdata(H, 'v'); % ho verificato che è bibo stabile e posso andare avanti
% 
% A = [-7, 0; 0, -5];
% B = [1; 1];
% C = [0, 3];
% D = 0;
% H = C * inv(s*eye(2) - A) * B + D;
% H = minreal(zpk(H), 0.5)
% [numY, demY] = tfdata(H, 'v'); % ho verificato che NON è bibo stabile e NON posso andare avanti
% 
% Calcolare y(t) Sapendo condizioni iniziali e A B C D
% A = [0, -1; 3 ,-2];
% B = [1;1];  
% C = [1,1];
% D = 0;
% U = 5/s;
% Risposta forzata
% risp_forzata = (C*inv(s*eye(size(A)) - A)*B+D)*U;
% Calcolo come scriverla con il teorema dei residui
% risp_forzata = minreal(zpk(risp_forzata), 0.5) % Semplifico la risposta forzata
% [numY, demY] = tfdata(risp_forzata, 'v');
% [R, P] = residue(numY, demY)
% abs(R(1))
% angle(R(1))

A = [2, 0; 0, 1];
B = [1; 5];
C = [0, 1];
D = 0;
pk = [0.1, 0.2];
sys = ss(A, B, C, D);
rank(obsv(sys))
rank(ctrb(sys))
K = place(A, B, pk);
L = place(A', C', pk);
