import numpy as np 
from scipy import stats
from sys import stdin

T = int(stdin.readline())

for t in xrange(T):
	N = int(stdin.readline())
	gpa = np.asarray(stdin.readline().split(), dtype = np.float)
	scores = np.asarray([np.asarray(stdin.readline().split(), dtype = np.float)
				 for _ in xrange(5)])
	pearsonrs = np.nan_to_num([abs(stats.pearsonr(gpa, scores[i,:])[0]) for i in xrange(5)])
	best = np.argmax(pearsonrs)
	print best+1