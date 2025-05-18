import subprocess

#ntpq
def test_ntpq():
    result = subprocess.run("ntpq -p | grep *gw", shell=True, text=True)
    assert result.returncode == 0

def t_delay(delay):
    assert 20.0 > float(delay)

def t_offset(offset):
    assert 20.0 > float(offset)

def t_jitter(jitter):
    assert 20.0 > float(jitter)

def test_margins():
    output = subprocess.run("ntpq -p | grep *gw", shell=True, text=True, stdout=subprocess.PIPE)
    output = output.stdout
    output_list = output.split()
    output_list.reverse()

    delay = output_list[2]
    offset = output_list[1][1:]
    jitter = output_list[0][:5]

    t_delay(delay)
    t_offset(offset)
    t_jitter(jitter)

#--------------------------------#

#conf
def test_server():
    result = subprocess.run("grep '^server.*10.0.0.1.*prefer' /etc/ntp.conf", shell=True, text=True)
    assert result.returncode == 0

def test_listen_broadcast():
    result1 = subprocess.run("grep '^disable.*auth' /etc/ntp.conf", shell=True, text=True)
    result2 = subprocess.run("grep '^broadcastclient' /etc/ntp.conf", shell=True, text=True)
    assert result1.returncode == 0 and result2.returncode == 0

#--------------------------------#

#services started
def test_ntp_is_active():
    result = subprocess.run("systemctl is-active ntp.service | grep '^active'", shell=True, text=True)
    assert result.returncode == 0

def test_ntp_is_enabled():
    result = subprocess.run("systemctl is-enabled ntp.service | grep enabled", shell=True, text=True)
    assert result.returncode == 0