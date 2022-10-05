posti = [[10,10,10,10,10,10,10],
         [10,10,10,10,10,10,10],
         [10,10,10,10,10,10,10],
         [10,20,20,20,20,20,10],
         [10,20,20,20,20,20,10],
         [20,30,30,30,30,30,20],
         [30,40,40,40,40,40,30],]
input_str = " "
while(input_str != ""):
    input_str = input("Inserire 1 per scegliere posto, 2 per un posto casuale in base al prezzo, invio per uscire: ")
    if(input_str == "1"):
        x = int(input("Inserire coordinata x da 0 a 6: "))
        y = int(input("Inserire coordinata y da 0 a 6: "))
        if(posti[x][y] != 0):
            print("Prenotato. Costo: ", posti[x][y])
            posti[x][y] = 0
        else:
            print("Posto già prenotato")
    elif(input_str == "2"):
        costo = int(input("Inserire costo tra 10, 20, 30, 40: "))
        i = 0
        trovato = False
        while(i!=len(posti) and trovato == False):
            y=0
            while(y!=len(posti[0]) and trovato == False):
                if(posti[i][y] == costo):
                    trovato = True
                else:
                    y+=1
            if(trovato != True):
                i+=1
        if(trovato == True):
            print("Posto prenotato. X: ", i, " Y:", y)
            posti[i][y] = 0
        else:
            print("Nessun posto trovato per quella fascia di prezzo.")
    print("Posti: ")
    print('\n'.join(['\t'.join([str(cell) for cell in row]) for row in posti]))
        
