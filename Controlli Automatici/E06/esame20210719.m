clear all
close all
s = tf('s');

Gp = 10 / (s * (s + 50)^2);
Gd = 1;
Gs = 2;
Ga = -3;
Da0 = 222e-2;
as = 2e-3;
ws = 2000;
Kd = 1;
er_inf = 0;
eda_inf = 0;
eds_inf = 10^(-5);
tr = 0.1;
ts_alpha = 1;
alpha = 0.05;
s_cappello = 0.1;
p = 1;

% 1   nu + p > 0 -> nu = 0
Gf = 1 / (Kd*Gs);
% 2 step input con errore 0 -> nu + p = 1 -> nu = 0
% 3 nu = 1
% 4 wc <= 200
MtHF = eds_inf * Gs / as;
MtHFdb = 20 * log10(MtHF);
wh = ws * 10 ^ (MtHFdb / 40);

% 5 6 7
zeta = abs(log(s_cappello) / sqrt(pi^2 + log(s_cappello)^2));
Tp = 1 / (2*zeta*sqrt(1-zeta^2));
Sp = (2*zeta * sqrt(2 + 4*zeta^2 + 2*sqrt(1+8*zeta^2))) / (sqrt(1+8*zeta^2) + 4*zeta^2 -1);
wc_tsa = (-log(alpha) / zeta) * (sqrt(sqrt(1+4*zeta^4) - 2*zeta^2) / (ts_alpha));
wc_tr = ((pi - acos(zeta)) / sqrt(1 - zeta^2)) * (sqrt(sqrt(1+4*zeta^4) - 2*zeta^2) / (tr));

Kc = -1; % si abbonda poco sempre
nu = 1;
Lin = minreal(zpk((Kc/s) * Gp * Ga * Gs * Gf));
%bodeplot(Lin);
figure(1)
[numLin,denLin] = tfdata(Lin,'v');
nyquist1(numLin,denLin)

figure(2)
myngridst(Tp,Sp)
nichols(Lin);

wc_des = 29;
%Zero network
wnorm_z = 100;
z = wc_des/wnorm_z;
Rz = (1+s/z);

%Lead network
wnorm_lead1 = 1.6;
md1 = 5;
zd1 = wc_des/wnorm_lead1;
Rd1 = (1+s/zd1)/(1+s/(md1*zd1));

% Controller
hold on
L = Lin*Rz*Rd1*10^(55/20);
nichols(L)

% Step response

T = minreal(zpk(L/(1+L)));

figure(3)
step(T/(Gf*Gs),15)

figure(4)
bodemag(T)

