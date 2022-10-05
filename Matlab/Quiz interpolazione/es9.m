% Assegnati i dati (3,8), (6,4), (7,5), (14,5), (21,7), il polinomio interpolante i dati nel punto \text{e}^{0.7} vale:
clc
clear all

x = [3,6,7,14,21];
y = [8,4,5,5,7];
num = exp(0.7);
c = polyfit(x, y, 4);
polyval(c, num)