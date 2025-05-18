import socket

#Your proxy will need one socket for talking to the client, and another socket for talking to the server. Make sure to keep track of which one is which.

port = 1337
host = "127.0.0.1"

#The server part receives the HTTP request form the browser and delivers that HTTP request to the client part 


with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((host,port))
    s.listen(10) 

    while True:    
            client_sock, address = s.accept()   #ska forkas? 
            print(f"Proxy server listening on port {port}...\n")
            print(f"Browser connecting to address {address} \n")
            
            mess = client_sock.recv(4096)
            
            with client_sock:
                #if Header_one.
                print(mess)
                
                decoded_msg = mess.decode("utf-8") # denna fungerar i bland, ibland ger felmedelanden
                        
                msg_list = decoded_msg.split("\r\n")
                GET_header = msg_list[0].split(" ")# denna är, enligt guiden, speciell 😊.

                #split GET_header into three parts
                if GET_header != {}:  # on get_heden är tom tror jag att den ska vara samma som förra, 
                    Header_one = { "req" :  GET_header[0],
                                 "URL" :  GET_header[1], #often, no URL index
                                "http_version" : GET_header[2]}
                
                print(Header_one, "\n")

                Header_lines = {}

                for i in range(1, (len(msg_list)-2) ): # dumma lösning,
                    key_pair = msg_list[i].split(": ")
                    Header_lines[key_pair[0]] = key_pair[1]  #känns rimligt att det skulle finnas ett smidigare/bättre sätt att göra detta,
                                           #men men... python string. parse() host host hugo host host
    
                host = Header_lines["Host"]
                # lägg till kod som hanterar om gethostbyname genererat felmedelanden, den är bra på sånt
                try:
                    ip_address = socket.gethostbyname(Header_lines["Host"])
                except:
                    print("Hostname error")
                    break
                
                if ip_address == "34.107.221.82":
                    break
    
                print(f"Resolved {host} to {ip_address}")  # loopen åter resolvar adressen för varje ny http get på en sida 
                client_2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)               
                client_2.connect((ip_address,80))
                client_2.send(mess)
                # for loop för att hämnta om det är flera http filer att hämta flera filer, som en text fil och en bildfil
                message_buffer = b""
                while True:
                    mess_2 = client_2.recv(4096)
                    message_buffer += mess_2
                    if not mess_2: #when there is no more data to recive, close it damit !!, this damm loop is unececary long
                        print("closing webpage sock") # denna kanske stängs för tidigt  
                        client_2.close()
                        break
                client_sock.send(message_buffer)
                
                
                
print("\n" ,"duktig")
s.close()
print("\n" ,"duktig")


    
