public int getHeight(){   return getHeight(this); // call private getHeight} // end getHeightprivate int getHeight(BinaryNode<T> node){   int height = 0;     if (node != null)      height = 1 + Math.max(getHeight(node.left),                             getHeight(node.right));                             return height;} // end getHeightpublic int getNumberOfNodes(){   int leftNumber = 0;   int rightNumber = 0;   if (left != null)      leftNumber = left.getNumberOfNodes();       if (right != null)      rightNumber = right.getNumberOfNodes();       return 1 + leftNumber + rightNumber;} // end getNumberOfNodes