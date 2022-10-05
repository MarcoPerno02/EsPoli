try:
    info_artisti = []
    canzoni = []
    file_artisti = open("artisti.txt", "r").readlines()
    
    #mi salvo il contenuto del file artisti in una lista
    for riga in file_artisti:
        campi = riga.rstrip().split(";")
        info_artisti.append({"codice": campi[0], "nome_file": campi[1]})
    
    for info_artista in info_artisti:
        file_canzone_artista = open(info_artista["nome_file"], "r")
        riga = file_canzone_artista.readline()
        while riga != "":
            campi = riga.rstrip().split(";")
            canzoni.append({"anno": campi[0], "nome_canzone": campi[1], "codice_artista": info_artista["codice"]})
            riga = file_canzone_artista.readline()
        file_canzone_artista.close()
    
    canzoni = sorted(canzoni, key=lambda d: d['anno'])
    
    for i in range(len(canzoni)):
        if(i==0):
            print(canzoni[i]["anno"])
            print(canzoni[i]["nome_canzone"], canzoni[i]["codice_artista"])
        else:
            if(canzoni[i]["anno"] != canzoni[i-1]["anno"]):
                print(canzoni[i]["anno"])
            print(canzoni[i]["nome_canzone"], canzoni[i]["codice_artista"])
                
except Exception as e:
    print("Si è verificata un eccezioen: ", e)
    