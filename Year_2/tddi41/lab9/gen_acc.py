#!/usr/bin/python3
import subprocess
import sys
import random
import string

#Läser in de namn vi vill skapa inlogg till från en textfil
def getNames():
    file = open(sys.argv[1], "r") 
    names = file.readlines()
    return names

#Genererar ett liu-id-liknande användarnamn med fem bokstäver
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

#Genererar tre siffror som läggs till efter de fem bokstäverna i användarnamnet
def genUsrNmbr(username):
    tmp = username + str(random.randint(100, 999))
    return tmp

#Genererar ett lösenord med sju slumpmässiga ascii-bokstäver 
def genPassword():
    password = ''.join(random.choice(string.ascii_letters) for i in range(7))
    return password




#--------------------------------MAIN--------------------------------#

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


#Fil för att kunna logga in efter användarna skapats
file = open("usrs.txt", "a") 

#Counter för att bestämma den användarens hemkatalog
home_counter = 0

for username in listOfUsrNames: 

    #Varannan användare läggs i home1 och varannan läggs i home2
    home_counter = home_counter + 1
    if home_counter % 2 == 0:
        home = "home2"
    else:
        home = "home1"  
    
    #Lägger till en användare lokalt och i LDAP
    subprocess.run(f"useradd -d /{home}/{username} -m -s /bin/bash {username}", shell=True, text=True)
    uid = subprocess.run(f"id -u {username}", shell=True, text=True, capture_output=True)
    result = subprocess.run(f"ldapadduser {username} users {uid.stdout.strip()}", shell=True, text=True)

    #Om användaren inte redan finns i LDAP-katalogen 
    if result.returncode == 0:
        password = genPassword()

        #Formaterar lösenordsfilen för "chpasswd"
        passfile = open("password.txt", "w")
        passfile.write(f"{username}:{password}")
        passfile.close()

        subprocess.run("chpasswd < password.txt", shell=True, text=True)

        #Formaterar lösenordsfilen för "ldapsetpasswd"
        passfile = open("password.txt", "w")
        passfile.write(f"{password}\n{password}\n")
        passfile.close()

        subprocess.run(f"ldapsetpasswd {username} < password.txt 2>/dev/null", shell=True, text=True)
            #2>/dev/null för att undgå varningar, samma funktion som utan
        
        #Lägger till automount-record i LDAP för användaren
        automount_ldif = open("automount.ldif", "a")
        automount_ldif.write(f"dn: cn={username},ou=auto.home,ou=automount,ou=admin,dc=hugo,dc=william,dc=com\n")
        automount_ldif.write(f"cn: {username}\n")
        automount_ldif.write("objectClass: top\n")
        automount_ldif.write("objectClass: automount\n")
        automount_ldif.write(f"automountInformation: -fstype=nfs4,rw 10.0.0.2:/{home}/{username}")
        automount_ldif.close()

        subprocess.run("ldapadd -D 'cn=admin,dc=hugo,dc=william,dc=com' -f automount.ldif -y adminpass.txt", shell=True, text=True)

        #Tar bort filen för att kunna skapa en ny för nästa användare i listan
        subprocess.run("rm -f automount.ldif", shell=True, text=True)

        #Sparar användarnamn och lösenord för att kunna testa att logga in
        #Sparar också vilken hemkatalog användaren får för att se om det blev rätt
        file.write(f"{username}:{password}    /{home}/{username}\n")
    else:
        username = username[:5]
        username = genUsrNmbr(username)
        listOfUsrNames.append(username)

#Städar upp efter körning
subprocess.run("rm -f password.txt", shell=True, text=True)     
file.close()
subprocess.run("chmod 400 usrs.txt", shell=True, text=True)
