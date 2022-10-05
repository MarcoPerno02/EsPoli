f = @(x) exp(2.*x)-exp(3.*x);
x = linspace(-2,1,14);
y = f(x);
c = polyfit(x, y, 6);
polyval(c, 0)