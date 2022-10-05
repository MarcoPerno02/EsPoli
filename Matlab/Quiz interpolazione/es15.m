format longE
f = @(x) ((exp(x)-1)./x)^(1/2);
x = 10^-11;
y = f(x)
f_nuova = @(x) ((x+x.^2./2)./x)^(1/2);
y_nuovo = f_nuova(x);
err_rel = abs(y-y_nuovo)/y_nuovo