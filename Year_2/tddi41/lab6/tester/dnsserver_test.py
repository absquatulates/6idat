#TESTS FOR DNS-SERVER

import subprocess

#TESTS THAT NAMED/BIND9 IS SETUP CORRECTLY
def test_bind():
    result = subprocess.run("named-checkconf", shell=True, text=True)
    assert result.returncode == 0

#TESTS THAT NAMED/BIND9 IS ACTIVE AND RUNNING PROPERLY
def test_bind_active():
    result = subprocess.run("systemctl is-active bind9.service | grep '^active'", shell=True, text=True)
    assert result.returncode == 0

def test_named_active():
    result = subprocess.run("systemctl is-active named.service | grep '^active'", shell=True, text=True)
    assert result.returncode == 0

def test_named_enabled():
    result = subprocess.run("systemctl is-enabled named.service | grep enabled", shell=True, text=True)
    assert result.returncode == 0

#TESTS THAT NFTABLES/FIREWALL IS ACTIVE AND RUNNING
def test_nftables_active():
    result = subprocess.run("systemctl is-active nftables.service | grep '^active'", shell=True, text=True)
    assert result.returncode == 0

def test_nfatables_enabled():
    result = subprocess.run("systemctl is-enabled nftables.service | grep enabled", shell=True, text=True)
    assert result.returncode == 0

#TESTS DNS-ZONES
def check_zone():
    result = subprocess.run("named-checkzone hugo.william.com /etc/bind/zones/hugo.william.com | grep OK", shell=True, text=True)
    assert result.returncode == 0

def check_zone_reverse():
    result = subprocess.run("named-checkzone 0.0.10.in-addr.arpa /etc/bind/zones/rev.10.0.0 | grep OK", shell=True, text=True)
    assert result.returncode == 0

def test_zonefiles():
    check_zone()
    check_zone_reverse()

#CHECKS IF PORT 53 IS OPEN FOR DNS TRAFFIC
def test_port53():
    result = subprocess.run("nc -zv server 53", shell=True, text=True)
    assert result.returncode == 0

    #Kollar om nftables är konfigurerad korrekt för DNS-trafik, tcp och udp
def tcp53():
    result = subprocess.run("grep 'tcp.*dport.*53.*accept' /etc/nftables.conf | grep '#'", shell=True, text=True)
    assert result.returncode == 1

def udp53():
    result = subprocess.run("grep 'udp.*dport.*53.*accept' /etc/nftables.conf | grep '#'", shell=True, text=True)
    assert result.returncode == 1

def test_nftables():
    tcp53()
    udp53()


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