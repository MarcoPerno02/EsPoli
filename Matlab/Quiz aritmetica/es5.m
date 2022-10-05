clc
clear all

n = linspace(1,14, 14);
h = zeros(14, 1);
for i = 1:14
    h(i)=10^(-n(i));
end

f = @(x)(1-cos(x))./(x.^2);
y = f(h)
