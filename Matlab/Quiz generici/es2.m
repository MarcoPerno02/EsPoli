f = @(x) sin(3.*cos(x)).*log(x);
x  =linspace(1,5, 1000);
y = f(x);
min(y)