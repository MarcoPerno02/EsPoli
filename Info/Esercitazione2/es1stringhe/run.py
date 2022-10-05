import numpy as np

num1 = int(input("Inserisci num1: "))
num2 = int(input("Inserisci num2: "))

print("Somma: "+str(num1+num2))
print("Differenza: "+str(num1-num2))
print("Prodotto: "+str(num1*num2))
print("Val medio: "+str((num1+num2)/2))
print("Distanza: "+str(np.abs(num1-num2)))
print("Max: "+str(max(num1, num2)))
print("Min: "+str(min(num1, num2)))