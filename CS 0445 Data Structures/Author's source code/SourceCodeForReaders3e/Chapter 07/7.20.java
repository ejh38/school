public void display(){   displayChain(firstNode);} // end displayprivate void displayChain(Node nodeOne) {   if (nodeOne != null)   {      System.out.println(nodeOne.getData()); // display data in first node      displayChain(nodeOne.getNextNode());   // display rest of chain   } // end if} // end displayChain