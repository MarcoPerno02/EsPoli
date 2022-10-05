format longE

f1 = @(x) 5-(25+x.^2).^(1/2);
f2 = @(x) (-x.^2)/(5+(25+x.^2).^(1/2));

x = 10^-6;
y1 = f1(x);
y2 = f2(x);
err_rel = abs(y1-y2)/y2