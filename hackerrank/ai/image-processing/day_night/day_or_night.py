import sys
import numpy as np

def rgb2gray(rgb):
	r, g, b = rgb[:,:,0], rgb[:, :, 1], rgb[:, :, 2]
	gray = 0.2989*r + 0.5870*g + 0.1140*b
	return gray

if __name__ == "__main__":
	img = np.asarray([ [map(int, pixel.split(",")) 
							for pixel in line.strip().split(" ")] 
							for line in sys.stdin.readlines()])
	gray = rgb2gray(img)
	plow, phigh = np.percentile(gray, [70, 100])
	#gray_robust = np.where((gray > p25) * (gray < p75), gray, 0)
	gray_robust = gray[np.where((gray > plow) * (gray < phigh))]

	gray_mean = gray_robust.mean()
	if (gray_mean > 128):
		print "day"
	else:
		print "night"
	