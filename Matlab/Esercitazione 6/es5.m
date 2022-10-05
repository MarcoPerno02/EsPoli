
format long e
n = 10;
H = hilb(n);
m_max = 100;
tol = 1.0e-14;

[d,m]  = qr_base(H, tol, m_max)
err = abs(sort(d)-sort(eig(H)))

%%%%%%%%%%%%%%

A = [0 0 2; 1 0 1; 0 1 1];
for m1=1:m_max
    [Q, R] = qr(A);
    A = R*Q;
end
A
eig(A)