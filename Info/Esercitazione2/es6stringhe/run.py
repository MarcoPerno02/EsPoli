num_telefono_corretto = False

while(num_telefono_corretto != True):
    print("Inserisci num_telefono: ")
    num_telefono = input()
    if(num_telefono.isdecimal() and num_telefono.__len__()==10):
        num_telefono_corretto = True

print("(", end="")
for i in range(0,3):
    print(num_telefono[i], end="")

print(") ", end="")

for i in range(3,6):
    print(num_telefono[i], end="")

print("-", end="")

for i in range(6,10):
    print(num_telefono[i], end="")
