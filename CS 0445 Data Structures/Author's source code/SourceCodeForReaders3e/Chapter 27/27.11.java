private BinaryNodeInterface<T> rebalance(BinaryNodeInterface<T> nodeN){   int heightDifference = getHeightDifference(nodeN);   if (heightDifference > 1)   {  // left subtree is taller by more than 1,       // so addition was in left subtree      if (getHeightDifference(nodeN.getLeftChild()) > 0)         // addition was in left subtree of left child         nodeN = rotateRight(nodeN);      else         // addition was in right subtree of left child         nodeN = rotateLeftRight(nodeN);   }   else if (heightDifference < -1)   {  // right subtree is taller by more than 1,       // so addition was in right subtree      if (getHeightDifference(nodeN.getRightChild()) < 0)         // addition was in right subtree of right child         nodeN = rotateLeft(nodeN);      else         // addition was in left subtree of right child         nodeN = rotateRightLeft(nodeN);   } // end if   // else nodeN is balanced   return nodeN;} // end rebalance