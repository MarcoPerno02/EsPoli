clear all
close all
s = tf('s');

Gp = -30/(s*(s^2 + 3*s + 2));
p = 1;
Gs = 10;
Ga = 0.06;
Gr = 1;
Gd = 1;
Da0 = 2.5e-3;
Dp0 = 8.5e-3;
as = 5e-2;
ws = 40;
Kd = 10;
R0 = 1;
er_inf = 2.5e-1;
eda_inf = 1e-2;
edp_inf = 0.94;
eds_inf = 1.6e-5;
tr = 2.5;
ts5 = 13;
ts_alpha = 0.05;
s_cappello = 0.14;


% 1
Gf = 1/(Kd*Gs);

% 2
Kp = -15;
Kc_tmp_2 = abs((Kd^2*R0)/(Kp*er_inf*Ga));

% 3
Kc_tmp_3 = abs((Kp*Da0)/(Kp*Ga*Gs*Gf*eda_inf));

% 4
Kc_tmp_4 = abs((2*Dp0)/(Kp*Ga*Gs*Gf*edp_inf));

% 5
MtHF = (eds_inf*Gs)/as;
wc_max = 1.13;

% 6 7 8
zeta = abs(log(s_cappello)) / sqrt(pi^2 + log(s_cappello)^2);
Tp_max = 1 / (2*zeta*sqrt(1 - zeta^2));
Sp_max = (2*zeta*sqrt(2 + 4 * zeta^2 + 2*sqrt(1 + 8 * zeta^2))) / (sqrt(1 + 8 * zeta^2) + 4 * zeta^2 -1);
wc_tsa = (-log(ts_alpha) / zeta) * ((sqrt(sqrt(1 + 4 * zeta^4) - 2 * zeta^2))/(ts5));
wc_tr = ((pi - acos(zeta))/(sqrt(1 - zeta^2))) * ((sqrt(sqrt(1 + 4 * zeta^4) - 2 * zeta^2))/(tr));

%bode
Kc = -0.25;
nu=1;
Lin = minreal(zpk((Kc/s^nu)*Ga*Gs*Gp*Gf));

%figure(1)
%bodeplot(Lin);

figure(1)
[numLin,denLin] = tfdata(Lin,'v');
nyquist1(numLin,denLin)

Tp_max = 1.11;
Sp_max = 1.43;
figure(2)
myngridst(Tp_max,Sp_max)
nichols(Lin);

% Selection of wcdes
wcdes = 0.9;

%Zero network

wnorm_z = 30;

z = wcdes/wnorm_z;

Rz = (1+s/z);

% Lead Network
wnorm_Rd = 2.2; %in order to gain 45 degrees

zd = wcdes/wnorm_Rd;

md = 6;

Rd = (1+s/zd)/(1+s/(md*zd));

% Final controller

Gc = (Kc/s^nu)*Rd*Rz;

% Final Loop function

L = minreal(zpk(Gc*Gp*Gf*Ga*Gs));

figure(2)
hold on
nichols(L)

% Step response

T = minreal(zpk(L/(1+L)));

figure(3)
time = [0:2.5/100:100];
step(T/(Gf*Gs),time)

[numGp,denGp] = tfdata(Gp,'v');
[numGc,denGc] = tfdata(Gc,'v');

figure(4)
bodemag(T)