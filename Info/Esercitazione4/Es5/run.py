num = int(input("Inserisci num: "))

for i in range(2, num+1):
    numPrimo = True

    y=2
    while(numPrimo == True and y<i):
        
        if(i % y == 0):
            numPrimo = False
        y+=1
    
    if(numPrimo == True):
        print(i)

