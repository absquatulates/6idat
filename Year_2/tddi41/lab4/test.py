import subprocess


def test_root():
    result = subprocess.run(['grep', 'root', '/etc/passwd'])
    assert result.returncode == 0

def test_games():
    result = subprocess.run(['grep', '^games:', '/usr/sbin/nologin', '/etc/passwd'])
    assert result.returncode == 0