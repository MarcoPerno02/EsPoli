str = input("Inserisci stringa: ")

i=0
strLettMaiusc=""

while(i<str.__len__()):
    if(ord(str[i]) >= 65 and ord(str[i]) <= 90):
        strLettMaiusc+=str[i]
    i+=1

print("StrLettMaiusc: "+strLettMaiusc)
