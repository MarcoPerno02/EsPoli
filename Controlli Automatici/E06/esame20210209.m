clear all
close all
s = tf('s');

Gp = -1 / (0.1 * s^2 + 12.5 * s);
Gda = 1;
Gdp = 1;
Gs = 5;
Ga = 3;
Da0 = 222e-2;
as = 5e-3;
ws = 2500;
Kd = 1;
eda_inf = 0;
eds_inf = 10^(-4);
tr = 0.05;
ts_alpha = 0.1;
alpha = 0.05;
s_cappello = 0.08;

% 1 nu = 0
Gf = 1 / (Kd * Gs);
% 2 nu = 1 no vincoli su Kc
% 3
MtHF = eds_inf * Gs / as;
MtHFdb = 20 * log10(MtHF);
wh = ws * 10^(MtHFdb / 40);

% 4 5 6
zeta = abs(log(s_cappello) / sqrt(pi^2 + log(s_cappello)^2));
Tp = 1 / (2*zeta*sqrt(1-zeta^2));
Sp = (2*zeta * sqrt(2 + 4*zeta^2 + 2*sqrt(1+8*zeta^2))) / (sqrt(1+8*zeta^2) + 4*zeta^2 -1);
wc_tsa = (-log(alpha) / zeta) * (sqrt(sqrt(1+4*zeta^4) - 2*zeta^2) / (ts_alpha));
wc_tr = ((pi - acos(zeta)) / sqrt(1 - zeta^2)) * (sqrt(sqrt(1+4*zeta^4) - 2*zeta^2) / (tr));

% Controllore
nu = 1;
Kc = -1000;
Lin = minreal(zpk((Kc/s) * Gp * Ga * Gs * Gf));
%bodeplot(Lin)
figure(1)
[numLin,denLin] = tfdata(Lin,'v');
nyquist1(numLin,denLin)

figure(2)
myngridst(Tp,Sp)
nichols(Lin);

wc_des = 80;
%Lead network
wnorm_lead1 = 3;
md1 = 2;
zd1 = wc_des/wnorm_lead1;
Rd1 = (1+s/zd1)/(1+s/(md1*zd1));

%Zero network
wnorm_z = 20;
z = wc_des/wnorm_z;
Rz = (1+s/z);

% Controller
hold on
L = Lin*Rd1*Rz;
nichols(L)

% Step response

T = minreal(zpk(L/(1+L)));

figure(3)
step(T/(Gf*Gs),15)

figure(4)
bodemag(T)
