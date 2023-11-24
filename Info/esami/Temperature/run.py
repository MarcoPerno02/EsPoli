import operator

def analizza(mappa, temeperature, analisi):
    for i in range(len(mappa)):
        for j in range(len(mappa[i])):
            if mappa[i][j] != "-":
                k = 0
                while analisi[k]["stanza"] != mappa[i][j]:
                    k+=1
                analisi[k]["cont"] += 1
                temeperature[i][j] = float(temeperature[i][j])
                analisi[k]["media"] += temeperature[i][j]
                if temeperature[i][j] < analisi[k]["min"]:
                    analisi[k]["min"] = temeperature[i][j]
                elif temeperature[i][j] > analisi[k]["max"]:
                    analisi[k]["max"] = temeperature[i][j]
    # Stampa
    analisi.sort(key=operator.itemgetter('stanza'))
    for i in range(len(analisi)):
        analisi[i]["media"] /= analisi[i]["cont"]
        print(analisi[i]["stanza"], analisi[i]["min"], analisi[i]["max"], analisi[i]["media"])



try:
    mappa = []
    lista_stanze = []
    f = open("mappa.txt")
    riga = f.readline()
    while riga != "":
        campi = riga.rstrip().split(" ")
        stanze_piano = campi
        mappa.append(stanze_piano)
        riga = f.readline()
        for stanza in stanze_piano:
            if stanza not in lista_stanze and stanza != "-":
                lista_stanze.append(stanza)
    f.close()
    f = open("temperature.txt")
    temperature = []
    riga = f.readline()
    while riga != "":
        campi = riga.rstrip().split(" ")
        temp_stane_piano = campi
        temperature.append(temp_stane_piano)
        riga = f.readline()
    f.close()
    analisi = []
    for stanza in lista_stanze:
        analisi.append({"stanza": stanza, "min": 999, "max": -999, "media":0, "cont": 0})
    analizza(mappa, temperature, analisi)
except IOError:
    print("err")