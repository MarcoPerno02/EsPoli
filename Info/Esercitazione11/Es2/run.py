str1 = set(input("Inserisci stringa: "))
str2 = set(input("Inserisci stringa: "))

intersezione = str1.intersection(str2)
print(intersezione)

caratteri_str1_non_in_str2 = str1 - str2
print(caratteri_str1_non_in_str2)

caratterri_univoci_str1_str2 = set()

intersezione = list(intersezione)

for elem in str1:
    dentro_lista = elem in intersezione
    if dentro_lista == False:
        caratterri_univoci_str1_str2.add(elem)
for elem in str2:
    dentro_lista = elem in intersezione
    if dentro_lista == False:
        caratterri_univoci_str1_str2.add(elem)
print(caratterri_univoci_str1_str2)
