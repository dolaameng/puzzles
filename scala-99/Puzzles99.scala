/**
 * References: 
 * http://aperiodic.net/phil/scala/s-99/
 * https://github.com/jsuereth/scala-99-puzzles/blob/master/src/test/scala/suereth/TestNinetyNine.scala
 */

object Puzzles99 extends App {
  /**
   * Two main paradigms - functional and recursion 
   */
  /**
   * Working with Lists P01 - P28
   */
  /**
   * For recursion implementation, the usually direction includes
   * (1) Linear: P08, P06 - usually equivalent to a foldLeft/foldRight
   * The key to switch from empirical to FP is to use approxiate combine method to avoid mutation
   * (2) Tree DF: P07
   * (3) Twisted: P35 - two strips matching
   * (4) Varying Levels of Loops (tree): P26 -> reduce to two-level-loop case with recursion (bottom up)
   */
  val xs = List(1, 2, 5, -1, 100, 16, 99)
  val palindrome = List(1, 2, 5, -1, 5, 2, 1)
  val ys = List('a, 'a, 'a, 'a, 'b, 'c, 'c, 'a, 'a, 'd, 'e, 'e, 'e, 'e)
  val letters = List('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h, 'i)
  // P01: Find the last element of a list (builtin)
  println("P01:" + xs.last)
  // P02: Find the last but one of a list
  println("P02:" + xs.init.last)
  // P03: Find the kth element of a list
  println("P03:" + xs(3))
  // P04: Find the number of element in a list
  println("P04:" + xs.length)
  // P05: Reverse a list
  println("P05:" + xs.reverse)
  // P06: Find out whether a list is palindrome
  def isPalindrome[T](xs: List[T]) : Boolean = xs match {
    case Nil => true
    case x::Nil => true
    case _ => if (xs.head != xs.last) false else isPalindrome(xs.tail.init)
  }
  println("P06:" + isPalindrome(xs))
  println("P06:" + isPalindrome(palindrome))
  // P07: Flatten a nested list
  // Think this as a depth-first traverse - the boundary case is the leaf node
  def flatten(xs: List[Any]) : List[Any] = 
    xs flatMap {
    	case x : List[Any] => flatten(x)
    	case x => List(x)
  	}
  println("P07:" + flatten(List(List(1, 1), 2, List(3, List(5, 8)))))
  // P08: Eliminate consecutive duplicates of list elements
  def compress[T](xs: List[T]) : List[T] = xs match {
    case Nil => Nil
    case x::xxs => x::compress(xxs dropWhile (_ == x))
  }
  def compressFunctional[T](xs: List[T]) : List[T] = 
    xs.foldRight(List[T]())((x, xs) => if (xs.nonEmpty && x == xs.head) xs else x::xs) 
  println("P08:" + compress(ys))
  println("P08 (functional):" + compress(ys))
  // P09: Pack consecutive duplicates of list elements into sublists
  def pack[T](xs: List[T]) : List[List[T]] = xs match {
    case Nil => Nil
    case x::_ => {
      val (left, right) = xs span (_ == x)
      left::pack(right)
    }
  }
  def packFunctional[T](xs: List[T]) : List[List[T]] = 
    xs.foldRight(List(List[T]())) {
    case (x, List(Nil)) => List(x::Nil)
    case (x, xs::rest) => if (x == xs.head) (x::xs)::rest else List(x)::xs::rest
  }
  println("P09:" + pack(ys))
  println("P09:" + packFunctional(ys)) 
  // P10: Run-length encoding of a list
  def runLengthEncode[T](xs: List[T]):List[(Int, T)] = 
    pack(xs) map (xxs => (xxs.length, xxs.head))
  println("P10: " + runLengthEncode(ys))
  // P11: Modified run-length encoding
  // Modify : if an element has no duplicates it is simply copied into the result list
  def runLengthEncodeModified[T](xs: List[T]):List[Any] = 
    pack(xs) map {
    	case x::Nil => x
    	case xxs => (xxs.length, xxs.head)
    }
  println("P11: " + runLengthEncodeModified(ys))
  // P12:  Decode a run-length encoded list
  def runLengthDecode[T](xs : List[(Int, T)]) : List[T] = 
    xs flatMap {case (times, x) => (1 to times) map (_=>x)}
  println("P12: " + runLengthDecode(runLengthEncode(ys)))
  // P13: Direct implementation of run length encoding without pack
  def runLengthEncodeDirect[T](xs: List[T]) : List[(Int, T)] = xs match {
    case Nil => List[(Int, T)]()
    case x::xxs => {
      val (left, rest) = xs span (_ == x)
      (left.length, x)::runLengthEncodeDirect(rest)
    }
  }
  def runLengthEncodeFunctionalDirect[T](xs: List[T]):List[(Int, T)] = 
    xs.foldRight(List[(Int, T)]()){
    	case (x, Nil) => List((1, x))
    	case (x, (times, y)::accum) => if (x == y) (times+1, y)::accum else (1, x)::(times, y)::accum
    } 
  println("P13: " + runLengthEncodeFunctionalDirect(ys))
  println("P13: " + runLengthEncodeDirect(ys))
  // P14 - P15: Duplicate the elements of a list a given number of times
  def duplicate[T](n: Int, xs : List[T]) = 
    for (x <- xs; _ <- 1 to n) yield x
  println("P14-15: " + duplicate(3, List('a, 'b, 'c, 'd)))
  // P16: Drop every Nth element from a list
  def dropN[T](n: Int, xs: List[T]) : List[T] = 
    for ((x, i) <- xs.zipWithIndex; if i % n == 0) yield x
  println("P16: " + dropN(3, xs))
  // P17-18: Extract a slice of a list
  def slice[T](start: Int, end: Int, xs: List[T]) : List[T] = 
    //xs drop start take (end - start)
    xs slice (start, end)
  println("P17-18: " + slice(1, 3, xs))
  // P19: Rotate a list N places to the left
  def rotateLeft[T](n: Int, xs: List[T]) : List[T] = {
      val (left, right) = if (n >= 0) xs splitAt n else xs splitAt xs.length+n
      right ++ left
    }
  println("P19: " + rotateLeft(3, List('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h, 'i, 'j, 'k)))
  println("P19: " + rotateLeft(-2, List('a, 'b, 'c, 'd, 'e, 'f, 'g, 'h, 'i, 'j, 'k)))
  // P23: Extract a given number of randomly selected elements from a list (WITH REPLACEMENT)
  def randomSelect[T](n: Int, xs: List[T]) : Seq[T] = 
    for (_ <- (1 to n); i = scala.util.Random.nextInt(xs.length)) yield xs(i)
  println("P23: " + randomSelect(3, List('a, 'b, 'c, 'd, 'f, 'g, 'h)))
  // P25: Generate a random permutation of the elements of a list
  def randomPermute[T](xs: List[T]) = scala.util.Random.shuffle(xs)
  println("P25: " + randomPermute(List('a, 'b, 'c, 'd, 'e, 'f)))
  // P26: Generate the combinations of K distinct objects chosen from the N elements of a list
  def choose[T](n: Int, xs: List[T]) : List[List[T]] = n match {
      case 0 => List(List[Nothing]())
      //case 1 => xs map (List(_))
      case _ => for {
        (x, i) <- xs.zipWithIndex
        ys <- choose(n-1, (xs slice (i+1, xs.length))) // avoid duplicates
      } yield x::ys
    }
  println("P26: " + choose(3, List('a, 'b, 'c, 'd, 'e, 'f)).length)
  // P27: Group the elements of a set into disjoint subsets
  // Generalize the above predicate in a way that we can specify 
  // a list of group sizes and the predicate will return a list of groups
  // DONT count in different permutations of the same set
  def group[T](szs: List[Int], xs: List[T]) : List[List[List[T]]] = szs match {
    case Nil => List(List[Nothing]())
    case n::ns => for {
      first <- choose(n, xs)
      second <- group(ns, xs filterNot (first contains _) )
    } yield first::second
  }
  println("P27: " + group(List(2, 2, 5), letters))
  // P28: Sorting a list of lists according to length of sublists
  // lsortFreq(List(List('a, 'b, 'c), List('d, 'e), List('f, 'g, 'h), List('d, 'e), List('i, 'j, 'k, 'l), List('m, 'n), List('o)))
  // >> List[List[Symbol]] = List(List('i, 'j, 'k, 'l), List('o), List('a, 'b, 'c), List('f, 'g, 'h), List('d, 'e), List('d, 'e), List('m, 'n)
  // Note that in the above example, the first two lists in the result have length 4 and 1 and both lengths appear just once. 
  // The third and fourth lists have length 3 and there are two list of this length. 
  // Finally, the last three lists have length 2. This is the most frequent length.
  def lsortFreq[T](xs: List[List[T]]) : List[List[T]] = {
    val keyToLens = xs.map(x=>(x->x.length)) // List(k_len)
    val lenFreqs = for {
      (len, ks) <- keyToLens.groupBy{case (k, len) => len} // {len->List(k_len, ...)}
    } yield (len, ks.length)
    val keyToLenFreqs = keyToLens.map{case (k, len) => (k -> lenFreqs(len))}.sortBy(_._2)
    keyToLenFreqs map (_._1)
  }
  println("P28: "+ lsortFreq(List(List('a, 'b, 'c), List('d, 'e), List('f, 'g, 'h), List('d, 'e), List('i, 'j, 'k, 'l), List('m, 'n), List('o))))
  
  /**
   * Arithmetic P31 - P41
   */
  
  // P31: Determine whether a given integer number is prime
  implicit class EnhancedInt(val x: Int) {
    def isPrime = (2 to math.sqrt(x).toInt) forall (x % _ != 0)
    def gcd (that: EnhancedInt) : EnhancedInt = if (that.x == 0) this else (that.x gcd (x % that.x))
    def isCoPrime(that: EnhancedInt) : Boolean = (this gcd that).x == 1
    def totient = (1 to x).filter(isCoPrime(_)).length
    val primes = Stream.cons(2, Stream.from(3, 2).filter(_.isPrime))
    def primeFactors : List[Int] = {
      def primeFactorsR(n: Int, ps: Stream[Int]) : List[Int] = 
        if (n.isPrime) List(n) 
        else if (n % ps.head == 0) (ps.head)::primeFactorsR(n / ps.head, ps)
        else primeFactorsR(n, ps.tail)
      primeFactorsR(x, primes)
    }
    def primeFactorMultiplicity : List[(Int, Int)] = 
      this.primeFactors.foldRight(List[(Int, Int)]()){
      	case (x, Nil) => List((x ->1))
      	case (x, (y, times)::ys) => if (x == y) (y->(times+1))::ys else (x->1)::(y->times)::ys
      }
    def goldbach : (Int, Int) = {
      val p = primes.dropWhile(p => !(x-p).isPrime).head
      (p -> (x-p))
    }
    override def toString = x.toString
  }
  println("P31: " + 7.isPrime)
  // P32: Determine the greatest common divisor of two positive integer numbers
  println("P32: " + (36 gcd 63))
  // P33: Determine whether two positive integer numbers are coprime
  println("P33: " + (35 isCoPrime 64))
  // P34: Calculate Euler's totient function phi(m)
  // Euler's so-called totient function phi(m) is defined as 
  // the number of positive integers r (1 <= r <= m) that are coprime to m
  println("P34: " + 10.totient)
  // P35: Determine the prime factors of a given positive integer
  println("P35: " + 315.primeFactors) // 3, 3, 5, 7
  // P36: Determine the prime factors of a given positive integer (2).
  // Construct a list containing the prime factors and their multiplicity
  println("P36: " + 315.primeFactorMultiplicity)
  // P40: Goldbach's conjecture
  // Goldbach's conjecture says that every positive even number 
  // greater than 2 is the sum of two prime numbers. E.g. 28 = 5 + 23.
  println("P40: " + 28.goldbach)
  println("P40: " + 1000.goldbach)
  // P41: A list of Godbach decomposition
  // Given a range of integers by its lower and upper limit, 
  // print a list of all even numbers and their Goldbach composition.
  def goldbachList(xs: Seq[Int]) : Seq[String] =
    for (x <- xs if x % 2 == 0) yield x.goldbach match {case (p1, p2) => s"$x = $p1 + $p2"}  
  println("P41: " + goldbachList(9 to 20))
  
  /** Logic and Codes P46 - P50
   *  
   */
  
  // P49: Gray Code An n-bit Gray code is a sequence of n-bit strings constructed according to certain rules
  // n = 1: C(1) = ("0", "1").
  // n = 2: C(2) = ("00", "01", "11", "10").
  // n = 3: C(3) = ("000", "001", "011", "010", "110", "111", "101", "100").
  def gray(n: Int) : List[String] = 
    if (n == 1) List("0", "1")
    else {
      val tail = gray(n-1)
      tail.map("0"+_) ++ tail.reverse.map("1"+_)
    }
  println(gray(3))
  // P50: Huffman code (minimized weighted code length prefix tree encoding)
  // Input = terms and their frequency
  // Output = terms and their encodings in binary tree
  // e.g. huffman(List(("a", 45), ("b", 13), ("c", 12), ("d", 16), ("e", 9), ("f", 5)))
  // List[String, String] = List((a,0), (b,101), (c,100), (d,111), (e,1101), (f,1100))
  object huffman {
	  sealed trait HuffmanTree {
	    val term : String
	    val freq : Int
	  }
	  case class HuffmanLeaf(tf: (String, Int)) extends HuffmanTree {
	    val (term, freq) = tf
	  }
	  case class HuffmanNode(tf: (String, Int), left: HuffmanTree, right: HuffmanTree) extends HuffmanTree {
	    val (term, freq) = tf
	  }
	  def buildHuffmanTree(tfs: List[(String, Int)]) : HuffmanTree = 
	    buildHuffmanTreeR(tfs.map(tf => HuffmanLeaf(tf)))
	  def buildHuffmanTreeR[T](nodes: List[HuffmanTree]) : HuffmanTree = nodes.sortBy(_.freq) match {
	    case n1::n2::Nil => HuffmanNode(((n1.term+n2.term) -> (n1.freq+n2.freq)), n1, n2)
	    case n1::n2::rest => buildHuffmanTreeR(HuffmanNode(((n1.term+n2.term) -> (n1.freq+n2.freq)), n1, n2)::rest)
	  }
	  def visitLeavesR(tree: HuffmanTree) : List[(String, String)] = tree match {
	    case n: HuffmanLeaf => List((n.tf._1 -> "")) // better be case HuffmanLeaf(tf)
	    case n: HuffmanNode => visitLeavesR(n.left).map{case (t, c) => (t-> ("0"+c))} ++ 
	    					visitLeavesR(n.right).map{case (t, c)=>(t->("1"+c))}
	  }
	  def encode(tfs: List[(String, Int)]) : List[(String, String)] = {
	    val tree = buildHuffmanTree(tfs)
	    visitLeavesR(tree).sortBy(_._1)
	  }
  }
  val tfs = List(("a", 45), ("b", 13), ("c", 12), ("d", 16), ("e", 9), ("f", 5))
  println("P50: " + huffman.encode(tfs))
  
  /** 
   *  Binary Trees P55 - P69
   */
  object bt {
    sealed trait Tree[+T] {
      def numOfNodes : Int
      def addNode[U >: T <% Ordered[U]](value: U) : Tree[U]
      def preorder : List[T]
      def inorder : List[T]
    }
    case object Empty extends Tree[Nothing] {
      override def toString = "."
      def numOfNodes = 0
      def addNode[U  <% Ordered[U]](value: U) : Tree[U] = new Node(value, Empty, Empty)
      def preorder : List[Nothing] = Nil
      def inorder : List[Nothing] = Nil
    }
    case class Node[T] (val value: T, left: Tree[T], right: Tree[T]) extends Tree[T] {
      override def toString = s"$value($left,$right)"
      def numOfNodes: Int = 1 + left.numOfNodes + right.numOfNodes
      def addNode[U >: T <% Ordered[U]] (value : U) : Tree[U] = 
        if (value == this.value) this
        else if (value < this.value) new Node(this.value, left.addNode(value), right)
        else new Node(this.value, left, right.addNode(value))
      def preorder : List[T] = 
        value::(left.preorder ++ right.preorder)
      def inorder : List[T] = left.inorder ++ (value::right.inorder)
    }
    object Node {
      def apply[T](value: T) = new Node(value, Empty, Empty)
    }
    
    def allBalanced[T](n: Int, v: T) : Set[Tree[T]] = {
      val newNode = new Node(v, Empty, Empty)
      def appendNode(balancedTree: Tree[T]) : List[Tree[T]] = {
        balancedTree match {
          case Empty => List(newNode)
          case Node(value, left, right) => {
            val ln = left.numOfNodes
            val rn = right.numOfNodes
            if (ln == rn) {
              appendNode(left).map(Node(value, _, right)) ++
          								appendNode(right).map(Node(value, left, _))
            }else if (ln < rn) appendNode(left).map(Node(value, _, right))
            else appendNode(right).map(Node(value, left, _))
          }
        }
      }
      if (n == 1) Set(newNode)
      else allBalanced(n-1, v).flatMap(appendNode(_)).toSet
    }
    
    def isSymmetric[T](tree: Tree[T]): Boolean = {
      def isMirror(treea: Tree[T], treeb: Tree[T]) : Boolean = (treea, treeb) match {
        case (Empty, Empty) => true
        case (Empty, _) => false
        case (_, Empty) => false
        case (Node(_, lefta, righta), Node(_, leftb, rightb)) => isMirror(lefta, rightb) && isMirror(leftb, righta)
      }
      tree match {
      	case Empty => true
      	case Node(_, left, right) => isMirror(left, right)
      }
    }
    
    def addNodes[U <% Ordered[U]]( xs: List[U]) : Tree[U] = {
      xs.foldLeft(Empty : Tree[U]){case (t, x) => t.addNode(x)}
    }
    
    def symmetricBalancedTrees[T](n: Int, x: T) : Set[Tree[T]] = 
      allBalanced(n, x).filter(isSymmetric(_))
      
    def countLeaves[T](tree: Tree[T]) : Int = tree match {
      case Empty => 0
      case Node(_, left, right) => 1 + countLeaves(left) + countLeaves(right)
    }
    def findLeaves[T](tree: Tree[T]) : List[T] = tree match {
      case Empty => List[Nothing]()
      case Node(v, left, right) => v::(findLeaves(left) ++ findLeaves(right))
    }
    def findInternals[T](tree: Tree[T]) : List[T] = tree match {
      case Node(_, Empty, Empty) => List[Nothing]()
      case Empty => List[Nothing]()
      case Node(x, left, right) => x::(findInternals(left)++findInternals(right))
    }
    def findAtLevel[T](tree: Tree[T], n: Int) : List[T] = 
      if (n == 1) tree match {
        case Empty => List[Nothing]()
        case Node(v, _, _) => List(v)
      }
      else tree match {
        case Empty => List[Nothing]()
        case Node(_, left, right) => findAtLevel(left, n-1) ++ findAtLevel(right, n-1)
      } 
    // e.g. a(b(d(.,.),e(.,.)),c(.,f(g(.,.),.)))
    def parse(s: String) : Tree[Char] = {
      if (s == ".") Empty : Tree[Char]
      else {
	      def splitPoint(s: String) : Int = {
	        val lrps = s.foldLeft(List[(Int, Int)]((0 -> 0))){
	        	case (pNums, x) => {
	        		val (lp, rp) = pNums.last
	        		if (x == '(') pNums :+ ((lp+1)->rp)
	        		else if (x == ')') pNums :+ (lp->(rp+1))
	        		else pNums :+ (lp->rp)
	         	} 
	        }
	        val r = s.zipWithIndex.find{case (x, i) => x==','&&lrps(i)._1==lrps(i)._2+1}
	        r match {
	          case None => -1
	          case Some(i) => i._2
	        }
	      }
	     val (lpart, rpart) = s splitAt splitPoint(s)
	     val v = lpart(0)
	     val l = lpart.substring(2) 
	     val r = rpart.substring(1, rpart.length-1) // ,
	     Node(v, parse(l), parse(r))
      }
    }
    def preInTree[T](pre: List[T], in: List[T]) : Tree[T] = 
      if (pre.length == 0) Empty
      else {
        val t = pre(0)
        val inLeft = in takeWhile (_!=t)
        val _::inRight = in dropWhile (_!=t)
        val preLeft = pre filter (inLeft contains _)
        val preRight = pre filter (inRight contains _)
        Node(t, preInTree(preLeft, inLeft), preInTree(preRight, inRight))
      }
  }
  // P55: Construct completely balanced binary trees
  // In a completely balanced binary tree, the following property holds for every node: 
  // The number of nodes in its left subtree and the number of nodes in its right subtree are almost equal, 
  // which means their difference is not greater than one
  println("P55: " + bt.allBalanced(4, 'x').mkString("\n"))
  // P56: Symmetric binary trees
  // Let us call a binary tree symmetric 
  // if you can draw a vertical line through the root node and then the right subtree is the mirror image of the left subtree
  // We are only interested in the structure, not in the contents of the nodes
  val tree = bt.Node('a, bt.Node('b, bt.Node('c, bt.Empty, bt.Empty), bt.Empty), 
		  			  bt.Node('d, bt.Empty, bt.Node('e, bt.Empty, bt.Empty)))
  println("P56: " + bt.isSymmetric(tree))
  println("P56: " + bt.isSymmetric(tree.left))
  // P57: Binary search trees (dictionaries), e.g.
  // scala> End.addValue(2)
  // res0: Node[Int] = T(2 . .)
  // scala> res0.addValue(3)
  // res1: Node[Int] = T(2 . T(3 . .))
  // scala> res1.addValue(0)
  // res2: Node[Int] = T(2 T(0 . .) T(3 . .))
  // Hint: The signature of addValue should be addValue[U >: T <% Ordered[U]](x: U): Tree[U]
  val t = bt.addNodes(List(2, 3, 0, 1, 6))
  println("P57: " + t)
  println("P57: " + bt.isSymmetric(bt.addNodes(List(5, 3, 18, 1, 4, 12, 21))))
  println("P57: " + bt.isSymmetric(bt.addNodes(List(3, 2, 5, 7, 4))))
  // P58: Apply the generate-and-test paradigm to construct all symmetric, completely balanced binary trees with a given number of nodes
  println("P58: " + bt.symmetricBalancedTrees(5, 'x'))
  // P61: Count the leaves of a binary tree
  println("P61: " + bt.countLeaves(bt.Node('x', bt.Node('x', bt.Empty, bt.Empty), bt.Empty)))
  // P61A: Collect the leaves of a binary tree in a list
  println("P61A: " + bt.findLeaves(bt.Node('a', bt.Node('b', bt.Empty, bt.Empty), bt.Empty)))
  // P62: Collect the internal nodes of a binary tree in a list
  println("P62: " + bt.findInternals(tree))
  // P62B: Collect the nodes at a given level in a list (root is at level 1)
  println("P62B: " + bt.findAtLevel(tree, 2))
  // P67: A string representation of binary trees
  // the reverse of toString method, e.g. a(b(d(.,.),e(.,.)),c(.,f(g(.,.),.)))
  val sTree = bt.Node('a', bt.Node('b', bt.Node('d'), bt.Node('e')), 
		  				   bt.Node('c', bt.Empty, bt.Node('f', bt.Node('g'), bt.Empty)))
  println("P67: " + sTree)
  val tStr = "a(b(d(.,.),e(.,.)),c(.,f(g(.,.),.)))"
  println("P67: " + bt.parse(tStr))
  // P68: Preorder and Inorder traverse
  println("P68: " + sTree.preorder)
  println("P68: " + sTree.inorder)
  // P68b: If both the preorder sequence and the inorder sequence of the nodes of a binary tree are given, 
  // then the tree is determined unambiguously. 
  // Write a method preInTree that does the job.
  val preorder = List('a', 'b', 'd', 'e', 'c', 'f', 'g')
  val inorder = List('d', 'b', 'e', 'a', 'c', 'g', 'f')
  println("P68b: " + bt.preInTree(preorder, inorder))
  /**
   * Multiway Trees P70 - P73
   */
  
  /**
   * Graphs P80 - P89
   */
  
  /** 
   *  Miscs P90 - P99
   */
}