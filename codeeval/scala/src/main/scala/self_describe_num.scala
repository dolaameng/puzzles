object SelfDescribeNum {
	import io.Source

	def isSelfDescribed(s: String) : Int = {
		val dict = s.groupBy(x => x - '0').map({case (k, v) => (k, v.length)})
		if (s.zipWithIndex.forall({case (x, i) => (x -'0') == dict.getOrElse(i, 0)})) 1
		else 0
	}

	def main(args: Array[String]): Unit = {
		val source = Source.fromFile(args(0))
		val lines = source.getLines.filter(_.length > 0)
		lines.map(isSelfDescribed).foreach(println)
	}
}