%Siano date le funzioni
%f_1(x) = \frac{e^{3x}-1}{x},\ \ \ \ f_2(x) = 3 + \frac{9x}{2!} + \frac{27x^2}{3!} + \frac{81x^3}{4!} + \frac{243x^4}{5!}.
%Si calcoli il valore di entrambe nel punto \overline{x}=10^{-12} usando Matlab. Si consideri quindi f_2(\overline{x}) come valore esatto: qual e' l%errore relativo che commettiamo sostituendo a f_2(\overline{x}) il valore f_1(\overline{x})?
clear all
clc

x = 10.^(-12);
f1 = (exp(3.*x)-1)./x;
f2 = 3 + (9.*x./2) + ((27.*x.^2)/6) + ((81.*x.^3)/24) + ((243.*x.^4)/120);
err_rel = abs(f2-f1)/f1