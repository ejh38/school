package TreePackage;import java.util.Iterator;import java.util.NoSuchElementException;import StackAndQueuePackage.*; // neede by tree iteratorspublic class BinaryTree<T> implements BinaryTreeInterface<T>,{   private BinaryNodeInterface<T> root;   public BinaryTree()   {      root = null;   } // end default constructor   public BinaryTree(T rootData)   {      root = new BinaryNode<T>(rootData);   } // end constructor   public BinaryTree(T rootData, BinaryTree<T> leftTree,                                  BinaryTree<T> rightTree)   {      privateSetTree(rootData, leftTree, rightTree);   } // end constructor   public void setTree(T rootData)   {      root = new BinaryNode<T>(rootData);   } // end setTree   public void setTree(T rootData, BinaryTreeInterface<T> leftTree,                                   BinaryTreeInterface<T> rightTree)   {      privateSetTree(rootData, (BinaryTree<T>)leftTree,                                (BinaryTree<T>)rightTree);   } // end setTree   private void privateSetTree(T rootData, BinaryTree<T> leftTree,                                           BinaryTree<T> rightTree)   {      // < FIRST DRAFT - See Segments 24.5 - 24.8 for improvements. >      root = new BinaryNode<T>(rootData);      if (leftTree != null)         root.setLeftChild(leftTree.root);               if (rightTree != null)         root.setRightChild(rightTree.root);   } // end privateSetTree   //  < Implementations of getRootData, getHeight, getNumberOfNodes, isEmpty, clear,   //    and the methods specified in TreeIteratorInterface are here. >   //  . . .} // end BinaryTree