f_input = open("input.txt", mode="r")
f_output = open("output.txt", mode="w")

riga = f_input.readline()
i=1
while(riga != ""):
    f_output.write("/*" + str(i) + "*/" + riga)
    i+=1
    riga = f_input.readline()
f_input.close()
f_output.close()