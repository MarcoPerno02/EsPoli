z = ones(10,1)
A = hilb(10);
n =size(A);
p=2;




w = z/norm(z);
lambda = p;
[L,U,P] = lu(A-p*eye(n));
for m = 1:4
    y = L\(P*w);
    z = U\y;
    lambda_p = p+1/(w'*z);
    w = z/norm(z);
    lambda = lambda_p;
end

autoval = eigs(A);
abs(autoval(1)-lambda)/autoval(1)