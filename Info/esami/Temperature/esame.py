# var1 = [{"ss": "ss", "aa": "aa", ...}, {...}, ...]
# var2 = [{"ss": "ss", "aa": "aa", ...}, {...}, ...]
import operator
parole_importanti = [{"parola": "aaa", "conteggio": 0}, {...}, ..]
f1 = open("libro.txt")
f2 = open("testo.txt")

riga = f1.readline()
while riga != "":
    parola_importante = riga.rstrip()
    # Aggiungo le parole_importanti
    parole_importanti.append({"parola": parola_importante, "cont": 0})
    riga = f2.readline()

riga = f2.readline()
while riga != "":
    parole = riga.rstrip()
    for i in range(len(parole)):
        for j in range(len(parole_importanti)):
            # Verifico se la parole[i] è dentro alla lista parole_importanti
            if(parole_importanti[j]["parola"] == parole[i]):
                parole_importanti[j]["conteggio"] += 1
    riga = f2.readline()

parole_importanti.sort(key=operator.itemgetter('conteggio'))
for i in range(10):
    print(parole_importanti[i]["parola"])
