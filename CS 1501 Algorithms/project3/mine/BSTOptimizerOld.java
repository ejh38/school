// This guy optimizes the tree! woohoo!

import java.util.ArrayList;
import java.util.Collections;

public class BSTOptimizerOld {

	public boolean MEMOIZE;   // turns memoization on or off
	public int CALLS;         // counts recursive calls
	ArrayList<Node> keys;		// where we store the keys
	ArrayList<BinaryTree> trees;
	
	// memos[i][j] contains the cost of a subtree of the keys
	// Key_i, Key_i+1, ... , Key_j
	BinaryTree memos[][];
	
	public BSTOptimizerOld() {
		// don't think he wants parameters here
		keys = new ArrayList<Node>();
	}

	public void addKey(String key, int frequency) {
		// add the key
		keys.add(new Node(key, null, null, frequency));
	}

	public BinaryTree computeSubtree(int firstIndex, int endIndex, int depth, BinaryTree parent) {
		
		// we have in issue if this happens, because we crossed streams
		if (firstIndex > endIndex) {
			return new BinaryTree();
		}
		
		// if we've solved this before
		if (memos[firstIndex][endIndex].cost != 0) {
			return memos[firstIndex][endIndex];
		}
		
		Node newRoot;
		Node bestRoot = null;
		int min = Integer.MAX_VALUE;
		int cost;
		BinaryTree tempTree;
		BinaryTree bestTree = null;

		for (int i = firstIndex; i <= endIndex; i++) {
			newRoot = keys.get(i);
			tempTree = new BinaryTree();
			tempTree.root = newRoot;
			
			cost =    computeSubtree(firstIndex, i - 1, depth + 1, tempTree).cost 		// the left subtree
					+ newRoot.frequency											// the root
					+ computeSubtree(i + 1, endIndex, depth + 1, tempTree).cost			// the right subtree
					+ sumFrequencies(firstIndex, i - 1)
					+ sumFrequencies(i + 1, endIndex);
			
			tempTree.cost = cost;
			
			CALLS += 2;
			if (cost < min) {
				min = cost;
				bestTree = tempTree;				
			}
		}
		
		
		memos[firstIndex][endIndex] = bestTree;
		return bestTree;
	}
	
	public int sumFrequencies(int first, int last) {
		int sum = 0;
		for (int i = first; i <= last; i++) {
			sum += keys.get(i).frequency;
		}
		return sum;
	}
	
	// returns an optimal BST
	public BinaryTree optimize() {
		memos = new BinaryTree[keys.size()][keys.size()];	// allocate space for the memos
		
		for (int i = 0; i < keys.size(); i++) {
			for (int j = i + 1; j < keys.size(); j++) {
				memos[i][j] = new BinaryTree();
				memos[i][j].cost = 0;
			}
		}		
		
		Collections.sort(keys); // do an initial sort before optimizing
		
		for (int i = 0; i < keys.size(); i++) {
			memos[i][i] = new BinaryTree();
			memos[i][i].cost = keys.get(i).frequency;
			memos[i][i].root = keys.get(i);
		}

		System.out.println(memos[0][keys.size()-1]);
		

		return computeSubtree(0, keys.size() - 1, 1, new BinaryTree());
		

	
		
	//	return memos[0][keys.size()];
	}
}
