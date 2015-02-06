object MatrixRotation {
	import io.Source.stdin

	def shiftRight[T](xs: List[T], k: Int): List[T] = {
		val times = k % xs.length
		xs.slice(xs.length-times, xs.length) ++ xs.slice(0, xs.length-times)
	}

	def rotate(mat: Array[Array[Int]], nr: Int, nc: Int, k:Int) : Array[Array[Int]] = {
		val borderRows = List.range(0, nr) ++ List.fill(nc-2)(nr-1) ++ List.range(nr-1, -1, -1) ++ List.fill(nc-2)(0)
		val borderCols = List.fill(nr)(0) ++ List.range(1, nc-1) ++ List.fill(nr)(nc-1) ++ List.range(nc-2, 0, -1)
		val border = borderRows.zip(borderCols)
		val new_border = shiftRight(border, k)//border.tail :+ border.head
		//println(border)
		//println(new_border)
		var new_mat = mat.map(_.clone) //deep copy
		border.zip(new_border).foreach({case ((r, c), (rr, cc)) => new_mat(r)(c)=mat(rr)(cc)})
		if (nr > 2 && nc > 2) {
			val submat = mat.slice(1, nr-1).map(_.slice(1, nc-1))
			val new_submat = rotate(submat, nr-2, nc-2, k)
			for (r <- List.range(1, nr-1); c <- List.range(1, nc-1)) {
				new_mat(r)(c) = new_submat(r-1)(c-1)
			}
		}
		new_mat
	}

	def main(args: Array[String]): Unit = {
		val lines = stdin.getLines
		val MNR = lines.take(1).toList(0).split(" ").map(_.toInt)
		val M = MNR(0); val N = MNR(1); val R = MNR(2)
		val mat = lines.take(M).toArray.map(_.split(" ").map(_.toInt).toArray)
		var new_mat = mat
		new_mat = rotate(new_mat, M, N, R)
		//println(mat.map(_.mkString(" ")).mkString("\n"))
		println(new_mat.map(_.mkString(" ")).mkString("\n"))
	}
}