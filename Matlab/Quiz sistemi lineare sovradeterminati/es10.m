%Supporre di avere effettuato le seguenti misurazioni:

%in x_1 = 0   y_1 = 1

%in x_2 = 1   y_2 = 2

%in x_3 = 2   y_3 = 4

%in x_4 = 3   y_4 = 8

%Determinare i coefficienti della somma esponenziale di ordine uno f(x) = \sum_{k=0}^1 a_k \text{e}^{kx} che meglio approssima nel senso dei minimi quadrati i dati assegnati e la norma del residuo a essa corrispondente.

%(suggerimento: effettuare la sostituzione z=\mathrm{e}^x)
x = [0, 1, 2, 3];
y = [1, 2, 4, 8];
z = exp(x);
c = polyfit(z, y, 1)
norm(polyval(c, z)-y, 2)