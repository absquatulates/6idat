import subprocess

def hostname():
    result = subprocess.run("hostname | grep client-1", capture_output=True, shell=True, text=True)
    assert result.returncode == 0

def ip():
    result = subprocess.run("cat /etc/network/interfaces | grep \"address 10.0.0.3/24\"", capture_output=True, shell=True, text=True)
    assert result.returncode == 0

def gateway():
    result = subprocess.run("ip route list | grep 10.0.0.1", capture_output=True, shell=True, text=True)
    assert result.returncode == 0

def reach_router():
    result = subprocess.run("ping -i 0.05 -c 4 10.0.0.1", shell=True, text=True)
    assert result.returncode == 0

def ping_google():
    result = subprocess.run("ping -i 0.05 -c 4 8.8.8.8", shell=True, text=True)
    assert result.returncode == 0

def ping_server():
    result = subprocess.run("ping -i 0.05 -c 4 server", shell=True, text=True)
    assert result.returncode == 0

def ping_client2():
    result = subprocess.run("ping -i 0.05 -c 4 client-2", shell=True, text=True)
    assert result.returncode == 0

def is_active():
    result = subprocess.run("systemctl is-active nftables.service | grep active", shell=True, text=True)
    assert result.returncode == 0

def active_on_boot():
    result = subprocess.run("systemctl is-enabled nftables.service | grep enabled", shell=True, text=True)
    assert result.returncode == 0

def port22():
    result = subprocess.run("nc -zv client-1 22", shell=True, text=True)
    assert result.returncode == 0
    
def port80():
    result = subprocess.run("nc -zv client-1 80", shell=True, text=True)
    assert result.returncode == 1

def firewall():
    is_active()
    active_on_boot()
    port22()
    port80()


def test_client1():
    hostname()
    ip()
    gateway()

    reach_router()
    ping_google()
    ping_server()
    ping_client2()

    firewall()