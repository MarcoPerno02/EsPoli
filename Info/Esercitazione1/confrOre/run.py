start1=0
start2=0
end1=0
end2=0
s=0
e=0

print("Start1: ")
start1= int(input())
print("Start2: ")
start2= int(input())
print("End1: ")
end1= int(input())
print("End2: ")
end2= int(input())

if(start1>start2):
    s=start1
else:
    s=start2
if(end1<end2):
    e=end1
else:
    e=end2
if(s<e):
    print("Sovrappongono")
else:
    print("no Sovrappongono")