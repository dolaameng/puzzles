object FilterElements {
	import io.Source.stdin

	def main(args: Array[String]): Unit = {
		val lines = stdin.getLines
		val T = lines.take(1).toList(0).toInt
		val solutions = List.range(1, T+1).map { _ => 
			val k = lines.take(1).toList(0).split(" ")(1).toInt
			val xs = lines.take(1).toList(0).split(" ").map(_.toInt)
			val (rdups, dupCounts) = xs.foldLeft( (List[Int](), Map[Int,Int]()) )({
				case ((ux, m), x) => {
					if (m.contains(x)) (ux, m.updated(x, m(x)+1))
					else (x::ux, m.updated(x, 1))
				}
			})
			val dups = rdups.reverse
			val solution = dups.zip(dups.map(dupCounts(_))).filter(_._2 >= k).map(_._1)
			if (solution.isEmpty) "-1"
			else solution.mkString(" ")
		}
		solutions.foreach(println)
	}
}