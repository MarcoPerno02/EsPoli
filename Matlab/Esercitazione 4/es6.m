tic
for n=100:100:500
    A = rand(n);

    B = ones(n, 1);
    x_matlab = A \ B;
    
    tic
    [Q, R] = qr(A);
    x_qr = R \ (Q' * B);
    err_rel1 = norm(x_matlab-x_qr, "inf")/norm(x_matlab);
    t1 = toc;

    tic
    [L, U, P] = lu(A);
    y = L\(P*B);
    x_pa = U\y;
    err_rel2 = norm(x_matlab-x_pa, "inf")/norm(x_matlab);
    t2 = toc;
    t1/t2
end


