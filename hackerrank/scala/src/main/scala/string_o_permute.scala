object StringOPermute {
	import io.Source.stdin
	def permute(str: String): String = {
		val n = str.length / 2
		val odds = Iterator.from(0, 2).take(n)
		val evens = Iterator.from(1, 2).take(n)
		val index = evens.zip(odds).foldRight(List[Int]())((p, xs) => p._1::p._2::xs)
		index.map(str(_)).mkString
	}
	def main(args: Array[String]): Unit = {
		val input = stdin.getLines()
		val nlines = input.take(1).map(_.toInt).toList(0)
		val lines = input.take(nlines).toList
		val permuted = lines.map(permute)
		permuted.foreach(println)
	}
}