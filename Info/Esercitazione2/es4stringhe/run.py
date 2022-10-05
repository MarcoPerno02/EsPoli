print("Inserisci costo totale: ")
COSTO_TOTALE = float(input())

print("Inserisci num libri: ")
NUM_LIBRI = int(input())

tasse = 7.5*COSTO_TOTALE/100
print("tasse: ", tasse)

costi_spedizione = 2*NUM_LIBRI
print("costi spedizione: ", costi_spedizione)

prezzo_tot = COSTO_TOTALE + tasse + costi_spedizione
print("prezzo_tot: ", prezzo_tot)