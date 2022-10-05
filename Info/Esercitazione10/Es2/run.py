f_input = open("input.txt", mode="r")
f_output = open("output.txt", mode="w")

righe = f_input.readlines()
for i in range(len(righe)):
    riga_da_scrivere = righe[len(righe) - 1 - i].rstrip()
    f_output.write(riga_da_scrivere+"\n")
f_input.close()
f_output.close()