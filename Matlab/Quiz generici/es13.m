format long e
H = hilb(11);
b = ones(11, 1);
aus = 1;
for i=1:11
    b(i) = aus;
    aus = aus+2;
end
x = H\b