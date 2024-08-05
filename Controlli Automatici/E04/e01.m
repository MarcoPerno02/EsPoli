clc
clear all

% Definizione costanti
m = 0.02;
g = 9.81;
Kt = 708.27;
Km = 1.52e-4;

syms x1 x2 Im
f1 = x2;
f2 = g - (Km * Im ^ 2) / (m * x1 ^ 2);

Im0 = 0.8;

% 1
F(x1, x2, Im) = [f1; f2];
Fu = subs(F, Im, Im0);

Fu0 = Fu == 0;
sFu0 = solve(Fu0);

%format short
disp(sFu0.x1)
disp(sFu0.x2)

% 2
X0 = [0.0223, 0]';
x1_eq = X0(1);
y = Kt * (x1 - x1_eq);
G(x1, x2, Im) = y;

A_mat = jacobian([f1, f2], [x1, x2]);
B_mat = jacobian([f1, f2], [Im]);
C_mat = jacobian([y], [x1, x2]);
D_mat = jacobian([y], [Im]);

A_mat = subs(A_mat, [x1, x2, Im], [X0(1), X0(2), Im0])
B_mat = subs(B_mat, [x1, x2, Im], [X0(1), X0(2), Im0])
C_mat = subs(C_mat, [x1, x2, Im], [X0(1), X0(2), Im0])
D_mat = subs(D_mat, [x1, x2, Im], [X0(1), X0(2), Im0])

% 3
eig(A_mat) % stabile

A_mat = double(A_mat)
B_mat = double(B_mat)
C_mat = double(C_mat)
D_mat = double(D_mat)