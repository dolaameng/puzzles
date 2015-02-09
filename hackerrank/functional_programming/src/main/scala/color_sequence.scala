object ColorSequence {
	import io.Source.stdin
	import math.abs

	def isFullColor(str: List[Char], rgyb: (Int, Int, Int, Int)): Boolean = {
		val (r, g, y, b) = rgyb
		if (str.isEmpty) (r == g) && (y == b)
		else if (abs(r-g) > 1 || abs(y-b) > 1) false
		else str match {
			case 'R'::tail => isFullColor(tail, (r+1, g, y, b)) 
			case 'G'::tail => isFullColor(tail, (r, g+1, y, b))
			case 'Y'::tail => isFullColor(tail, (r, g, y+1, b))
			case 'B'::tail => isFullColor(tail, (r, g, y, b+1))
			case _ => throw new IllegalArgumentException("invalid string")
		}
	}

	def main(args: Array[String]): Unit = {
		val lines = stdin.getLines
		val n = lines.take(1).toList(0).toInt
		val strs = lines.take(n).toList

		val solutions = strs.map(s => isFullColor(s.toList, (0, 0, 0, 0)))
		solutions.map(if (_) "True" else "False").foreach(println)
	}
}