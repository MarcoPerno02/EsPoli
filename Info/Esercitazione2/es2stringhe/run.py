num_corretto = False

while(num_corretto!=True):
    num = int(input("Inserisci num: "))
    if(num>=10000 and num<=99999):
        num_corretto = True

num_str=str(num)
for i in range(5):
    print(num_str[i])
