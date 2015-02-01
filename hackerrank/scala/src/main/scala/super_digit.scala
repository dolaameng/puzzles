object SuperDigit {
	import io.Source.stdin
	import math.BigInt

	def main(args: Array[String]): Unit = {
		val line = stdin.getLines.take(1).toList(0).split(" ")
		val Array(n, k) = line.map(BigInt(_))

		def superDigit(n: BigInt): BigInt = {
			n.toString.foldLeft(BigInt(0))( (s, c) => s + (c-'0').toInt)
		}
		
		val r = Stream.iterate(k * superDigit(n))(superDigit(_)).find(_ < 10).get
		println(r)
	}
}