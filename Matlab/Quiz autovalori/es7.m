% Data la matrice A generata con il comando A=pascal(8), quanto vale all'incirca la distanza in norma 2 di A dall'insieme delle matrici di rango 5
format long e

A = pascal(8);
d = svd(A)
d(6)