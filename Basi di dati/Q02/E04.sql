E = sigma(tipo <> fiera)
B = EDIZIONE
D = sigma(data <= '2019-06-31' AND data <= '2019-01-01')
F = NATURALJOIN
A = EDIZIONE
C = sigma(data <= '2019-06-31' AND data <= '2019-01-01')
H = -
G = LUOGO
I = sigma(CapienzaMax > 500)
L = NATURALJOIN
M = PI(nome, citta)