public boolean connect(VertexInterface<T> endVertex, double edgeWeight) {   boolean result = false;   if (!this.equals(endVertex))   { // vertices are distinct      Iterator<VertexInterface<T>> neighbors = this.getNeighborIterator();      boolean duplicateEdge = false;      while (!duplicateEdge && neighbors.hasNext())      {         VertexInterface<T> nextNeighbor = neighbors.next();         if (endVertex.equals(nextNeighbor))            duplicateEdge = true;      } // end while      if (!duplicateEdge)      {         edgeList.add(new Edge(endVertex, edgeWeight));         result = true;      } // end if   } // end if   return result;} // end connectpublic boolean connect(VertexInterface<T> endVertex) {   return connect(endVertex, 0);} // end connect