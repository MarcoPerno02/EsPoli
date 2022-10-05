def sameSet(a, b):
    trovato = True
    i=0
    while( i!=len(a) and trovato == True ):
        y=0
        while( y != len(b) and a[i] != b[y] ):
            y+=1
        
        if(y == len(b)):
            trovato = False
        i+=1

    if(trovato == True):
        return True
    else:
        return False

lista1 = [ 1, 4, 9, 16, 9, 7, 4, 9, 1 ]
lista2 = [ 11, 11, 7, 9, 16, 4, 1 ]

if(sameSet(lista1, lista2)):
    print("Uguali")
else:
    print("Diverse")

