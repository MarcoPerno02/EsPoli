lista = []

input_num=" "
while(input_num!=""):
    input_num = input("Inserisci numero: ")
    if(input_num.isdigit() == True):
        lista.append(int(input_num))

sum_alternata = 0
for i in range(len(lista)):
    if(i%2 == 0):
        sum_alternata+=lista[i]
    else:
        sum_alternata-=lista[i]

print("sum_alternata: ", sum_alternata )