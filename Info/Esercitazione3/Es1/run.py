print("Inserisci num1: ")
num1 = int(input())
print("Inserisci num2: ")
num2 = int(input())

if(num2 > num1 or num2 < num1):
    print("Inserisci num3: ")
    num3 = int(input())
    if(num3 > num2 and num2 > num1):
        print("Increasing")
    elif(num3 < num2 and num2 < num1):
        print("Decreasing")
    else:
        print("Neither")
else:
    print("Neither")