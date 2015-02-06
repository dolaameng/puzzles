object SwapNodes {
	import io.Source.stdin

	sealed trait Tree[+T] {
		def inorder(): List[T] = this match {
			case Empty => List[T]()
			case Node(v, left, right) => left.inorder ++ (v::right.inorder)
		}
		def swap(depth: Int): Tree[T] = {
			def rec_swap(level: Int, tree: Tree[T]): Tree[T] = tree match {
				case Empty => Empty
				case Node(v, l, r) if level % depth == 0 => Node(v, rec_swap(level+1, r), rec_swap(level+1, l))
				case Node(v, l, r) => Node(v, rec_swap(level+1, l), rec_swap(level+1, r))
			}
			rec_swap(1, this)
		}
	}
	case object Empty extends Tree[Nothing]
	case class Node[T](value: T, left: Tree[T], right: Tree[T]) extends Tree[T]

	object Tree {
		def buildTree[T](root: T, nodes: Map[T, (T, T)], na: T): Tree[T] = nodes(root) match {
			case (left, right) if left==na && right==na => Node(root, Empty, Empty)
			case (left, right) if left==na => Node(root, Empty, buildTree(right, nodes, na))
			case (left, right) if right==na => Node(root, buildTree(left, nodes, na), Empty)
			case (left, right) => Node(root, buildTree(left, nodes, na), buildTree(right, nodes, na))
		} 
	}

	def main(args: Array[String]): Unit = {
		// parse input to the tree
		val lines = stdin.getLines
		val n = lines.take(1).toList(0).toInt
		val nodes = lines.take(n).toList.map(_.split(" ").map(_.toInt))
					.zipWithIndex.map({case (xs, i)=>(i+1 -> (xs(0)->xs(1)))}).toMap
		//for (k <- nodes.keys) {println(k); println(nodes(k))}
		val tree = Tree.buildTree(1, nodes, -1)
		//println(tree.inorder)
		val nswaps = lines.take(1).toList(0).toInt
		val depths = lines.take(nswaps).map(_.toInt).toList

		var t = tree
		for (d <- depths) {
			t = t.swap(d)
			println(t.inorder.mkString(" "))
		}
	}
}