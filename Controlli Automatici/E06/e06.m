clear all
close all
s = tf('s');

Gp = 40 / (s^3 + 3*s^2 + 4.5*s);
Gs = 3;
Ga = -0.27;
Gr = 1;
Gd = 1;
Da0 = 8.5e-3;
Dp0 = 3e-3;
as = 10^(-2);
ws = 50;
Kd = 3;
er_inf = 3.5e-1;
eda_inf = 1.75e-2;
edp_inf = 0.375;
eds_inf = 3.3e-5;
tr = 2.35;
ts_alpha = 8;
alpha = 0.05;
s_cappello = 0.09;

% 1 nu + p > 0 -> p = 1 -> nu = 0
Gf = 1/(Kd*Gs);
% 2
% nu + p = 1 -> nu = 0
Kp = 40/4.5;
Kc_2 = abs((Kd^2)/(Kp*Ga*er_inf));

% 3 nu = 0
Kc_3 = abs((Kp*Da0)/(Kp*Ga*Gs*Gf*eda_inf));

% 4 nu = 1
Kc_4 = abs(Dp0/(Kp*Ga*Gs*Gf*edp_inf));

% 5
MtHF = eds_inf * Gs / as;
MtHFdb = 20*log10(MtHF);
wh = ws * 10^(MtHFdb / 40);

% 6 7 8
zeta = abs(log(s_cappello) / sqrt(pi^2 + log(s_cappello)^2));
Tp = 1 / (2*zeta*sqrt(1-zeta^2));
Sp = (2*zeta * sqrt(2 + 4*zeta^2 + 2*sqrt(1+8*zeta^2))) / (sqrt(1+8*zeta^2) + 4*zeta^2 -1);
wc_tsa = (-log(alpha) / zeta) * (sqrt(sqrt(1+4*zeta^4) - 2*zeta^2) / (ts_alpha));
wc_tr = ((pi - acos(zeta)) / sqrt(1 - zeta^2)) * (sqrt(sqrt(1+4*zeta^4) - 2*zeta^2) / (tr));

% Progetto 
Kc = -0.013; % si abbonda poco sempre
nu = 1;
Lin = minreal(zpk((Kc/s) * Gp * Ga * Gs * Gf));
%bodeplot(Lin)
figure(1)
[numLin,denLin] = tfdata(Lin,'v');
nyquist1(numLin,denLin)

figure(2)
myngridst(Tp,Sp)
nichols(Lin);

wc_des = 1.2;
%Zero network
wnorm_z = 90;
z = wc_des/wnorm_z;
Rz = (1+s/z);

%Lead network
wnorm_lead1 = 1.4;
md1 = 3;
zd1 = wc_des/wnorm_lead1;
Rd1 = (1+s/zd1)/(1+s/(md1*zd1));

% Controller
hold on
L = Lin*Rz*Rd1;
nichols(L)

% Step response

T = minreal(zpk(L/(1+L)));

figure(3)
step(T/(Gf*Gs),15)

figure(4)
bodemag(T)

S = minreal(zpk(1 / (1 + L)));
figure(5);
bodemag(S)