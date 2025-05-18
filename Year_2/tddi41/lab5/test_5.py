import subprocess
import time


def hostname_gw():
    result = subprocess.run("hostname | grep gw", capture_output=True, shell=True, text=True)
    assert result.returncode == 0

def hostname_server():
    result = subprocess.run("hostname | grep server", capture_output=True, shell=True, text=True)
    assert result.returncode == 0

def hostname_client1():
    result = subprocess.run("hostname | grep client-1", capture_output=True, shell=True, text=True)
    assert result.returncode == 0

def hostname_client2():
    result = subprocess.run("hostname | grep client-2", capture_output=True, shell=True, text=True)
    assert result.returncode == 0


def ip():
    result = subprocess.run("cat /etc/network/interfaces | grep \"address 10.0.0.*/24\"", capture_output=True, shell=True, text=True)
    assert result.returncode == 0

def ping_10022():
    result = subprocess.run("ping -i 0.05 -c 4 10.0.2.2", shell=True, text=True)
    assert result.returncode == 0

def ip_forward():
    result = subprocess.run("cat /proc/sys/net/ipv4/ip_forward | grep 1", capture_output=True, shell=True, text=True)
    assert result.returncode == 0

def ip_masquerade():
    result = subprocess.run("nft list ruleset | grep masquerade", capture_output=True, shell=True, text=True)
    assert result.returncode == 0

def ping_google():
    result = subprocess.run("ping -i 0.05 -c 4 8.8.8.8", shell=True, text=True)
    assert result.returncode == 0

def gateway():
    result = subprocess.run("ip route list | grep 10.0.0.1", capture_output=True, shell=True, text=True)
    assert result.returncode == 0

def reach_router():
    result = subprocess.run("ping -i 0.05 -c 4 10.0.0.1", shell=True, text=True)
    assert result.returncode == 0


def port22():
    result = subprocess.run("nc -zv gw 22")

def port80():
    result = subprocess.run("nc -zv gw 80")

def firewall():
    port22()
    port80()



#TESTS

def test_gw():
    hostname_gw()
    ip()
    ping_10022()
    ping_google()
    ip_forward()
    ip_masquerade()

def test_server():
    subprocess.run("ssh root@server", shell=True, text=True)
    time.sleep(1)
    hostname_server()
    ip()
    gateway()
    reach_router()
    ping_google()
    subprocess.run("exit", shell=True, text=True)

def test_client1():
    subprocess.run("ssh root@client-1", shell=True, text=True)
    hostname_client1()
    ip()
    gateway()
    reach_router()
    ping_google()
    subprocess.run("exit", shell=True, text=True)

def test_client2():
    subprocess.run("ssh root@client-2", shell=True, text=True)
    hostname_client2()
    ip()
    gateway()
    reach_router()
    ping_google()
    subprocess.run("exit", shell=True, text=True)