A = [0 -1 5; 0 0 3; 0 0 -2];
B = [1; 1; 1];
C = [0 0 5];
D = 0;
s = tf("s");
U = 9/s;
X0_3 = [1 5 0]';
X0_4 = [0 0 3]';

% 1
A1 = minreal(zpk(inv(s*eye(size(A)) - A))) % non internamente stabile perchè un termine della matrice ha denominatore con radice 0 non semplice
sys = ss(A, B, C, D);
H = tf(sys) % solo un polo in -2, che è negativo quindi BIBO Stabile

% 2
% Risposta forzata
risp_forzata = (C*inv(s*eye(size(A)) - A)*B+D)*U;
% Calcolo come scriverla con il teorema dei residui
risp_forzata = minreal(zpk(risp_forzata)) % Semplifico la risposta forzata
[numY, demY] = tfdata(risp_forzata, 'v');
[R, P] = residue(numY, demY);
% Antitrasformo su carta
%   22.5   22.5
% - ____ + ____  ---L^-1--> -22.5*e^(-2t)*h(t) + 22.5*h(t)
%   (s+2)   s

% 3
% Risposta Libera
risp_libera = C*inv(s*eye(size(A)) - A)*X0_3;
risp_libera = minreal(zpk(risp_libera)) % Semplifico la risposta libera
[numY, demY] = tfdata(risp_libera, 'v');
[R, P] = residue(numY, demY)
% Con quelle condizioni iniziali la risposta libera è 0

% 4
% Risposta Libera
risp_libera = C*inv(s*eye(size(A)) - A)*X0_4;
risp_libera = minreal(zpk(risp_libera)) % Semplifico la risposta libera
[numY, demY] = tfdata(risp_libera, 'v');
[R, P] = residue(numY, demY)

% Antitrasformo su carta
%   15 
%  ____  ---L^-1--> 15*e^(-2t)*h(t) 
%  (s+2) 

