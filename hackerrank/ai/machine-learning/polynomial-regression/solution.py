import numpy as np 
from sys import stdin
from numpy import linalg
from sklearn.preprocessing import PolynomialFeatures

def polynomial(X, order):
	poly = PolynomialFeatures(order)
	return poly.fit_transform(X)

if __name__ == "__main__":
	P = 3
	(F, N) = map(int, stdin.readline().split(" "))
	train_data = np.array([map(float, stdin.readline().split(" ")) for _ in xrange(N)])
	T = int(stdin.readline())
	test_data = np.array([map(float, stdin.readline().split(" ")) for _ in xrange(T)])

	train_X = polynomial(train_data[:, :-1], P)
	train_y = train_data[:, -1]
	test_X = polynomial(test_data, P)

	w = np.dot(linalg.pinv(train_X), train_y)
	test_yhat = np.dot(test_X, w)
	print "\n".join([str(v) for v in test_yhat])