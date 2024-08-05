clc
clear all

A = [0, 1; -3, -4];
B = [0; 1];
C = [2 , 1];
D = 0;
sys = ss(A, B, C, D);
obsv(sys);
ctrb(sys);
pk = [-10 -20];
pl = [-10 -11];
K = place(A, B, pk);
L = place(A', C', pl)';
minreal(zpk(tf(reg(sys, K, L))))

alpha = 1/[-(C-D*K)*inv(A-B*K)*B+D]