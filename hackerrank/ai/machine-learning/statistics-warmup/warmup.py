import numpy as np 
from sys import stdin
from collections import Counter
from scipy import stats


if __name__ == "__main__":
	N = int(stdin.readline())
	xs = np.array(stdin.readline().split(" "), dtype = np.int)
	mean = xs.mean()
	median = np.median(xs)
	c = Counter(xs)
	max_count = max(c.items(), key = lambda (k, v): v)[1]
	mode = min([k for k, v in c.items() if v == max_count])
	std = xs.std()
	ste = std / np.sqrt(N)
	lb, ub = mean - 1.96 * ste, mean + 1.96 * ste
	print round(mean, 1)
	print round(median, 1)
	print mode
	print round(std, 1)
	print round(lb, 1), round(ub, 1) 