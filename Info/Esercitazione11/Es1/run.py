"""
i1 = {1,5,3,4}
for elem in sorted(i1):
    print(elem)
i1.discard(1)
i2 = {8,5}
i3 = i2.union(i1)
print(i3)
"""
f_input = open("input.txt", "r")

i_parole_univoche = set()
freq_parole = {}

riga = f_input.readline()
while(riga != ""):
    riga = riga.strip()
    valori = riga.split(" ")
    
    i_parole = set(valori)
    for elem in i_parole:
        i_parole_univoche.add(elem)
        
    chiavi = freq_parole.keys()
    for i in range(len(valori)):
        if(valori[i] in chiavi):
            freq_parole[valori[i]] += 1
        else:
            freq_parole[valori[i]] = 1
        
    riga = f_input.readline()
f_input.close()
print(i_parole_univoche)

freq_parole_ord = dict(sorted(freq_parole.items(), key=lambda item: item[1], reverse=True))
freq_parole_ord_list = list(freq_parole_ord.items())

i = 0
while(i<100 and i <len(freq_parole_ord_list)):
    print(freq_parole_ord_list[i])
    i+=1