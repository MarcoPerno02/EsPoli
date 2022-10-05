% Valutare y=3-\sqrt{9+x^2} per x=10^{-5}.
%Successivamente riformulare y al fine di evitare il fenomeno
%della cancellazione numerica e, assumendo come valore esatto
%quello che si ottiene mediante la riformulazione proposta,
%calcolare l'errore relativo associato a y. Esso vale all'incirca:
f = @(x) 3-(9+x.^2).^(1/2);
x = 10^-5;
y = f(x)
f_nuova = @(x) (-x.^2)./(3+(9+x.^2).^(1/2))
y_nuovo = f_nuova(x);
err_rel = abs(y-y_nuovo)/y_nuovo