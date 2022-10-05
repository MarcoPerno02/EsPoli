citta="aa"

while(citta != ""):
    citta = input("Inserisci citta: ")
    if(citta != ""):
        if( citta.lower() == "belize" or citta.lower() == "cambodge" or citta.lower() == "mexique" or citta.lower() == "mozambique" or citta.lower() == "zaïre" or citta.lower() == "zimbabwe" ):
            print("le ", end="")
        elif( citta.upper()[0]=="A" or citta.upper()[0]=="E" or citta.upper()[0]=="I" or citta.upper()[0]=="O" or citta.upper()[0]=="U" ):
            print("l'", end="")
        elif( citta.lower()[-1] == "s" ):
            print("les ", end="")
        elif(citta.lower()[-1] == "e"):
            print("le ", end="")
        elif(citta.lower()[-1] == "a"):
            print("la ", end="")
        print(citta)

