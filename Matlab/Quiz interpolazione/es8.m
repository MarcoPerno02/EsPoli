f = @(x) ((1.-x.^2).*x.^3);

a = 0;
b = 1;

n=6;
x = linspace(a, b, n+1);
y = f(x);
c = interp1(x, y)

z = 