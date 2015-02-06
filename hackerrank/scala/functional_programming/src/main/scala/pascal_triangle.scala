object PascalTriangle {
	// n choose m = n-1 choose m-1 + n-1 choose m
	// triangle(r, c) = r choose c for c from 0 to n
	def tri1(n: Int): String = {
		def rec_tri1(row: Int, result: List[List[Int]]): List[List[Int]] = {
			if (row == n-1) result 
			else {
				val pre_row = result.head
				val cur_row = List.range(0, row+2).map( (col) => {
						if (col == 0) 1
						else if (col == row+1) 1
						else pre_row(col-1) + pre_row(col)
					} )
				rec_tri1(row+1, cur_row::result)
			}
		}
		rec_tri1(0, List[List[Int]](List(1))).reverse.map(_.mkString(" ")).mkString("\n")
	}
	import collection.mutable.ArrayBuffer
	def tri2(n: Int): String = {
		var result = ArrayBuffer[ArrayBuffer[Int]]()
		for (r <- 0 to n-1) {
			val row = ArrayBuffer.fill(r+1)(0)
			for (c <- 0 to r) {
				if (c == 0) row(c) = 1
				else if (c == r) row(c) = 1
				else row(c) = result(r-1)(c) + result(r-1)(c-1)
			}
			result += row 
		}
		result.map(_.mkString(" ")).mkString("\n")
	}

	def main(args: Array[String]): Unit = {
		println(tri1(5))
		println(tri2(5))
	}
}