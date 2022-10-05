lista = []
lista_pos_max_locali = []

input_num=" "
while(input_num!=""):
    input_num = input("Inserisci numero: ")
    if(input_num.isdigit() == True):
        lista.append(int(input_num))

for i in range(1, len(lista)-1):
    if(lista[i] > lista[i-1] and lista[i] > lista[i+1]):
        lista_pos_max_locali.append(i)

if(len(lista_pos_max_locali) != 0):
    print("Lista pos max locali: ", lista_pos_max_locali)
else:
    print("no max locali")