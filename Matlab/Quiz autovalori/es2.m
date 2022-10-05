% Sia data la matrice A di ordine n=12 le cui componenti sono definite come
% a_{ij}=\left\{\begin{array}{ll}2i & \text{se }i=j\\-2/j & \text{se }i<j\\2/j & \text{se }i>j\end{array}\right.
% Il suo raggio spettrale (cioe' il massimo dei moduli degli autovalori) e' circa

n=100;
A = ones(n,n);
for i=1:n
    for j=1:n
        A(i,j) = (1+i+j)./(1+abs(i-j));
    end
end

[X, D] = eigs(A, 1, 100);
norm(X, 1)

