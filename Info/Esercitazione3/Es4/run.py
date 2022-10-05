print("Inserisci mese: ")
mese = int(input())
print("Inserisci giorno: ")
giorno = int(input())

if(mese >= 1 and mese <= 3):
    stagione = "Winter"
elif(mese >= 4 and mese <= 6):
    stagione = "Spring"
elif(mese >= 7 and mese <= 9):
    stagione = "Summer"
else:
    stagione = "Fall"

if(mese % 3 == 0 and giorno == 21 ):
    if(stagione  == "Winter"):
        stagione = "Spring"
    elif(stagione == "Spring"):
        stagione = "Summer"
    elif(stagione == "Sumer"):
        stagione = "Fall"
    else:
        stagione = "Winter"

print(stagione)

