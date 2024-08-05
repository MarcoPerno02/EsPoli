Kd = 1;
Gs = 1;
Ga = 0.014;
R0 = 1;
er_inf = 1.5e-1;

Gf = 1 /(Kd * Gs);

Kp = 1 * (100/(0 + 0 + 4.5));
Kc = abs((Kd^2*R0)/(Kp* Ga * er_inf));