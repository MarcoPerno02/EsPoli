clc
clear all

a = -5;
b = 5;

f = @(x) 1./(1+x.^2);

%grado
for n=20:4:28

%dati di interpolazione
x = linspace(a, b, n);
xx = linspace(a, b, n*4);
y = f(x);

yy = spline(x, y, xx);

plot(x, y, 'o', xx, yy, 'LineWidth', 3)
err=max(abs(f(xx) - yy));
pause
end