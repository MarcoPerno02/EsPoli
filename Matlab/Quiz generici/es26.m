f = @(x) sin(x);
x = linspace(0,1,9);
y = f(x);
x_test = linspace(0,1,180);
y_eval = f(x_test);
y_test = spline(x, y, x_test);
max(abs(y_eval-y_test));

0.1* 10 + 0.50*10^4