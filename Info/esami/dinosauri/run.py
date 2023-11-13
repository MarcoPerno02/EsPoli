def leggiFile(mazzo1, mazzo2):
    try:
        f = open("mazzo.txt", "r")
        i = 0
        riga = f.readline()
        while riga != "":
            riga = riga.rstrip()
            if riga == "Rosso":
                riga = 5
            elif riga == "Giallo":
                riga = 3
            else:
                riga = 1
            if i % 2 == 0:
                mazzo1.append(riga)
            else:
                mazzo2.append(riga)
            riga = f.readline()
            i+=1
        f.close()
    except IOError:
        print("Errore nella lettura del file")

def gioca(mazzo1, mazzo2, punt1, punt2):
    punt_carte_in_campo = 0
    for i in range(0, 15):
        print("Mani n° ", i+1)
        if(mazzo1[i] == 5):
            carta = "Rossa"
        elif(mazzo1[i] == 3):
            carta = "Gialla"
        else:
            carta = "Verde"
        print("carta giocatore 1: ", carta)
        if(mazzo2[i] == 5):
            carta = "Rossa"
        elif(mazzo2[i] == 3):
            carta = "Gialla"
        else:
            carta = "Verde"
        print("carta giocatore 2: ", carta)


        if(mazzo1[i] > mazzo2[i]):
            print("Risultato: vince la mano il giocatore 1")
            punt1 += mazzo1[i] + mazzo2[i] + punt_carte_in_campo
            punt_carte_in_campo = 0
        elif(mazzo1[i] < mazzo2[i]):
            print("Risultato: vince la mano il giocatore 2")
            punt2 += mazzo1[i] + mazzo2[i] + punt_carte_in_campo
            punt_carte_in_campo = 0
        else:
            print("Pareggio")
            punt_carte_in_campo += mazzo1[i] + mazzo2[i]
        print("Punteggio giocatore 1: ", punt1)
        print("Punteggio giocatore 2: ", punt2)

    if(punt1 > punt2):
        print("Vince il giocatore 1 con ", punt1, "punti")
    else:
        print("Vince il giocatore 2 con ", punt2, "punti")

#####################################

punt1 = 0
punt2 = 0
mazzo1 = []
mazzo2 = []
leggiFile(mazzo1, mazzo2)
gioca(mazzo1, mazzo2, punt1, punt2)