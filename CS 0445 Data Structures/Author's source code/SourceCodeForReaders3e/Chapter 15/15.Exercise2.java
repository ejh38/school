Iterator<String> nameIterator = nameList.getIterator();nameIterator.next();nameIterator.remove();nameIterator.next(); nameIterator.next(); nameIterator.remove(); System.out.println(nameIterator.next());displayList(nameList);System.out.println(nameIterator.next());System.out.println(nameIterator.next());