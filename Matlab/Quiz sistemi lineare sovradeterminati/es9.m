% Si consideri f(x)=x^2\log(1+x). Si costruisca il polinomio p(x) di grado 4 approssimante f nel senso dei minimi quadrati su 22 nodi equispaziati nell'intervallo [0,5], estremi inclusi. p(2) vale circa
clc
clear all

f = @(x) x.^2.*log(1+x);
x = linspace(0,5,22);
y = f(x);
c = polyfit(x, y, 4);
polyval(c, 2)

