files = []
parola_da_cercare = ""

input_str = input("Inserire nomi file separate da virgole e parola da cercare :")

inputs = input_str.split(",")
for i in range(len(inputs)):
    inputs[i] = inputs[i].strip()
    if(i == len(inputs) - 1):
        parola_da_cercare = inputs[i].lower()
    else:
        files.append(inputs[i])

for file in files:
    error = False
    try:
        f_input = open(file, "r")
    except Exception as e:
        print(e.args)
        error = True
    if(error == False):
        righe = f_input.readlines()
        for riga in righe:
            riga_aus = riga.lower()
            if parola_da_cercare in riga_aus:
                print(riga.rstrip())
        f_input.close()