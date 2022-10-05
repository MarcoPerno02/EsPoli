v = linspace(1, 30, 30);
somma = 0;
for i=1:30
    somma = somma + 1./(v(i)).^(1/2);
end
somma
