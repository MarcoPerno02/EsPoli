%Sia f(x)=\sqrt{1+x^2} e sia p(x) il polinomio interpolante f nell'intervallo [0,5] in 5 nodi di Chebyshev. Quanto vale, approssimato alla quarta cifra decimale, il coefficiente del temine di grado 1 del polinomio?

%N.B. Si ricorda che n+1 nodi di Chebyshev nell'intervallo [-1,1] sono dati dalla formula seguente:
% t_i = -\cos \left(\frac{(2i-1)\pi}{2(n+1)}\right), \quad i=1,\ldots,n+1

f = @(x) (1.+x.^2).^(1/2);
a = 0;
b = 5;
n = 4;
i = 1:n+1; % 5 nodi così
t = -cos(((2.*i-1).*pi)./(2.*(n+1))); 
x = (b-a)/2.*t+(b+a)/2;
y = f(x);

c = polyfit(x, y, n);
c(end-1)
