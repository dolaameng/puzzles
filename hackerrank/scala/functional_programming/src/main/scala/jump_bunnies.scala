object JumpBunnies {
	import io.Source.stdin

	/*
	def main1(args: Array[String]): Unit = {
		val lines = stdin.getLines
		val steps = lines.take(2).toList(1).split(" ").map(_.toInt)

		val ns = Stream.from(1)
		val jumps = ns.map(n => steps.map(_ * n))
		val r = jumps.find(jmp => jmp.exists(j => steps.forall(j % _ == 0))).get
		println(r.filter(j => steps.forall(j%_==0)).min)
	}
	*/

	def gcd(a: BigInt, b: BigInt): BigInt = if (b == 0) a else gcd(b, a % b)

	def lcm(a: BigInt, b: BigInt): BigInt = (a*b)/gcd(a, b)

	def main(args: Array[String]): Unit = {
		val lines = stdin.getLines
		val steps = lines.take(2).toList(1).split(" ").map(BigInt(_))
		val r = steps.reduce(lcm(_, _))
		println(r)
	}
}