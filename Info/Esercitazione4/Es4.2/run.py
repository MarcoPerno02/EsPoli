strInput = input("Inserisci strInput: ")

for i in range(strInput.__len__()):
    if(strInput[strInput.__len__()-1-i] == "A" or strInput[strInput.__len__()-1-i] == "E" or strInput[strInput.__len__()-1-i] == "I" or strInput[strInput.__len__()-1-i] == "O" or strInput[strInput.__len__()-1-i] == "U"):
        print(strInput[strInput.__len__()-1-i], end="")

