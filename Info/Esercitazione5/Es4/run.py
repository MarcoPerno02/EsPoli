num = int(input("Inserisci num: "))
fat = 2
while(num != 1):
    if(num % fat == 0):
        print(fat)
        num/=fat
    else:
        fat+=1
