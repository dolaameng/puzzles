object RangeMinQuery {

	import io.Source.stdin

	abstract class SegmentTree {
		val min: Int 
		val lb: Int 
		val rb : Int 
		def findMin(l: Int, r: Int): Int = {
			if (l <= lb && rb <= r) min 
			else if (l > rb || r < lb) 1000000
			else this match {
				case leaf:SegmentLeaf => throw new Exception()
				case SegmentNode(_, _, _, lchild, rchild) => {
					val lmin = lchild.findMin(l, r)
					val rmin = rchild.findMin(l, r)
					if (lmin < rmin) lmin else rmin 
				}
			}
		}
	}
	case class SegmentLeaf (lb: Int, rb: Int, min: Int) extends SegmentTree {
	}
	case class SegmentNode (min: Int, 
						lb: Int, rb: Int,
						lchild: SegmentTree, 
						rchild: SegmentTree) extends SegmentTree {
	}

	object SegmentTree {
		def buildTree(xs: List[Int], lb: Int, rb: Int) : SegmentTree = xs match {
			case List(x) => {
				//println("LEAF: ", x, lb, rb)
				//assert (lb == rb)
				SegmentLeaf(lb, rb, x)
			}
			case _ => {
				val sep = xs.length / 2
				val (lxs, rxs) = xs.splitAt(sep)
				val ltree = buildTree(lxs, lb, lb+sep-1)
				val rtree = buildTree(rxs, lb+sep, rb)
				val minValue = if (ltree.min < rtree.min) ltree.min else rtree.min 
				SegmentNode(minValue, lb, rb, ltree, rtree)
			}
		}
		def apply(xs: List[Int]) : SegmentTree = {
			buildTree(xs, 0, xs.length-1)
		}
	}

	def main (args: Array[String]): Unit = {
		val lines = stdin.getLines
		val Array(n, m) = lines.next.split(" ").map(_.toInt)
		val xs = lines.next.split(" ").map(_.toInt).toList
		val tree = SegmentTree(xs)
		//println(tree)
		for (t <- List.range(0, m)) {
			val Array(l, r) = lines.next.split(" ").map(_.toInt)
			println(tree.findMin(l, r))
		}
	}
}