f = @(x) x.^2.*sin(x);
fd = @(x) 2.*x.*sin(x) + x.^2.*cos(x);
x = linspace(0,1,9);
y = f(x);
f1 = fd(0);
fn = fd(1);
x_test = linspace(0,1,100);
y_corrette = f(x_test);
y_test = spline(x, [f1 y fn], x_test);
max(abs(y_corrette - y_test))