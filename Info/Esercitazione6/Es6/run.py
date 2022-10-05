biglietti = 100
n_clienti = 0

while( biglietti > 0 ):
    n_acquisto = int(input("Inserire num biglietti da acquistare: "))

    if(n_acquisto > 4):
        print("Quantita non permessa")
    else:
        if(n_acquisto <= biglietti):
            print("Biglietti acquistati")
            n_clienti+=1
            biglietti-=n_acquisto
        else:
            print("Quantita non disponibile")

print("Biglietti terminati. Num clienti ", n_clienti)


