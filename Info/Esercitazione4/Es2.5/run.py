strInput = input("Inserisci stringa: ")
strRis = ""

for i in range(strInput.__len__()):
    if(strInput[i].lower() == "a" or strInput[i].lower() == "e" or strInput[i].lower() == "i" or strInput[i].lower() == "o" or strInput[i].lower() == "u"):
        strRis+=str(i)+" "

print("Posizioni vocali :"+strRis)
