f = @(x) exp(-x.^2).*sin(x);
x = linspace(0,1, 1000);
y = f(x);
max(y)