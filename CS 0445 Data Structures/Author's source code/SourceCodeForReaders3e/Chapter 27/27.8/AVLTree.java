package TreePackage;public class AVLTree<T extends Comparable<? super T>>             extends BinarySearchTree<T>              implements SearchTreeInterface<T>, java.io.Serializable{   public AVLTree()   {      super();   } // end default constructor   public AVLTree(T rootEntry)   {      super(rootEntry);   } // end constructor   // < Implementations of add and remove are here. A definition of add appears in Segment 27.12   //   of this chapter. Other methods in SearchTreeInterface are inherited. >   // . . .   // < Implementations of private methods to rebalance the tree using rotations are here. >   // . . .} // end AVLTree