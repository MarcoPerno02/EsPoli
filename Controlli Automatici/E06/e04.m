clc
clear all
close all
s = tf("s");

Gp = 100/(s^2 + 5.5*s + 4.5);
Gs = 1;
Ga = 0.014;
Gr = 1;
Gd = 1;
Da0 = 15e-3;
ap = 16e-2;
wp = 0.03;
as = 2e-1;
ws = 60;
Kd = 1;
R0 = 1;
er_inf = 1.5e-1;
eda_inf = 4.5e-3;
edp_inf = 2e-3;
eds_inf = 8e-4;
tr = 2;
ts_5 = 8;
ts_alpha = 0.05;
s_cappello = 0.12;

% 1
Gf = 1 / (Kd*Gs);

% 2
Kp = 22.22;
Kc_tmp2 = abs((Kd^2*R0)/(Kp*er_inf*Ga));

% 3
% Nessun vincolo su Kc o nu

% 4
MsLF = edp_inf / ap;

% 5
MtHF = eds_inf * Gs / as;

% 6 7 8
zeta = abs(log(s_cappello))/sqrt(pi^2 + log(s_cappello)^2);
Tp_max = 1 / (2 * zeta * sqrt(1 - zeta^2));
Sp_max = (2 * zeta * sqrt(2 + 4 * zeta^2 + 2 * sqrt(1 + 8 * zeta^2)))/(sqrt(1 + 8 * zeta^2) + 4 * zeta^2 -1);
wc_tsa = (-log(ts_alpha)/zeta) * ((sqrt(sqrt(1 + 4 * zeta^4) - 2 * zeta^2))/(ts_5));
wc_tr = ((pi - acos(zeta))/(sqrt(1 - zeta^2))) * ((sqrt(sqrt(1 + 4 * zeta^4) - 2 * zeta^2))/(tr));

% Controllore 
Kc = 21.6;
nu = 1;

Lin = 30.1/(s*(s+1)*(s+4.5));
%bodeplot(Lin)
figure(1)
[numLin,denLin] = tfdata(Lin,'v');
nyquist1(numLin,denLin)
figure(2)
myngridst(Tp_max,Sp_max)
nichols(Lin);

wc_des = 1.54;
%Lead network
wnorm_lead1 = 2.2 ;
md1 = 11;

zd1 = wc_des/wnorm_lead1;

Rd1 = (1+s/zd1)/(1+s/(md1*zd1));

% Lag network

wnorm_lag1 = 100 ; %final 500

pi1 = wc_des/wnorm_lag1;

mi1 = 5; % final value 22dB

Ri1 = (1+s/(mi1*pi1))/(1+s/pi1);


% Controller
Gc = Kc/s^nu*Rd1*Ri1;
hold on
L = Gc*Gp*Ga*Gs*Gf;
nichols(L)

% Step response

T = minreal(zpk(L/(1+L)));
S = minreal(zpk(1/(1+L)));

figure(3)
time = [0:2.5/100:15];
step(T/(Gf*Gs),time)

[numGp,denGp] = tfdata(Gp,'v');
[numGc,denGc] = tfdata(Gc,'v');

figure(4)
bodemag(T)
bodemag(S)
