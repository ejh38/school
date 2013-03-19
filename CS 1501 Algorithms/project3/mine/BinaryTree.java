/*********************
 * CS 1501 Project 3
 * Zach Sadler
 * zps6@pitt.edu
 * 
 * The Binary Tree, which will soon be optimized.
 *********************/

public class BinaryTree {

  public int cost;

  Node root;

  public BinaryTree() {
    // maybe bring in the root and then calculate the cost?
	  cost = 0;
	  root = new Node("null", null, null, 0);
  }

  public String toString() {
	  return root.toString();
  }
}
