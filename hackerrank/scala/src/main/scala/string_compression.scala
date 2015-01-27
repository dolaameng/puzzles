object StringCompression {
	import io.Source.stdin
	private def compress(s: String): String = {
		s.foldLeft( (' ', List[(Char, Int)]()) )( (accu, c) => {
				val pre_c = accu._1
				val cs = accu._2
				if (pre_c == c) (c, (c, cs.head._2+1)::cs.tail)
				else (c, (c, 1)::cs) 
			})._2.reverse
				.map({case (c, n) => if (n > 1) f"$c$n" else f"$c"})
				.mkString
	}
	def main(args: Array[String]): Unit = {
		val line = stdin.getLines().take(1).toList(0)
		println(compress(line))
	}
}