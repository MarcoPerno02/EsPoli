strInput = input("Inserisci stringa: ")
numCifre = 0

for i in range(strInput.__len__()):
    if(strInput[i].isdigit()):
        numCifre+=1

print("NumCifre :"+str(numCifre))
