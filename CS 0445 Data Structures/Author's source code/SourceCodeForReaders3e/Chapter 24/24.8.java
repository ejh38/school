private void privateSetTree(T rootData, BinaryTree<T> leftTree,                                         BinaryTree<T> rightTree){   root = new BinaryNode<T>(rootData);   if ((leftTree != null) && !leftTree.isEmpty())      root.setLeftChild(leftTree.root);       if ((rightTree != null) && !rightTree.isEmpty())   {      if (rightTree != leftTree)         root.setRightChild(rightTree.root);      else         root.setRightChild(rightTree.root.copy());   } // end if   if ((leftTree != null) && (leftTree != this))      leftTree.clear();        if ((rightTree != null) && (rightTree != this))      rightTree.clear();} // end privateSetTree