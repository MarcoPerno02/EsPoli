num_esami = -1
while(num_esami <= 0):
    print("Inserisci numero esami: ")
    num_esami = input()
    
    if(num_esami.isdigit()):
        num_esami = int(num_esami)
    else:
        num_esami = -1

stop = "0"

while(stop == "0"):
    somma = 0
    for i in range(num_esami):
        ok = False
        while(ok == False):
            x = input("Inserisci voto " + str(i+1)+" esame: ")
            if(x.isdigit() and int(x)>0):
                somma+=int(x)
                ok=True
        
    print("La media dello studente è: " + str(somma/num_esami))
    stop = input("Inerire 0 per calcolare media di un altro studente, 1 per uscire: ")