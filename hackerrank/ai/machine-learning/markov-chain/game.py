from sys import stdin
import random
from time import time


R, C = 10, 10
NTIMES = 5000
MAX_STEPS = 500



def play(faces, ladders, snakes):
	rnums = [random.random() for _ in xrange(MAX_STEPS)]
	steps = [[d for d, p in faces if p >= rn][0] for rn in rnums]
	##print [(k, v*1./MAX_STEPS) for k, v in Counter(steps).items()]
	pos = 1
	for nsteps, step_size in enumerate(steps, 1):
		if pos == R * C: break
		elif pos > R * C: continue
		else: 
			pos += step_size
			if pos in ladders: pos = ladders[pos]
			if pos in snakes: pos = snakes[pos]
	return nsteps

if __name__ == "__main__":
	ngames = int(stdin.readline())
	for _ in xrange(ngames):
		faces = zip(xrange(1, 7), map(float, stdin.readline().split(",")))
		vs, ps = zip(*faces)
		face_probs = [(vs[i], sum(ps[:i+1])) for i in xrange(6)]
		nladders, nsnakes = map(int, stdin.readline().split(","))
		ladders = dict([tuple(map(int, pair.split(","))) for pair in stdin.readline().split(" ")])
		snakes = dict([tuple(map(int, pair.split(","))) for pair in stdin.readline().split(" ")])
		## play once
		##print faces 
		nsteps = [play(face_probs, ladders, snakes) for _ in xrange(NTIMES)]
		#from collections import Counter
		#print Counter(nsteps)
		nsteps = [n for n in nsteps if n < MAX_STEPS]
		print int(sum(nsteps) * 1. / len(nsteps))
