def scambiaPrimoUltimo(_lista):
    lista = list(_lista)
    aus = lista[-1]
    lista[-1] = lista[0]
    lista[0] = aus
    return lista

def scorriVersoDestra(_lista):
    lista = list(_lista)
    new_lista = []
    new_lista.append(lista[-1])
    for i in range(len(lista) - 1):
        new_lista.append(lista[i])
    return new_lista

def sostituireCon0IdxPari(_lista):
    lista = list(_lista)
    for i in range(len(lista)):
        if(i%2==0):
            lista[i] = 0
    return lista

def sostPiuGrandeAdiac(_lista):
    lista = list(_lista)
    new_lista = []
    for i in range(1, len(lista) - 1):
        if(lista[i-1] > lista[i+1]):
            new_lista.append(lista[i-1])
        else:
            new_lista.append(lista[i+1])
    return new_lista

def eliminaElCentrali(_lista):
    lista = list(_lista)
    if(len(lista)%2 == 0):
        idx = int((len(lista)/2))-1
        del lista[idx]
        del lista[idx]
    else:
        idx = int((len(lista)/2))
        del lista[idx]
    return lista

def spostaPariDisp(_lista):
    lista = list(_lista)
    lista_pari = []
    lista_disp = []
    for i in range(len(lista)):
        if(lista[i]%2==0):
            lista_pari.append(lista[i])
        else:
            lista_disp.append(lista[i])
    new_list = lista_pari + lista_disp
    return new_list

def trovaSecondoMax(_lista):
    lista = (_lista)
    if(lista[0] > lista[1]):
        sec_max = lista[1]
        max = lista[0]
    else:
        sec_max = lista[0]
        max = lista[1]
    for i in range(2, len(lista)):
        if(lista[i]>max):
            sec_max = max
            max = lista[i]
        elif(lista[i]>sec_max):
            sec_max = lista[i]
    return sec_max

def controllaOrdCrescente(_lista):
    lista = list(_lista)
    i = 0
    while(i < len(lista) - 1 and lista[i]<lista[i+1]):
        i+=1
    if(i == len(lista) - 1):
        return True
    else:
        return False

def controllaAdiacDupl(_lista):
    lista = list(_lista)
    i = 0
    while(i < len(lista) - 1 and lista[i]!=lista[i+1]):
        i+=1
    if(i == len(lista) - 1):
        return False
    else:
        return True

def controllaDupl(_lista):
    lista = list(_lista)
    i = 0
    trovato = False
    while(i < len(lista) - 1 and trovato == False):
        y = i+1
        while(y!=len(lista) and trovato == False):
            if(lista[i] != lista[y]):
                y+=1
            else:
                trovato = True
        i+=1
            
    if(trovato == True):
        return True
    else:
        return False

lista = [10,20,30,40,50,60]
print(scambiaPrimoUltimo(lista))
print(scorriVersoDestra(lista))
print(sostituireCon0IdxPari(lista))
print(sostPiuGrandeAdiac(lista))
print(eliminaElCentrali(lista))
print(spostaPariDisp(lista))
print(trovaSecondoMax(lista))
print(controllaOrdCrescente(lista))
print(controllaAdiacDupl(lista))
print(controllaDupl(lista))