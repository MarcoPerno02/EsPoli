% Insert data of the control design problem

clear all
close all
s = tf('s');
Gp = 25/(s^3+3.3*s^2+2*s);
Ga = 0.095;
Gs = 1;

% Performance requirements translation

Kd = 1; %requirement 1
Gf = 1/(Kd*Gs);

% Controller parameters constraints (requirements 2 and 3)
nu = 0;
Kc = 6%*10^(0.5/20); % |Kc|>=5.61

% Constraints derived from sinusoidal disturbances and transient
% requirements

Tp_max = 1.05;
Sp_max = 1.36;
wc_min = 0.66;
wc_max = 1.4;

% Let me compute the initial loop function Lin

Lin= Kc/(s^nu)*Gp*Ga*Gf*Gs;

% Plot Lin in the Nichols chart together with the forbidden region
% (corresponding to constraints on Tp and Sp)

figure(1)
myngridst(Tp_max,Sp_max)
nichols(Lin)

% Selection of wcdes

wcdes =0.8;

% Design of the lead/lag networks

% Lead Network

wnorm_Rd = 1.2; %in order to gain 45 degrees

zd = wcdes/wnorm_Rd;

md = 11;

Rd = (1+s/zd)/(1+s/(md*zd));

% Lag Network

wnorm_Ri = 100;

p_i = wcdes/wnorm_Ri;

mi = 10^(19.4/20);

Ri = (1+s/(mi*p_i))/(1+s/p_i);

% Final controller

Gc = (Kc/s^nu)*Rd*Ri;

% Final Loop function

L = minreal(zpk(Gc*Gp*Gf*Ga*Gs));

figure(1)
hold on
nichols(L)

% Step response of the obtained feedback control system

T = minreal(zpk(L/(1+L)));

figure(2)
step(T*1/(Gs*Gf));
