import subprocess


def test_ldapsearch():
    result = subprocess.run("ldapsearch -x | grep hugo.william.com", shell=True, text=True)
    assert result.returncode == 0

def nslcd_is_active():
    result = subprocess.run("systemctl is-active nslcd.service | grep active", shell=True, text=True)

def nslcd_is_active():
    result = subprocess.run("systemctl is-enabled nslcd.service | grep enabled", shell=True, text=True)


def test_nss_passwd():
    result = subprocess.run("grep '^passwd:.*ldap' /etc/nsswitch.conf", shell=True, text=True)
    assert result.returncode == 0

def test_nss_group():
    result = subprocess.run("grep '^group:.*ldap' /etc/nsswitch.conf", shell=True, text=True)
    assert result.returncode == 0

def test_nss_shadow():
    result = subprocess.run("grep '^shadow:.*files.*ldap' /etc/nsswitch.conf", shell=True, text=True)
    assert result.returncode == 0