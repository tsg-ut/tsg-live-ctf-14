#!/usr/bin/env sage 
from flag import flag

def sage_encode(obj):
    from sage.misc.persist import SagePickler
    from base64 import b64encode
    return b64encode(SagePickler.dumps(obj)).decode('ascii')

def sage_decode(enc_data):
    from base64 import b64decode
    import pickle
    return pickle.loads(b64decode(enc_data))

class Isogeny_decomp:
    def __init__(self,P,order_P = -1):
        if isinstance(P,list):
            for i in range(len(P)-1):
                assert P[i].codomain() == P[i+1].domain()
            self.isogenies = P[:]
            return
        if order_P == -1:
            order_P = P.order()
        self.isogenies = []
        for p,c in factor(order_P):
            for i in range(c):
                phi = P.curve().isogeny((order_P//p)*P)
                self.isogenies.append(phi)
                P = phi(P)
                order_P //= p
                if P == P.curve()((0,1,0)):
                    break
            if P == P.curve()((0,1,0)):
                break
    def __call__(self,P):
        for phi in self.isogenies:
            P = phi(P)
        return P
    def __mul__(self,other):
        assert other.isogenies[-1].codomain().j_invariant() == self.isogenies[0].domain().j_invariant()
        isom = other.isogenies[-1].codomain().isomorphism_to(self.isogenies[0].domain())
        return Isogeny_decomp(other.isogenies + [isom] + self.isogenies)
    def dual(self):
        ret = []
        for phi in self.isogenies:
            ret.append(phi.dual())
        ret.reverse()
        return Isogeny_decomp(ret)
    def domain(self):
        return self.isogenies[0].domain()
    def codomain(self):
        return self.isogenies[-1].codomain()

#SIKEp434
e2 = 0xD8
e3 = 0x89
p = 2**e2*3**e3-1
R.<x> = GF(p)[]
k.<i> = GF(p**2,modulus=x**2+1)

xQ30 = 0x00012E84_D7652558_E694BF84_C1FBDAAF_99B83B42_66C32EC6_5B10457B_CAF94C63_EB063681_E8B1E739_8C0B241C_19B9665F_DB9E1406_DA3D3846
xQ31 = 0x00000000
yQ30 = 0x00000000
yQ31 = 0x0000EBAA_A6C73127_1673BEEC_E467FD5E_D9CC29AB_564BDED7_BDEAA86D_D1E0FDDF_399EDCC9_B49C829E_F53C7D7A_35C3A074_5D73C424_FB4A5FD2
xP30 = 0x00008664_865EA7D8_16F03B31_E223C26D_406A2C6C_D0C3D667_466056AA_E85895EC_37368BFC_009DFAFC_B3D97E63_9F65E9E4_5F46573B_0637B7A9
xP31 = 0x00000000
yP30 = 0x00006AE5_15593E73_97609197_8DFBD70B_DA0DD6BC_AEEBFDD4_FB1E748D_DD9ED3FD_CF679726_C67A3B2C_C12B3980_5B32B612_E058A428_0764443B
yP31 = 0x00000000
xR30 = 0x0001CD28_597256D4_FFE7E002_E8787075_2A8F8A64_A1CC78B5_A2122074_783F51B4_FDE90E89_C48ED91A_8F4A0CCB_ACBFA7F5_1A89CE51_8A52B76C
xR31 = 0x00014707_3290D78D_D0CC8420_B1188187_D1A49DBF_A24F26AA_D46B2D9B_B547DBB6_F63A760E_CB0C2B20_BE52FB77_BD2776C3_D14BCBC4_04736AE4


xP3 = xP30+xP31*i
xQ3 = xQ30+xQ31*i
xR3 = xR30+xR31*i
yP3 = yP30+yP31*i
yQ3 = yQ30+yQ31*i

ec_start = EllipticCurve(k,[0,6,0,1,0])
P3 = ec_start((xP3,yP3))
Q3 = ec_start((xQ3,yQ3))

import secrets
sk3 = int(secrets.randbelow(int(3)**e3))
sp3 = P3+sk3*Q3

isogeny = Isogeny_decomp(sp3,3**e3)
E1 = isogeny.codomain()

P = sage_decode(input("Enter a point: "))
print(sage_encode(isogeny(P)))

user_sk = int(input("Enter your answer: "))
if user_sk == sk3:
    print("Correct")
    print(flag)
else:
    print("Incorrect")

