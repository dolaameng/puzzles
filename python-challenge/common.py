from functools import wraps

def solution_url(solution_fn):
	URL = "http://www.pythonchallenge.com/pc/def/%s.html"
	def _fn(*args, **kwargs):
		r = solution_fn(*args, **kwargs)
		return URL % str(r)
	return wraps(solution_fn)(_fn)