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


file = open("usrs.txt", "w")

for username in listOfUsrNames:   
    subprocess.run(f"useradd {username}", shell=True, text=True) 
    result = subprocess.run(f"ldapadduser {username} users", shell=True, text=True)
     
    if result.returncode == 0:
        password = genPassword()

        passfile = open("password.txt", "w")
        passfile.write(password)
        passfile.close()

        passfile = open("password.txt", "r")
        new_password = passfile.read()
        input_data = f"{new_password.strip()}\n{new_password.strip()}\n"

        subprocess.run(f"ldapsetpasswd {username}", input=input_data, shell=True, text=True)
        passfile.close()
        file.write(f"{username}:{password}\n")	
    else:
        username = username[:5]
        username = genUsrNmbr(username)
        listOfUsrNames.append(username)

subprocess.run("rm -f password.txt", shell=True, text=True)     
file.close()
subprocess.run("chmod 400 usrs.txt", shell=True, text=True)