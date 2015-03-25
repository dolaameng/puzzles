MOD = 1000000007



T = input()
for _ in xrange(T):
	lrs = map(int, raw_input().split())
	lrs = zip(lrs[::2], lrs[1::2])
	print count(lrs)