MOD = 1000000000+7;

def ipow(base, exp):
    result = 1
    while exp:
        if exp & 1: result = (result * base) % MOD
        exp >>= 1
        base = (base * base) % MOD
        #print base, exp
    return result

def apalin(N, M):
    if (N == 1): return M % MOD
    elif (N == 2): return M*(M-1) % MOD
    else: return M*(M-1)*ipow(M-2, N-2) % MOD

T = input()
for t in xrange(T):
    N, M = map(int, raw_input().split())
    print apalin(N, M);