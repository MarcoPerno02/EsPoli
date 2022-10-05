f_input = open("input1.txt", "r")
servizi_costo = {}

for i, value in enumerate(f_input.readlines()):
    try:
        campi = value.split(";")
        if(len(campi) != 4):
            raise Exception("Troppi campi nella riga: " + str(i))
        
        for y in range(len(campi)):
            campi[y] = campi[y].strip()
        
        servizi = list(servizi_costo.keys())
        
        try:
            campi[2] = float(campi[2])
        except:
            raise Exception("Prezzo non corretto nella riga: " + str(i))
        if(campi[1] in servizi):
            servizi_costo[campi[1]] += campi[2]
        else:
            servizi_costo[campi[1]] = campi[2]
            
    except Exception as e:
        print(e.args)

f_input.close()
print(servizi_costo)