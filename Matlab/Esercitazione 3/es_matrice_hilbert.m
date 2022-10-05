ord = 2:14;
for n = 1:length(ord)
    A = hilb(ord(n));
    b = sum(A,2);
    x = A\b;
    u = ones(ord(n),1);
    err(n) = norm(u-x,inf)/norm(u,inf);
    Kinf(n) = cond(A,inf);
end
