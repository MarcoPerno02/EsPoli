clc
clear all

% Definizione variabili
s = tf('s');
p1 = 0.003;
p2 = 0.025;
p3 = 0.000013;
V1 = 12;
VG = 126;
n = 5/54;
Gb = 81;
Ib = 15;

syms G I B R U2;
f1 = -p1 * (G - Gb) - B * G + U2/VG;
f2 = -n * I + R/V1;
f3 = -p2 * B + p3 * (I-Ib);
y = G;
g(G, I, B, R, U2) = y;

r = 16.66667;
u2 = 0;

% E01
F(G, I, B, R, U2) = [f1; f2; f3];
Fu = subs(F, R, r);
Fu = subs(Fu, U2, u2);

Fu0 = Fu == 0;
sFu0 = solve(Fu0);

%format short
disp(sFu0)

% E02
X0 = [81, 15, 0]';
U0 = [r, u2]';
A_mat = jacobian([f1, f2, f3], [G, I, B]);
B_mat = jacobian([f1, f2, f3], [R, U2]);
C_mat = jacobian([y], [G, I, B]);
D_mat = jacobian([y], [R, U2]);

A_mat = subs(A_mat, [G, I, B, R, U2], [X0(1), X0(2), X0(3), U0(1), U0(2)])
B_mat = subs(B_mat, [G, I, B, R, U2], [X0(1), X0(2), X0(3), U0(1), U0(2)])
C_mat = subs(C_mat, [G, I, B, R, U2], [X0(1), X0(2), X0(3), U0(1), U0(2)])
D_mat = subs(D_mat, [G, I, B, R, U2], [X0(1), X0(2), X0(3), U0(1), U0(2)])

% E03
eig(A_mat) % stabile
size(A_mat)