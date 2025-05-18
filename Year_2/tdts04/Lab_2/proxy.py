#student ID viles222 hugho678

import socket

def init_server_socket(HOST, PORT):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))
    s.listen(10)
    return s


def init_client_socket(HOST, PORT):
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    return s


def recv_message(c_socket):
    data = c_socket.recv(4096)
    if not data: #denna kanske är redundant 
        return ""
    
    try:
        return data.decode("utf-8") # ibland försöker den avkoda ett digitaltcertificat vilket crashar programmet :(
    except:
        return ""


def get_info(message):
    info = message.split("\r\n")

    info_header = info[0].split(" ")
    info_dict = { "req" : info[0], "URL" : info[1], "http_version" : info[2]}

    for line in info[1:]:
        if line != "":
            key, value = line.split(": ", 1)
            info_dict[key] = value
    return info_dict


def send_awnser(message, ip, c_socket):
    client_socket = init_client_socket(ip, 80)
    client_socket.sendall(message.encode())

    awnser = b""

    while True:
        data = client_socket.recv(4096)
        if not data:
            break
        awnser += data


    if not b"Content-Type: image/jpeg" in awnser:
        awnser = awnser.decode()
        new_awnser = awnser.replace("/Stockholm", "/tmp")
        #new_awnser = answer.replace() # increment the header. 
        new_awnser = new_awnser.replace("Stockholm", "Linköping")
        new_awnser = new_awnser.replace("Smiley", "Trolly")
        new_awnser = new_awnser.replace("smiley", "trolly")
        new_awnser = new_awnser.replace("/tmp", "/Stockholm")
        c_socket.sendall(new_awnser.encode("utf-8"))
    else:
        c_socket.sendall(awnser)

    client_socket.close()


#----------------MAIN LOOP----------------#

HOST = "127.0.0.1"
PORT = 1337

server_socket = init_server_socket(HOST, PORT)

while True:
    c_socket, addr = server_socket.accept()
    message = recv_message(c_socket)

    if message:
        response_data = get_info(message)
        ip = socket.gethostbyname((response_data["Host"]))
        send_awnser(message, ip, c_socket)
    c_socket.close()