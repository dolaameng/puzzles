object Solution {
	def main(args: Array[String]): Unit = { 
		val m = Console.readLine.toInt
        val grid = new Array[String](m)
        for (i <- 0 until m) {
            grid.update(i, Console.readLine)
        }
    	displayPathtoPrincess(m,grid)
    }

  /* Refer to Output format section for more details */
	def displayPathtoPrincess(m:Int,grid:Array[String]): Unit = {
		val bot_cr = grid.map(line => line.indexOf("m")).zipWithIndex.filter(_._1 >= 0).head
		val princess_cr = grid.map(line => line.indexOf("p")).zipWithIndex.filter(_._1 >= 0).head
		val (dc, dr) = (princess_cr._1 - bot_cr._1, princess_cr._2 - bot_cr._2)
		val hmove = if (dc < 0) "LEFT" else "RIGHT"
		val vmove = if (dr < 0) "UP" else "DOWN"
		val moves = List.range(0, math.abs(dc)).map(_ => hmove) ++ List.range(0, math.abs(dr)).map(_ => vmove)
		println(moves.mkString("\n"))
	}
}