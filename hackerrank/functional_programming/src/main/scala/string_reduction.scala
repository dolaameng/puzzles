object StringReduction {

	import io.Source.stdin

	def main(args: Array[String]): Unit = {
		val str = stdin.getLines.take(1).toList(0)
		val clean = str.foldLeft(("", Set[Char]() ))( (p, c) => {
				val (s, cs) = p
				if (s.contains(c)) (s, cs)
				else (s+c, cs+c)
			})._1
		println(clean)
	}
}