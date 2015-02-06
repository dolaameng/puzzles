

object StringMingling {
	import io.Source.stdin
	def main(args: Array[String]): Unit = {
		val lines = stdin.getLines().take(2).toList
		val mixed = lines match {
			case p::q::Nil => p.zip(q).foldRight(List[Char]())((ab, s) => ab._1::ab._2::s).mkString
			case _ => None
		}
		println(mixed)
	}
}

