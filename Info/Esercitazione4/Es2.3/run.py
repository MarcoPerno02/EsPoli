str = input("Inserisci stringa: ")
strRis = ""

for i in range(str.__len__()):
    if(str[i].lower() == "a" or str[i].lower() == "e" or str[i].lower() == "i" or str[i].lower() == "o" or str[i].lower() == "u"):
        strRis+="_"
    else:
        strRis+=str[i]

print("Solo vocali :"+strRis)
