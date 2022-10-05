% Si vuole determinare il polinomio esponenziale di secondo grado p_e(x)=a\text{e}^{2x}+b\text{e}^{x}+c che approssima nel senso dei minimi quadrati la nube di punti (x,y): x=[0.34 0.19 0.25 0.61 0.47 0.35 0.83] y=[0.58 0.54 0.91 0.28 0.75 1.17 0.38] Il coefficiente a di p_e vale circa:
% (suggerimento: si effettui la sostituzione z=\mathrm{e}^x)

clc
clear all
x=[0.34 0.19 0.25 0.61 0.47 0.35 0.83];
y=[0.58 0.54 0.91 0.28 0.75 1.17 0.38];
z = exp(x);
c = polyfit(z, y, 2)