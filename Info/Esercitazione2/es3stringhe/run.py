str_corretto = False

while(str_corretto!=True):
    str = input("Inserisci str: ")
    if(str.__len__()>=7):
        str_corretto = True

for i in range(3):
    print(str[i])

print("...")

for i in range(-3, 0):
    print(str[i])