num=1
numPrec = None
strNumAdiac = ""

while(num != ""):
    num = input("Inserisci num, spazio vuoto per uscire: ")
    if(num.isdigit()):
        num=int(num)
        if(numPrec == None):
            numPrec=num
        else:
            if(num == numPrec):
                strNumAdiac+=str(num)+" "
            numPrec=num

print("NumAdiacenti: "+strNumAdiac)
