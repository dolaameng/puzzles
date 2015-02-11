from sys import stdin

R, C = 10, 10
NTIMES = 5000
MAX_STEPS = 1000

def play(faces, ladders, snakes):
	fvalues, fprobs = zip(*faces)
	## TODO
	nsteps, pos = 0, 1
	while (nsteps <= MAX_STEPS and pos != R*C):
		pass
	return nsteps if nsteps <= MAX_STEPS else -1 

if __name__ == "__main__":
	
	ngames = int(stdin.readline())
	for _ in xrange(ngames):
		faces = zip(xrange(1, 7), map(float, stdin.readline().split(",")))
		nladders, nsnakes = map(int, stdin.readline().split(","))
		ladders = [tuple(map(int, pair.split(","))) for pair in stdin.readline().split(" ")]
		snakes = [tuple(map(int, pair.split(","))) for pair in stdin.readline().split(" ")]
		## play once
		nsteps = play(faces, ladders, snakes)