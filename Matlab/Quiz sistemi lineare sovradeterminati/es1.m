% Si considerino le seguenti informazioni riguardanti la velocita' di un corpo in funzione del tempo:
% Tempo(s): [0, 8, 18]
% Velocita'(m/s): [44, 43, 67]
% Approssimando i dati mediante la retta dei minimi quadrati, che velocita' ha il corpo dopo 2 secondi?
T = [0, 8, 18];
V = [44, 43, 67];
c_star = polyfit(T, V, 1);
aus = polyval(c_star, [2])
