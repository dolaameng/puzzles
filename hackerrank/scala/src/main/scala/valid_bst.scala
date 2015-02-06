object ValidBST {
	import io.Source.stdin

	def isValidBST(xs: List[Int]): Boolean = {
		val pivot = xs.head
		val (left, right) = xs.tail.zipWithIndex.partition({case (x, i) => x < pivot})
		(left, right) match {
			case (Nil, Nil) => true
			case (Nil, _) => isValidBST(right.map(_._1))
			case (_, Nil) => isValidBST(left.map(_._1))
			case (_, _) => (left.map(_._2).max < right.map(_._2).min) && isValidBST(left.map(_._1)) && isValidBST(right.map(_._1))
		}
	}

	def main(args: Array[String]): Unit = {
		val lines = stdin.getLines
		val nTrials = lines.take(1).toList(0).toInt
		for (t <- List.range(0, nTrials)) {
			val xs = lines.drop(1).take(1).toList(0).split(" ").map(_.toInt).toList
			if (isValidBST(xs)) println("YES")
			else println("NO")
		}
	}
}