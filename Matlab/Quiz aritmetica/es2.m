format longE
x_aus = 2;
min = 100000;
for n=2:1:40
    f = 2^(n-1/2).*(1-(1-4.^(1-n).*x_aus.^(2)).^(1/2)).^(1/2);
    err_rel = abs(f-pi)/pi;
    if(err_rel<min)
        min = err_rel;
    end
    x_aus = f;
end
min