num=1
nPari=0
nDisp=0

while(num != ""):
    num = input("Inserisci num, spazio vuoto per uscire: ")
    if(num.isdigit()):
        num=int(num)
        if(num%2 == 0):
            nPari+=1
        else:
            nDisp+=1

print("NPari: "+str(nPari)+". NDisp: "+str(nDisp))
