object ListGCD {
	import io.Source.stdin

	def gcd(n1: Map[Int, Int], n2: Map[Int, Int]): Map[Int, Int] = {
		n1.keySet.intersect(n2.keySet).map(k => (k, if (n1(k) < n2(k)) n1(k) else n2(k) )).toMap
	}

	def collectiveGcd(nums: List[Map[Int, Int]]): Map[Int, Int] = nums match {
		case Nil => Map[Int, Int]()
		case h::Nil => h
		case h1::h2::t => collectiveGcd(gcd(h1,h2)::t)//gcd(h, collectiveGcd(t))
	}

	def main(args: Array[String]): Unit = {
		val lines = stdin.getLines
		val n = lines.take(1).toList(0).toInt
		val nums = lines.take(n).map(_.split(" ")
										.map(_.toInt).grouped(2)
										.map(x=>(x(0), x(1))).toMap).toList
		val factor = collectiveGcd(nums)
		println(factor.toList.sortBy({case (k, v) => k}).map({case (k, v) => f"$k $v"}).mkString(" "))
		//println(nums.map(_.mkString))
	}
}