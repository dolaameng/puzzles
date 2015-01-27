object CrossWords {
	import io.Source.stdin
	def main(args: Array[String]): Unit = {
		val lines = stdin.getLines()
		val grid = lines.take(10).toList
		val words = lines.take(1).toList(0).split(";")
		println(words(3))
		println(grid)
		println("to be done")
	}
}