object SuperQueens {
	import io.Source.stdin
	import math.abs 
	

	def main(args: Array[String]): Unit = {
		val N = stdin.getLines.take(1).toList(0).toInt

		def placeQueens(k: Int): List[List[Int]] = {
			if (k == 0) List(List())
			else for {
				queens <- placeQueens(k - 1)
				column <- List.range(1, N+1).filterNot(queens.toSet)
				if isSafe(column, queens)
				} yield column::queens
		}

		def isSafe(col: Int, queens: List[Int]) : Boolean = {
			val rows = List.range(N-queens.length+1, N+1)
			val rcs = rows.zip(queens)
			val row = N-queens.length
			if (queens.contains(col)) false
			else if (rcs.exists({case (r, c) => abs(r-row)==abs(c-col)})) false
			else if (rcs.exists({case (r, c) => abs(r-row)+abs(c-col) <= 3})) false
			else true
		}

		val solutions = placeQueens(N).map(List.range(1, N+1).zip(_))
		println(solutions.length)
	}
}