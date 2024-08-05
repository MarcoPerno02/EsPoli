% Controller design 
clear all
close all
s = tf('s')
Gp = 100/(s^3+5.5*s^2+4.5*s);
[nGp,dGp] = tfdata(Gp,'v');
Gs = 0.5;
Ga = 0.112;
Gr = 1;
Gd = 1;

Kd = 8;
Gf = 1/(Gs*Kd);
nu = 1;
Kc = 0.06 % magnitude of Kc is free

% Overshoot requirements translation
overshoot_up = 0.13;
damp = abs(log(overshoot_up))/sqrt(pi^2+(log(overshoot_up))^2);
Tp = 1/(2*damp*sqrt(1-damp^2));
Sp = 2*damp*sqrt(2+4*damp^2+2*sqrt(1+8*damp^2))/(sqrt(1+8*damp^2)+4*damp^2-1);

%Rise time requirements translation

tr_up = 1.8

wc_lw1 = (1/sqrt(1-damp^2)*(pi-acos(damp))*sqrt(sqrt(1+4*damp^4)-2*damp^2))/tr_up;

% Settling time requirement translation

ts_up = 6;

wc_lw2 = -log(0.05)/damp * sqrt(sqrt(1 + 4*damp^4) - 2*damp^2)/ts_up;


%%%%%%%%%%%

Lnyq = Kc/s^nu*Gp*Ga*Gs*Gf;

[nLnyq,dLnyq] = tfdata(Lnyq,'v');

figure(1)
nyquist1(nLnyq,dLnyq);

figure(2)
myngridst(Tp,Sp)
omega = logspace(-2,4,500);
nichols(Lnyq,omega)

% Design solution 1 (Zro network + Lead)

% Range di wcdes [1.07,19]
wcdes = 1.2; %125 gradi di fase da recuperare

% Zero network

wnorm = 60;

z = wcdes/wnorm;

Rz = (1+s/z);

% Lead networks

wnorm1 = 2;
zd1 = wcdes/wnorm1;
md1 = 4; 

Rd1 = (1+s/zd1)/(1+s/(md1*zd1));

% wnorm1 = 1.2;
% zd1 = wcdes/wnorm1;
% md1 = 16; 
% 
% Rd1 = (1+s/zd1)/(1+s/(md1*zd1));

% Controller

Gc = Kc/s^nu*Rz*Rd1;

[nGc,dGc] = tfdata(Gc,'v');

L = Gc*Gp*Ga*Gs*Gf;

%figure(3)
myngridst(Tp,Sp)
omega = logspace(-3,4,500);
nichols(L,omega)

figure(3)
T = minreal(zpk(L/(1+L)));
Gry = T*1/(Gs*Gf);
t = [0:0.001:10];
step(Gry,t)

figure(4)
T = minreal(zpk(L/(1+L)));
%Gry = T*1/(Gs*Gf);
t = [0:0.001:100];
step(T,t)

figure(5);
bodemag(T);

S = minreal(zpk(1/(1+L)));
figure(6);
bodemag(S);

[magTws,phTws] = bode(T,60)
magTwsdB = 20*log10(magTws)

S = minreal(zpk(1/(1+L)));

[magSwp,phSwp] = bode(S,0.03)
magSwpdB = 20*log10(magSwp)