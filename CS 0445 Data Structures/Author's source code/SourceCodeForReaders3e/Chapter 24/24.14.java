public void inorderTraverse(){   StackInterface<BinaryNodeInterface<T>> nodeStack =                            new LinkedStack<BinaryNodeInterface<T>>();   BinaryNodeInterface<T> currentNode = root;   while (!nodeStack.isEmpty() || (currentNode != null))   {      // find leftmost node with no left child      while (currentNode != null)      {         nodeStack.push(currentNode);         currentNode = currentNode.getLeftChild();      } // end while      // visit leftmost node, then traverse its right subtree      if (!nodeStack.isEmpty())      {         BinaryNodeInterface<T> nextNode = nodeStack.pop();         assert nextNode != null; // since nodeStack was not empty                               // before the pop         System.out.println(nextNode.getData());         currentNode = nextNode.getRightChild();      } // end if   } // end while} // end inorderTraverse