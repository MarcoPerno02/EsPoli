import numpy as np

lista = []
for i in range(10):
    lista.append(int(np.round(np.random.rand()*100)))
print(lista)
print("----------")

for i in range(0, 10, 2):
    print(lista[i])
print("----------")

for i in range(0, 10):
    if(lista[i]%2 == 0):
        print(lista[i])
print("----------")

for i in range(0, 10):
    print(lista[lista.__len__()-1-i])
print("----------")

print(lista[0])
print(lista[-1])