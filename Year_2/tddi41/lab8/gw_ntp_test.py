import subprocess

#ntpq
def test_ntpq_pool():
    result = subprocess.run("ntpq -p | grep 'se.pool.ntp.org.*.POOL..*p '", shell=True, text=True)
    assert result.returncode == 0    

#--------------------------------#

#conf
def test_broadcast():
    result = subprocess.run("grep '^broadcast.*10.0.0.1' /etc/ntp.conf", shell=True, text=True)
    assert result.returncode == 0

def test_pool():
    result = subprocess.run("grep '^pool.*se.pool.ntp.org.*iburst' /etc/ntp.conf", shell=True, text=True)
    assert result.returncode == 0

#--------------------------------#

#services started
def test_ntp_is_active():
    result = subprocess.run("systemctl is-active ntp.service | grep active", shell=True, text=True)
    assert result.returncode == 0

def test_ntp_is_enabled():
    result = subprocess.run("systemctl is-enabled ntp.service | grep enabled", shell=True, text=True)
    assert result.returncode == 0

#nftables
def test_port123():
    result = subprocess.run("grep 'udp.*123' /etc/nftables.conf | grep '#'", shell=True, text=True)
    assert result.returncode == 1