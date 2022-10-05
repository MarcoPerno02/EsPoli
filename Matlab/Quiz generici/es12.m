f = @(x) 1./(x.^3+5);
x = linspace(0, 1, 8);
y = f(x);
c =polyfit(x, y, 7)