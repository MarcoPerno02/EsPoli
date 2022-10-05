import numpy as np

lista = []

for i in range(20):
    lista.append(int(np.random.rand()*100))

lista = np.sort(lista)
print(lista)