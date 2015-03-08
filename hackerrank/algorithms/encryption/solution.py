from math import sqrt, ceil, floor

msg = raw_input()
nr = int(floor(sqrt(len(msg))))
nc = int(ceil(sqrt(len(msg))))

" ".join([msg[c::nc] for c in xrange(nc)])