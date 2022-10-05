clc
clear all

a = -5;
b = 5;

f = @(x)1./(1.+x.^2);

% Grado del polinomio. I nodi da usare saranno n+1
for n=5:4:13
    % Dati d'interpolazione
    % Versione con nodi equispaziati
    %x = linspace(a, b, n+1);
    %y = f(x);
    
    % Versione con nodi di Chebyshev
    i = linspace(1, n+1, n+1);
    t = -cos(((2.*i-1).*pi)./(2.*(n+1)));
    x = (b-a)/2.*t+(b+a)/2;
    y = f(x);
    c = polyfit(x, y, n);

    % Verifica dei dati
    z = linspace(a, b);
    p = polyval(c, z);
    fz = f(z);

    plot(x, y, 'ko', z, fz,'r', z, p, 'b', 'LineWidth', 3)
    err_max = max(abs(fz - p));
    fprintf("%f\n", err_max);
    pause
end
