import numpy as np

print("Inserisci base: ")
base = float(input())
print("Inserisci altezza: ")
altezza = float(input())

print("Area: "+str(base*altezza)+". Perimetro: "+str((base+altezza)*2))
print("Diagonale: "+str(np.sqrt(np.power(base, 2)+np.power(altezza, 2))))
