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
        if c == ' ' or c not in string.ascii_letters:
            tmp = tmp.replace(c, random.choice(string.ascii_letters))

    return tmp.lower()

def genUsrNmbr(username):
    tmp = username + str(random.randint(100, 999))
    return tmp


def genPassword():
    password = ''.join(random.choice(string.ascii_letters) for i in range(7))
    return password




#main
names = getNames()
listOfUsrNames = []
for name in names:
    username = genUsrStr(name)
    username = genUsrNmbr(username)

    while username in listOfUsrNames:
        username = username[:5]
        username = genUsrNmbr(username)
        
    tmpList = [username]
    listOfUsrNames = listOfUsrNames + tmpList


file = open("usrs.txt", "a")

for username in listOfUsrNames:   
    subprocess.run(f"useradd -m -s /bin/bash {username}", shell=True, text=True)
    uid = subprocess.run(f"id -u {username}", shell=True, text=True, capture_output=True)
    result = subprocess.run(f"ldapadduser {username} users {uid.stdout.strip()}", shell=True, text=True)
     
    if result.returncode == 0:
        password = genPassword()
        
        passfile = open("password.txt", "w")
        passfile.write(f"{username}:{password}")
        passfile.close()

        subprocess.run("chpasswd < password.txt", shell=True, text=True)

        passfile = open("password.txt", "w")
        passfile.write(f"{password}\n{password}\n")
        passfile.close()

        subprocess.run(f"ldapsetpasswd {username} < password.txt 2>/dev/null", shell=True, text=True)
            #2>/dev/null för att undgå varningar, samma funktion som utan
        
        file.write(f"{username}:{password}\n")	
    else:
        username = username[:5]
        username = genUsrNmbr(username)
        listOfUsrNames.append(username)

subprocess.run("rm -f password.txt", shell=True, text=True)     
file.close()
subprocess.run("chmod 400 usrs.txt", shell=True, text=True)
