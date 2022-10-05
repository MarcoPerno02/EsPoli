def countLowels(stringa):
    cont = 0
    for lettera in stringa:
        lettera = lettera.upper()
        if(lettera == "A" or lettera == "E" or lettera == "I" or lettera == "O" or lettera == "U"):
            cont+=1
    return cont

stringa = input("Inserisci stringa: ")
cont = countLowels(stringa)
print("Numero vocali: ", cont)