import random

def ssbt(A, V, X, i, P):
    n = len(A)
    if V == P:
        return X
    elif i == n or P>V:
        return None
    else:
        for b in [1,0]:
            X[i] = b
            R = ssbt(A, V, X, i, P +(b*A[i])
             
    return None 

def ss(A, V):
    n = len(A)
    X = n * [0]
    return ssbt(A, V, X, 0, 0)


n = 10
maxval = 100
A = [random.randrange(0, maxval) for i in range(n)]
X = [random.randrange(0, 2) for i in range(n)]
V = sum((X[i] * A[i] for i in range(n)))

print("A=", A)
print("X=", X)
print("V=", V) 