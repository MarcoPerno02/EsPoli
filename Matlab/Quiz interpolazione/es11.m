% Si consideri f(x)=1+x^2\log(2+x). Si costruisca il polinomio p(x) interpolante f(x) nei punti di ascissa x\in\lbrace 0.3,0.6,0.9,1.2,1.5\rbrace. Il valore di |f(3)-p(3)| e' circa
clc
clear all


f = @(x) 1+x.^2.*log(2+x);
x = [0.3,0.6,0.9,1.2,1.5];
y = f(x);
c = polyfit(x,y,4);
abs(f(3)-polyval(c,3))