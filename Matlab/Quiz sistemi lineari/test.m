clc
clear all
format longE
A = [-1, 0 ,3; 1, 2, -1; 0, 0, 2];
[autovet, D] = eig(A);
diag = autovet*D*inv(autovet);
D_aus = inv(autovet)*A*autovet;
A = [-1,0,0;0,1/3,0;0,0,2/5];
[d] = eigs(A);
[U, S, V] = svd(A);
212.41*50.326;
f = @(x) sin(4*x);
x = [0, pi/8, pi/4];
y = f(x);
c = polyfit(x,y,2);
polyval(c, pi/16);

%%%%%%%%%%%%%%%
A = pascal(8);
d = svd(A)
