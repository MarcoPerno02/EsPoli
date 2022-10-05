function [lambda,w,m] = potenze(A,z,tol,m_max)

w=z/norm(z);
lambda(1) = 0;

for m=1:m_max
    z=A*w;
    lambda(m+1) = w'*z;
    w=z/norm(z);

    if(abs(lambda(m+1) - lambda(m)) <= tol*abs(lambda(m+1)))
        break
end

end