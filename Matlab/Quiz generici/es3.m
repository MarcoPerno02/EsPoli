f = @(x) x.^6-2.*x.^5+x-2;
n = 9;
x = linspace(0,1, 9);
y = f(x);
c = polyfit(x, y, 8)