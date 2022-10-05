import numpy as np

def sumWithoutTheSmallest(lista):
    lista = np.sort(lista)
    sum = 0
    for i in range(1, len(lista)):
        sum+=lista[i]
    return sum

lista = [10, 20, 30, 2, 5]
print(sumWithoutTheSmallest(lista))


