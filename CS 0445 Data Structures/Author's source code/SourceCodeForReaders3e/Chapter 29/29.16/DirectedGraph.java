package GraphPackage;import java.util.Iterator;import ADTPackage.*; // classes that implement various ADTspublic class DirectedGraph<T> implements GraphInterface<T>{   private DictionaryInterface<T, VertexInterface<T>> vertices;   private int edgeCount;   public DirectedGraph()   {      vertices = new LinkedDictionary<T, VertexInterface<T>>();      edgeCount = 0;   } // end default constructor   // < Implementations of the graph operations go here. >   // . . .  } // end DirectedGraph