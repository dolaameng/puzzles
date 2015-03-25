MOD = 1000000007

N = input()
xs = map(int, raw_input().split())
n_odds = len(filter(lambda x: x%2==1, xs));
n_evens = N - n_odds

def choose(N):
	if N == 0: return 1
	return 2**(N-1) % MOD

total = 2**n_evens % MOD
nchoose = choose(n_odds)
#for n in xrange(0, n_odds+1, 2):
#	nchoose += choose(n_odds, n)
total *= nchoose
total %= MOD

print total - 1