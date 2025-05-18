# TESTS FOR CLIENTS AND ROUTER

import subprocess

#CHECKS IF THE MACHINE USES THE DNS-SERVER AS NAMESERVER
def test_nameserver():
    result = subprocess.run("cat /etc/resolv.conf | grep 10.0.0.2", shell=True, text=True)
    assert result.returncode == 0


#TESTS FORWARD DNS
def server_forward():
    result = subprocess.run("dig +noall +answer server.hugo.william.com A | grep 10.0.0.2", shell=True, text=True)
    assert result.returncode == 0

def gw_forward():
    result = subprocess.run("dig +noall +answer gw.hugo.william.com A | grep 10.0.0.1", shell=True, text=True)
    assert result.returncode == 0

def client1_forward():
    result = subprocess.run("dig +noall +answer client-1.hugo.william.com A | grep 10.0.0.3", shell=True, text=True)
    assert result.returncode == 0

def client2_forward():
    result = subprocess.run("dig +noall +answer client-2.hugo.william.com A | grep 10.0.0.4", shell=True, text=True)
    assert result.returncode == 0

def test_forward():
    server_forward()
    gw_forward()
    client1_forward()
    client2_forward()


#TESTS REVERSE DNS
def server_reverse():
    result = subprocess.run("dig +noall +answer 2.0.0.10.in-addr.arpa PTR | grep server.hugo.william.com", shell=True, text=True)
    assert result.returncode == 0

def gw_reverse():
    result = subprocess.run("dig +noall +answer 1.0.0.10.in-addr.arpa PTR | grep gw.hugo.william.com", shell=True, text=True)
    assert result.returncode == 0

def client1_reverse():
    result = subprocess.run("dig +noall +answer 3.0.0.10.in-addr.arpa PTR | grep client-1.hugo.william.com", shell=True, text=True)
    assert result.returncode == 0
    
def client2_reverse():
    result = subprocess.run("dig +noall +answer 4.0.0.10.in-addr.arpa PTR | grep client-2.hugo.william.com", shell=True, text=True)
    assert result.returncode == 0

def test_reverse():
    server_reverse()
    gw_reverse()
    client1_reverse()
    client2_reverse()