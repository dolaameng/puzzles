object Solution {
	import io.Source.stdin
	import util.Random
	def neighbor(hits: List[(Int, Int)], N: Int, grid: Array[Array[Char]]): Option[(Int, Int)] = hits match {
		case Nil => None
		case _ => hits.flatMap({case (r,c) => List((r-1,c), (r+1,c), (r,c-1), (r,c+1))})
							.filter({case (r, c) => r >= 0 && r < N && c >= 0 && c < N})
							.filter({case (r, c) => grid(r)(c) == '-'})
							.headOption
	}
	def main(args: Array[String]): Unit = {
		val lines = stdin.getLines
		val N = lines.take(1).toList(0).toInt
		val grid = lines.take(N).toArray.map(_.toArray)
		val indices = for {r <- List.range(0, N); c <- List.range(0, N)} yield (r,c)
		val hits = indices.filter({case (r, c) => grid(r)(c) == 'h'})                                                                                                                      
		val nextMove = neighbor(hits, N, grid) match {
			case None => {
				val pos = indices.filter({case (r, c) => grid(r)(c) == '-'})
				pos(Random.nextInt(pos.length))
			}
			case Some(hit) => hit
		}
		println(f"${nextMove._1} ${nextMove._2}")
	}
}