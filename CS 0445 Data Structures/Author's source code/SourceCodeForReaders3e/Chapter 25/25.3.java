SearchTreeInterface<Person> myTree = new BinarySearchTree<Person>();Person whitney = new Person("Whitney", "111223333");Person returnValue = myTree.add(whitney);Person whitney2 = new Person("Whitney", "444556666");returnValue = myTree.add(whitney2);returnValue = myTree.getEntry(whitney);returnValue = myTree.remove(whitney);