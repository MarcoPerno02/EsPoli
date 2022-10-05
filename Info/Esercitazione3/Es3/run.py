print("Inserisci str: ")
str = input()

if(str.isalpha()):
    print("Contiene solo lettere")
else:
    print("Non contiene solo lettere")

if(str.isupper()):
    print("Contiene solo lettere maiuscole")
else:
    print("Non contiene solo lettere maiuscole")

if(str.islower()):
    print("Contiene solo lettere minsuscole")
else:
    print("Non contiene solo lettere minsuscole")

if(str.isdigit()):
    print("Contiene solo numeri")
else:
    print("Non contiene solo numeri")

if(str.isalnum()):
    print("Contiene solo lettere e numeri")
else:
    print("Non contiene solo lettere e numeri")

if(str[0].isupper()):
    print("Primo carattere è uppercase")
else:
    print("Primo carattere non è uppercase")

if(str[-1] == "."):
    print("Ultimo carattere è .")
else:
    print("Ultimo carattere non è .")