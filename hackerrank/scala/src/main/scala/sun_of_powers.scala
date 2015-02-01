object SumOfPowers {
	import io.Source.stdin
	import math.{ceil, sqrt, pow}

	def main(args: Array[String]): Unit = {
		val lines = stdin.getLines.take(2).toList.map(_.toInt)
		val X = lines(0)
		val N = lines(1)
		//val sqrs = List.range(1, sqrt(X).toInt+2).map( x => x*x -> x).toMap

		def factor(num: Int, candidates: List[Int]): List[List[Int]] = num match {
			case 0 => List[List[Int]](List[Int]())
			case n if n <0 => List[List[Int]]()
			case _ => for { x <- candidates; 
							f <- factor(num - pow(x, N).toInt, candidates.filter(_ > x))} yield x::f
		}

		val solutions = factor(X, List.range(1, sqrt(X).toInt + 2))
		println(solutions.length)
	}
}