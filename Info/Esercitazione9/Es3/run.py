def controllaQuadratoMagico(values):
    lista_sum = []
    
    #somma righe
    for i in range(len(values)):
        sum = 0
        for y in range(len(values[0])):
            sum+=values[i][y]
        lista_sum.append(sum)
    
    #somma colonne
    for y in range(len(values)):
        sum = 0
        for i in range(len(values[0])):
            sum+=values[i][y]
        lista_sum.append(sum)
        
    #somma diagonale1
    sum = 0
    for i in range(len(values)):
        sum+=values[i][i]
    lista_sum.append(sum)
    
    #somma diagonale2
    sum = 0
    for i in range(len(values)):
        sum+=values[4-1-i][4-1-i]
    lista_sum.append(sum)
    print(lista_sum)
    
    #controlla somme uguali
    i=0
    uguale = True
    while(i<len(lista_sum)-1 and uguale == True):
        if(lista_sum[i] != lista_sum[i+1]):
            uguale = False
        i+=1
    return uguale
    

values = []
for i in range(4):
    values.append([-1]*4)

i = 0
j = 0
num = -1
while(i<4):
    while(num<1 or num>16):
        num = int(input("Inserisci numero: "))
    
    if(num in values[0] or num in values[1] or num in values[2] or num in values[3]):
        print("Valore già inserito")
    else:
        print("Inserito")
        values[i][j] = num
        if(j==3):
            i+=1
            j=0
        else:
            j=j+1
    num=-1
print(values)
print(controllaQuadratoMagico(values))