import subprocess


def slapd_is_active():
    result = subprocess.run("systemctl is-active slapd.service | grep active", shell=True, text=True)
    assert result.returncode == 0

def slapd_is_enabled():
    result = subprocess.run("systemctl is-enabled slapd.service | grep enabled", shell=True, text=True)
    assert result.returncode == 0

def test_slapd():
    slapd_is_active()
    slapd_is_enabled()


def test_port389():
    result = subprocess.run("grep 'tcp.*389' /etc/nftables.conf | grep '#'", shell=True, text=True)
    assert result.returncode == 1

def test_ldapsearch():
    result = subprocess.run("ldapsearch -x | grep hugo.william.com", shell=True, text=True)
    assert result.returncode == 0



#NSSWITCH

def test_nss_passwd():
    result = subprocess.run("grep '^passwd:.*ldap' /etc/nsswitch.conf", shell=True, text=True)
    assert result.returncode == 0

def test_nss_group():
    result = subprocess.run("grep '^group:.*ldap' /etc/nsswitch.conf", shell=True, text=True)
    assert result.returncode == 0

def test_nss_shadow():
    result = subprocess.run("grep '^shadow:.*files.*ldap' /etc/nsswitch.conf", shell=True, text=True)
    assert result.returncode == 0

def test_user_existance():
    result = subprocess.run("getent passwd will | grep will", shell=True, text=True)
    assert result.returncode == 0