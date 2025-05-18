#!/usr/bin/python3
import subprocess
import sys
import random
import string

def getNames():
    file = open(sys.argv[1], "r") 
    names = file.readlines()
    return names

def genUsrStr(name):
    tmp = name[:3]
    if ' ' in name:
        spaceIndex = name.rindex(' ')
        tmp = tmp + name[spaceIndex+1 : ]
    else:
        tmp = name[:5]
    
    while len(tmp) < 5:
        tmp += ' '
    tmp = tmp[:5]


    for c in tmp:
        if c == ' ':
            tmp = tmp.replace(c, random.choice(string.ascii_letters))

    return tmp.lower()

def genUsrNmbr(username):
    tmp = username + str(random.randint(100, 999))
    return tmp



#main
names = getNames()
listOfUsrNames = []
for name in names:
    flag = True
    if not name.isascii() or name == '\n':
        flag = False
        
    if flag == True:
        username = genUsrStr(name)
        username = genUsrNmbr(username)

        while username in listOfUsrNames:
            username = username[:5]
            username = genUsrNmbr(username)
        tmpList = [username]
        listOfUsrNames = listOfUsrNames + tmpList

for name in listOfUsrNames:
    print(name)





    


subprocess.run(['useradd', '-m', '--badname', username])