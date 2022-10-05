clc
clear all
close all

a =-1;
b = 1;
f = @(x) (1.-x.^2).^(5/2);
df = @(x) (5/2).*(-2.*x).*(1.-x.^2).^(3/2);
for k=2:1:5
    n = 2^k;
    i = 0:n;
    x = -1.+2.*i./n;
    y=f(x);
    z = linspace(a, b);
    
    s = spline(x, y, z);
    s1 = spline(x, [df(x(1)), y, df(x(end))], z);
    fz = f(z);

    figure(1)
    plot(x, y, 'ko', z, fz,'r', z, s, 'g', z, s1, 'b', 'LineWidth', 3)
    legend("Dati di interpolazione", "Funzione studiata", "Spline", "Spline cubica vincolata")

    err_max = max(abs(fz-s))
    err_max1 = max(abs(fz-s1))

    figure(2);
    semilogy(z, abs(fz-s), "g", z, abs(fz-s1), 'b', 'LineWidth', 3)
    legend("Errore spline", "Errore spline vincolata")
    pause

end
