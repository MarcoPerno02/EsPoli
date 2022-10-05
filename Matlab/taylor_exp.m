function [y,i] = taylor_exp(x,tol)
y = 0;
i = 0;

termine_sviluppo = 1;
while termine_sviluppo >= tol
    y = y + termine_sviluppo;
    i = i + 1;
    termine_sviluppo = x^i/factorial(i);
end