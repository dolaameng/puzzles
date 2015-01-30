object PrefixCompression {
	import io.Source.stdin;

	private def prefix(s1: List[Char], s2: List[Char], p: List[Char]): (List[Char], List[Char], List[Char]) = (s1, s2) match {
		case (_, Nil) => (s1, s2, p.reverse)
		case (Nil, _) => (s1, s2, p.reverse)
		case (h1::t1, h2::t2) if h1 == h2 => prefix(t1, t2, h1::p)
		case (s1, s2) => (s1, s2, p.reverse)
	}

	def main(args: Array[String]): Unit = {
		val lines = stdin.getLines
		val str1 = lines.take(1).toList(0)
		val str2 = lines.take(1).toList(0)
		val r = prefix(str1.toList, str2.toList, List[Char]())
		val r1 = r._1.mkString
		val r2 = r._2.mkString
		val p = r._3.mkString
		println(f"${p.length}%d $p%s\n${r1.length}%d ${r1}%s\n${r2.length}%d ${r2}%s\n");
	}
}