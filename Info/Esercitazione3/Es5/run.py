print("Inserisci anno: ")
anno = int(input())

if (anno % 4 == 0 and anno % 100 !=0) or anno % 400 == 0:
    print("Bisestile")
else:
    print("No bisestile")

