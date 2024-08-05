clear all
close all
s = tf('s');

Gp = 375200/(s^3 + 575*s^2 + 70000*s);
Gd = 1;
Gs = 3;
Ga = 6650;
Dp0 = 1.5e-2;
as = 3e-1;
ws = 5000;
Kd = 3;
er_inf = 10^(-3);
edp_inf = 0;
eds_inf = 10^(-2);
ts_alpha = 0.00648;
alpha = 0.05;
s_cappello = 0.11;
P = 1;

% 1 nu + p > 0 -> nu = 0
Gf = 1/(Kd*Gs);
% 2 nu + p = 0 -> nu negativo, quindi nu = 0 e no vincoli Kc
Kp = 375200 / 70000;
% 3 nu = 0 Kc Libero
% 4
MtHF = eds_inf * Gs / as;
MtHFdb = 20 * log10(MtHF);
wh = ws * 10 ^ (MtHFdb / 40);

% 5 6
zeta = abs(log(s_cappello) / sqrt(pi^2 + log(s_cappello)^2));
Tp = 1 / (2*zeta*sqrt(1-zeta^2));
Sp = (2*zeta * sqrt(2 + 4*zeta^2 + 2*sqrt(1+8*zeta^2))) / (sqrt(1+8*zeta^2) + 4*zeta^2 -1);
wc_tsa = (-log(alpha) / zeta) * (sqrt(sqrt(1+4*zeta^4) - 2*zeta^2) / (ts_alpha));

% Controllore 
Kc = 1;
nu = 0;
Lin = minreal(zpk((Kc/1) * Gp * Ga * Gs * Gf));
% bodeplot(Lin)

figure(1)
[numLin,denLin] = tfdata(Lin,'v');
nyquist1(numLin,denLin)

figure(2)
myngridst(Tp,Sp)
nichols(Lin);

wc_des = 620;
%Lead network
wnorm_lead1 = 3;
md1 = 9;
zd1 = wc_des/wnorm_lead1;
Rd1 = (1+s/zd1)/(1+s/(md1*zd1));

% Controller
hold on
L = Lin*Rd1*Rd1 * 10^(-28.3/20);
nichols(L)

% Step response

T = minreal(zpk(L/(1+L)));

figure(3)
step(T/(Gf*Gs),15)

figure(4)
bodemag(T)
