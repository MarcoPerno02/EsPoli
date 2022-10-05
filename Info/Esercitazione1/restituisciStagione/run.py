giorno= 0
mese= 0
stagione=""

print("mese: ")
mese= int(input())
print("giorno: ")
giorno= int(input())

if(mese <= 3):
    stagione="Winter"
elif(mese >= 4 and mese <=6):
    stagione="Spring"
elif(mese >= 7 and mese <=9):
    stagione="Summer"
elif(mese >= 10 and mese <=12):
    stagione="Fall"   
if(mese%3 == 0 and giorno >= 21):
    if(stagione=="Winter"):
        stagione="Spring" 
    elif(stagione=="Spring"):
        stagione="Summer" 
    elif(stagione=="Summer"):
        stagione="Fall" 
    else:
        stagione="Winter" 
print(stagione)