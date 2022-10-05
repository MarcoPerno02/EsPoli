def merge(a, b):
    i = 0
    lista_merge = []
    while(i < len(a) and i < len(b)):
        lista_merge.append(a[i])
        lista_merge.append(b[i])
        i+=1
    if(i == len(a) and i < len(b)):
        for y in range(i, len(b)):
            lista_merge.append(b[y])
    elif(i == len(b) and i < len(a)):
        for y in range(i, len(a)):
            lista_merge.append(a[y])
    return lista_merge

b = [ 1, 4, 9, 16 ]
a = [ 9, 7, 4, 9, 11 ]
print(merge(a, b))