num=1
min=99999999
max=-99999999

while(num != ""):
    num = input("Inserisci num, spazio vuoto per uscire: ")
    if(num.isdigit()):
        num=int(num)
        if(max<num):
            max=num
        if(min>num):
            min=num

print("Min: "+str(min)+". Max: "+str(max))
