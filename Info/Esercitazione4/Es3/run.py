lunghLato = int(input("Inserisci lungh lato: "))

for i in range(lunghLato):
    print("*" * lunghLato)

for i in range(lunghLato):
    print(" " * (lunghLato-i-1), end="")
    print("*"* (i+1), end="")
    print("*"*i)
for i in range(lunghLato-1):
    print(" " * (i+1), end="")
    print("*"* (lunghLato-i-1),end="")
    print("*"* (lunghLato-i-2))

