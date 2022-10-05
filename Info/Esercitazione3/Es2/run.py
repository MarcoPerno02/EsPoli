print("Inserisci voto: ")
voto_str = input()
voto_str = voto_str.upper()

val = ord(voto_str[0])#converto in ascii
voto = float(4 - (val - 65))
if(voto == -1):
    voto = 0

if(voto_str.__len__() == 2 and voto != 0):
    if(voto_str[1] == "+" and voto != 4):
        voto += 0.3
    elif(voto_str[1] == "-"):
        voto -= 0.3
print(voto)