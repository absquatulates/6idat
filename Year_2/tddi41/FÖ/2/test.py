import subprocess

result = subprocess.run(["ls -l | wc -l "], shell=True, capture_output=True, text=True)
print(result.stdout)

if result.stdout == 4:
    print("Yes")
    print("YEs")
else:
    print("no")


def test_nisse():
    result = subprocess.run(["ls -l | wc -l "], shell=True, capture_output=True, text=True)
    assert(int(result.stdout) == 4)
