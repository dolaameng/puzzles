from numpy import linalg
import numpy as np 
import sys

if __name__ == "__main__":
	F, N = map(int, sys.stdin.readline().strip().split(" "))
	train_data = [map(float, sys.stdin.readline().strip().split(" ")) for _ in xrange(N)]
	T = int(sys.stdin.readline().strip())
	test_data = [map(float, sys.stdin.readline().strip().split(" ")) for _ in xrange(T)]
	train_data = np.asarray(train_data)
	test_X = np.c_[np.asarray(test_data), np.ones(T)]
	train_X = np.c_[train_data[:, :-1], np.ones(N)]
	train_y = train_data[:, -1]
	w = np.dot(linalg.pinv(train_X), train_y)
	test_yhat = np.dot(test_X, w)
	print "\n".join([str(y) for y in test_yhat])
	#print train_X
	#print train_y
	#print test_X