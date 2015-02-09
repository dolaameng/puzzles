object Solution2 {
	 def main(args: Array[String]): Unit = { 
        val n = Console.readInt
        var x_y = Console.readLine.split(" ")
        val r = x_y(0).toInt
        val c = x_y(1).toInt
        val grid = new Array[String](n)
        for (i <- 0 until n) {
            grid.update(i, Console.readLine)
        }
        nextMove(n,r,c,grid)
    }

  /* Refer to Output format section for more details */
	def nextMove(m:Int,grid:Array[String]): Unit = {
		val bot_cr = grid.map(line => line.indexOf("m")).zipWithIndex.filter(_._1 >= 0).head
		val princess_cr = grid.map(line => line.indexOf("p")).zipWithIndex.filter(_._1 >= 0).head
		val (dc, dr) = (princess_cr._1 - bot_cr._1, princess_cr._2 - bot_cr._2)
		if (dc < 0) println("LEFT")
		else if (dc > 0) println("RIGHT")
		else if (dr < 0) println("UP")
		else println("DOWN")
	}
}