def compraCalciatori(fanta_ruolo_disp:int, n_calciatori_ruolo:int, ruolo:str):
    for i in range(n_calciatori_ruolo):
        costo_max = fanta_ruolo_disp - (n_calciatori_ruolo - i - 1)
        trovato = False
        while trovato != True:
            j = 0
            while calciatori[ruolo].__len__() != j and int(calciatori[ruolo][j][3]) != costo_max :
                j+=1
            if calciatori[ruolo].__len__() == j:
                costo_max-=1
            else:
                fanta_ruolo_disp -= int(calciatori[ruolo][j][3])
                squadra[ruolo].append(calciatori[ruolo][j])
                del calciatori[ruolo][j]
                trovato = True
                
def stampaCalciatori():
    ruoli = ["portiere", "difensore", "centrocampista", "attaccante"]
    for ruolo in ruoli:
        print(ruolo, ": ")
        for i in range(len(squadra[ruolo])):
            print(squadra[ruolo][i][0], " ", squadra[ruolo][i][3], " ")
        print("")

fanta_portieri = 20
fanta_difensori = 40
fanta_centrocampisti = 80
fanta_attaccanti = 120
calciatori = {"portiere": [], "difensore": [], "centrocampista": [], "attaccante": []}
squadra = {"portiere": [], "difensore": [], "centrocampista": [], "attaccante": []}

try:
    file_calc = open("fantacalcio.txt", "r")
    
    #inizio letura file
    riga = file_calc.readline()
    while riga != "":
        riga = riga.rstrip().split(", ")
        calciatori[riga[2]].append(riga)
        riga = file_calc.readline()
    print("Lettura completata")
    
    #portieri
    compraCalciatori(fanta_portieri, 3, "portiere")
    #difensori
    compraCalciatori(fanta_difensori, 8, "difensore")
    #centrocampisti
    compraCalciatori(fanta_centrocampisti, 8, "centrocampista")
    #attacanti
    compraCalciatori(fanta_attaccanti, 6, "attaccante")
    
    stampaCalciatori()
except Exception as e:
    print("Si è verificata un eccezione: " + str(e))