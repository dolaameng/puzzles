# Enter your code here. Read input from STDIN. Print output to STDOUT

MOD = 1000000007

def count(N, M):
    total = 1
    for t in xrange(M+1, N+M+1):
        total = total * t
    for t in xrange(1, N+1):
        total = total / t
    return total % MOD

T = input()
for _ in xrange(T):
    N, M = map(int, raw_input().split())
    print count(N, M)