%Il minimo valore assunto dalla funzione f(x)=\sin(3\cos(x))\log(x) sull'intervallo [1,5] vale circa:
f = @(x) sin(3.*cos(x)).*log(x);
x = linspace(1,5, 1000);
y = f(x);
min(y)