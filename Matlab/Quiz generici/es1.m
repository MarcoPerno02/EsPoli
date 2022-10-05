H = hilb(11);
b = zeros(11,1);
aus = 1
for i = 1:11
    b(i) = aus;
    aus =aus+2;
end
x = H\b;
x(4)