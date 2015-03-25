MOD = 1000000007

N = input()
xs = map(int, raw_input().split())
n_odds = len(filter(lambda x: x%2==1, xs));
n_evens = N - n_odds

def choose(N, n):
	r = 1
	for i in xrange(N-n+1, N+1):
		r *= i
	for i in xrange(1, n+1):
		r /= i
	return r

total = 2**n_evens % MOD
nchoose = 0
for n in xrange(0, n_odds+1, 2):
	nchoose += choose(n_odds, n)
total *= nchoose
total %= MOD

print total - 1