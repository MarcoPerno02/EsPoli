clear all 
clc

M = magic(432); 
A = M + 10* eye(432);
b = sum(A,2);
x = A\b;
norm(b- A*x, "inf")