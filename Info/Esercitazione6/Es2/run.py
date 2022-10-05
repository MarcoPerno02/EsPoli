def countWords(stringa):
    cont = 1
    check_next_space = False
    for i in range(len(stringa)):
        if(stringa[i]==" " and check_next_space==False):
            check_next_space=True
        elif(stringa[i]!=" " and check_next_space==True):
            cont+=1
            check_next_space=False
    if(len(stringa) == 0):
        cont=0
    return cont

stringa = input("Inserisci stringa: ")
cont = countWords(stringa)
print("Numero parole: ", cont)