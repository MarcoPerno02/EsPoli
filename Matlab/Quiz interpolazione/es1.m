% Assegnati i dati (-1,4), (1,3), (7,10), (9,10), (19,9), la spline di tipo not-a-knot interpolante i dati nel punto \log 0.9 vale:
format long e

x = [-1 1 7 9 19];
y = [4 3 10 10 9];

z = log(0.9);

s = spline(x, y, z)