from Crypto.Util.number import getStrongPrime, bytes_to_long
from flag import flag

p = getStrongPrime(512)
q = getStrongPrime(512)
n = p * q
e = 65537

m = bytes_to_long(flag.encode())
assert m < n

c = (pow(m, e, n) >> 384) << 384
cp = pow(m+p, e, n)
cq = pow(m+q, e, n)

print(f"{n=}")
print(f"{e=}")
print(f"{c=}")
print(f"{cp=}")
print(f"{cq=}")