/*********************
 * CS 1501 Project 3
 * Zach Sadler
 * zps6@pitt.edu
 * 
 * Node for our BinaryTree. Pretty simple.
 *********************/
public class Node implements Comparable<Node> {

  Node leftChild;
  Node rightChild;

  String key;
  int frequency;
  int depth;

  public Node(String key, Node leftChild, Node rightChild, int frequency) {
    this.leftChild = leftChild;
    this.rightChild = rightChild;
    this.key = key;
    this.frequency = frequency;
  }

  // piggyback off of String being comparable
  public int compareTo(Node other) {
    return this.key.compareTo(other.key);
  }
  
  // Wheeee! Recursion is fun!
  public String toString() {
	  if (this.key == "null")
		  return "null ";
	  
	  String ans = "(" + this.key + " ";
	  if (leftChild != null) 
		  ans += leftChild.toString();
	  else
		  ans += "null ";
	  
	  if (rightChild != null) 
		  ans += rightChild.toString();
	  else
		  ans += "null ";
	  
	  ans += ")";
	  return ans;
  }

}
