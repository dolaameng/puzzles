object Solution {
	import io.Source.stdin
	import math.BigInt
	def main (args: Array[String]): Unit = {
        val lines = stdin.getLines
		val N = lines.take(1).toList(0).toInt
		val xs = lines.take(N).map(BigInt(_)).toList
		val maxn = xs.reduce(_ max _)
		//println(lines.mkString(" "))
		//println(maxn)
		lazy val allFibs : Stream[BigInt] = BigInt(0) #:: BigInt(1) #:: allFibs.zip(allFibs.tail).map({case (a, b) => a + b})
		val fibs = allFibs.takeWhile(_ <= maxn)
		println(xs.map( x=> {if (fibs.contains(x)) "IsFibo" else "IsNotFibo" }).mkString("\n"))
		//xs foreach println
	}
} 