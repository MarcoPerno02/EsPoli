format longG
p=1;
z = ones(7,1)
A = hilb(7)
n = size(A);
w = z/norm(z);
lambda = p;
[L,U,P] = lu(A-p*eye(n));
for m = 1:18
    y = L\(P*w);
    z = U\y;
    lambda_p = p+1/(w'*z);
    w = z/norm(z);
    lambda = lambda_p;
end

autoval = eigs(A)
abs(autoval(1)-lambda)/autoval(1)

