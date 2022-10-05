def sparseArraySum(a, b):
    sum  = dict(a)
    
    ultimo_indice=-1
    chiavi = list(a.keys())
    for i in range(len(chiavi)):
        if int(chiavi[i]) > ultimo_indice:
            ultimo_indice = int(chiavi[i])
    
    items = b.items()
    for dict_elem in enumerate(items):
        sum[str(ultimo_indice+int(dict_elem[1][0]))] = dict_elem[1][1]
    return sum

a = {"1": 10, "3":50, "4":21}
b = {"0": 11, "2":51, "4":88}
print(sparseArraySum(a, b))