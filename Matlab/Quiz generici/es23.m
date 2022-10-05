f = @(x) exp(x.^2);
x = linspace(0, 1, 7);
y = f(x);
c = polyfit(x, y, 6);
x_test = linspace(0, 1, 150);
y_eval = f(x_test);
y_test = polyval(c, x_test);
max(abs(y_eval-y_test))