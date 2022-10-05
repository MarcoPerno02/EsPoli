import numpy as np

def calcolaContoBancario(saldo, anni, interssi_perc):
    for i in range(anni):
        saldo+=saldo/100*interssi_perc
    return np.round(saldo, 2)

saldo=0.
anni=0
interessi_perc=0.
exit = ""

while(exit != "-1"):
    saldo = float(input("Inserisci saldo: "))
    anni = int(input("Inserisci anni: "))
    interessi_perc = float(input("Inserisci anni: "))
    saldo = calcolaContoBancario(saldo, anni, interessi_perc)
    print("Saldo: ", saldo)
    exit = input("Inserisci -1 per uscire, per continuare digita invio: ")