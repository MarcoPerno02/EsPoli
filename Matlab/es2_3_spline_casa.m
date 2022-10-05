clc
clear all
close all

a = -5;
b = 5;
f = @(x) 1./(1.+x.^2);

for n=6:4:14 % Striamo indicando il numero dei nodi
    x = linspace(a, b, n);
    y = f(x);

    z = linspace(a, b);
    s = spline(x, y, z);
    fz = f(z);
    plot(x, y, 'ko', z, fz,'r', z, s, 'b', 'LineWidth', 3)
    legend("Dati di interpolazione", "Funzione di Runge", "Spline cubuca not-a-knot")
    errmax = max(abs(fz - s))
    pause
end

