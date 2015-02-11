from sys import stdin

def pearsonr(x, y):
	N = x.shape
	zx = (x-sum(x)/N)

if __name__ == "__main__":
	N = int(stdin.readline())
	MPC = np.array([np.array(stdin.readline().split(), dtype = np.int) 
						for _ in xrange(N)])
	corrs = [pearsonr(MPC[:,x], MPC[:,y])[0] for x, y in zip(xrange(3),[1, 2, 0])]
	for c in corrs:
		print round(c, 2)



