nomePopolazione = "worldpop.txt"
nomeArea = "worldarea.txt"
nomeOutput = "world_pop_density.txt"


def main():
    filePop = open(nomePopolazione, "r")
    fileArea = open(nomeArea, "r")
    fileOutput = open(nomeOutput, "w")
    
    listaPop = leggiRiga(filePop)
    while len(listaPop) > 0:
        listaArea = leggiRiga(fileArea)
        if(listaArea[1]>0):
            densita = listaPop[1] / listaArea[1]
        else:
            densita = 0

    filePop.close()
    fileArea.close()
    fileOutput.close()
        
def leggiRiga(fileInput):
    riga = fileInput.readline()
    campi = []
    if riga != "":
        campi = riga.split(" ", 1)
        nazione = campi[0].strip()
        valore = int(campi[1])
    return nazione, valore
    