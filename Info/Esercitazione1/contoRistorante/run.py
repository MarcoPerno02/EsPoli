conto=0
nPers=0

print("Inserisci conto: ")
conto=float(input())
print("Inserisci nPers: ")
nPers=int(input())

mancia= conto*15/100
costoTot= mancia+conto
costCiascuno= costoTot/nPers
percConto= conto*100/costoTot
percMancia = 100-percConto

print("mancia: "+str(mancia))
print("costoTot: "+str(costoTot))
print("costCiascuno: "+str(costCiascuno))
print("percConto: "+str(percConto))
print("percMancia: "+str(percMancia))