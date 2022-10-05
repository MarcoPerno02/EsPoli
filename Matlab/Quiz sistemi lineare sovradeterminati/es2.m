% Supporre di aver effettuato le seguenti misurazioni:
% in x_1 = 0  y_1 = 1;
% in x_2 = 1  y_2 = 2 ;
% in x_3 = 2  y_3 = 4.
% Quanto valgono i coefficienti a e b della retta di regressione y = ax+b?
X = [0, 1, 2];
Y = [1, 2, 4];
c = polyfit(X, Y, 1)