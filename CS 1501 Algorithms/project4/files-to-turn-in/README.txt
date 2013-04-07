Approximately Solve Euclidean TSP with MST-Walk
Zach Sadler
April 7, 2013

CONTENTS

Implements MST-Walk algorithm to find approximate solution to
Euclidean TSP.  The following files should be present:

  City.java
  Edge.java
  EuclideanTSP.java
  Map.java
  DemonstrateEuclideanTSP.java

USAGE

Compile and run with Java 1.5 or later:

  javac DemonstrateEuclideanTSP.java
  java DemonstrateEuclideanTSP NUMBER_OF_CITIES

This will generate random NUMBER_OF_CITIES cities, find and display
the MST, then find and display the MST-Walk tour.

********* 
Controls are listed on the terminal: You can press '1', '2', or '3' to toggle displaying the Vertices, MST, and MST-walk respectively.

PROBLEMS

Rounding of floating-point coordinates of cities can introduce errors
with small maps or very close cities.

