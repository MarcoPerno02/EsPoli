def calcolaSussidio(reddito, n_figli):
    sussidio = 0
    if(reddito>30000 and reddito<=40000 and n_figli>=3):
        for i in range(n_figli):
            sussidio+=1000
    elif(reddito>20000 and reddito<=30000 and n_figli>=2):
        for i in range(n_figli):
            sussidio+=1500
    elif(reddito<=20000):
        for i in range(n_figli):
            sussidio+=2000
    return sussidio

reddito=0
n_figli=0
exit = ""

while(exit != "-1"):
    reddito = int(input("Inserisci reddito: "))
    n_figli = int(input("Inserisci n_figli: "))
    sussidio = calcolaSussidio(reddito, n_figli)
    if(sussidio == 0):
        print("Non ti spetta nessun sussidio")
    else:
        print("Sussidio: ", sussidio)
    exit = input("Inserisci -1 per uscire, per continuare digita invio: ")