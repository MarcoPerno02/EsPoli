function [d,m] = qr_base(A, tol, m_max)

for m=1:m_max
    [Q,R] = qr(A);
    A=R*Q;
    if(norm(tril(A, -1), "inf")<=tol)
        break
    end
end

d=diag(A);

