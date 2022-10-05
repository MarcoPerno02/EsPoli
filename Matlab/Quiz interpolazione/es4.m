% Calcolare il polinomio interpolante la funzione f(x)=\arctan(x (x+1)) in 8 punti equispaziati dell'intervallo [0,1]. Quanto vale l'errore di interpolazione nei punti 0.5 e 0.7?
f = @(x) (atan(x.*(x+1)));

a = 0;
b = 1;
n = 7;
x = linspace(a, b, n+1);
y = f(x);
c = polyfit(x, y, n);

p = polyval(c, [0.5, 0.7]);
err1 = abs(f(0.5) - p(1))
err2 = abs(f(0.7) - p(2))