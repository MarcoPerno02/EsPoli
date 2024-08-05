clear all
close all
s = tf('s');

Gp = 40/(s^2+3*s+4.5);
Kd = 1;
Gs = 1;
Ga = -0.09;
R0 = 1;
er_inf = 3.5e-1;

Da0 = 8.85e-3;
Dp0 = 3e-3;
as = 1e-2;

eda_inf = 1.75e-2;
edp_inf = 1e-3;
eds_inf = 2e-4;

tr = 2.5;
ts5 = 10;
a_perc = 0.05;
s_cappello = 0.08;

Gf = 1 /(Kd * Gs);

Kp = 1 * (40/(0 + 0 + 4.5));
Kc = abs((Kd^2*R0)/(Kp* Ga * er_inf));

Kc_p = Dp0/(Kp * Ga * edp_inf);

Kc_tmp = 3.8;

zeta = abs(log(s_cappello))/sqrt(pi^2+log(s_cappello)^2);
Tp_max = 1 / (2*zeta*sqrt(1-zeta^2));  
Sp_max = (2*zeta*sqrt(2+4*zeta^2+2*sqrt(1+8*zeta^2)))/(sqrt(1+8*zeta^2)+4*zeta^2-1);
wc_tsa = (-(log(a_perc)/zeta)*sqrt(sqrt(1+4*zeta^4)-2*zeta^2))/ts5;
wc_tr = ( ((pi - acos(zeta))/(sqrt(1-zeta^2))) * sqrt(sqrt(1+4*zeta^4)-2*zeta^2))/tr;

%* Inizio Controllore *%

nu=1;
% Kc = 3.8;
% Lin= Kc/(s^nu)*Gp*Ga*Gf*Gs;
% bode(Lin), grid -> ottengo Kc negativo
% Plot Lin in the Nichols chart together with the forbidden region
% (corresponding to constraints on Tp and Sp)
Kc = -3.8;
Lin= Kc/(s^nu)*Gp*Ga*Gf*Gs;

figure(1)
myngridst(Tp_max,Sp_max)
nichols(Lin)

wcdes = 3;

% Lead Network
wnorm_Rd = 1.2;
zd = wcdes/wnorm_Rd;
md = 16;
Rd = (1+s/zd)/(1+s/(md*zd));

% Final controller

Gc = (Kc/s^nu)*Rd*Rd;

% Final Loop function

L = minreal(zpk(Gc*Gp*Gf*Ga*Gs));

figure(1)
hold on
nichols(L)

% Step response of the obtained feedback control system

T = minreal(zpk(L/(1+L)));

figure(2)
step(T*1/(Gs*Gf));
