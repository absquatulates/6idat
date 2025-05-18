import math


def collision(t, n):
    result = (1 - ((math.factorial(t))/(math.factorial(t-n)*(t**(n))))) 
    return result

print(collision(365, 23))