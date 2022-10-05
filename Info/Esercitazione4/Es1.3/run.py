num=1
somma = 0
strSommeParziali = ""

while(num != ""):
    num = input("Inserisci num, spazio vuoto per uscire: ")
    if(num.isdigit()):
        num=int(num)
        somma+=num
        strSommeParziali+=str(somma)+" "

print("SommeParziali: "+strSommeParziali)
