public void add(T newEntry){   Node newNode = new Node(newEntry);    Node nodeBefore = getNodeBefore(newEntry);   if (nodeBefore == null) // no need to call isEmpty      addFirstNode(newNode);   else      addAfterNode(nodeBefore, newNode);} // end add