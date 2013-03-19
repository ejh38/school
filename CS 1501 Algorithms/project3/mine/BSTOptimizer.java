/*********************
 * CS 1501 Project 3
 * Zach Sadler
 * zps6@pitt.edu
 * 
 * This class does the actual algorithm part of the project.
 * Pretty well commented- just dive in!
 *********************/

import java.util.ArrayList;
import java.util.Collections;

public class BSTOptimizer {

	public boolean MEMOIZE;   	// trust me, you want this turned on
	public int CALLS;         	// counts recursive calls
	ArrayList<Node> keys = new ArrayList<Node>();
	
	// memos[i][j] contains the optimal subtrees for keys
	// {Key_i, Key_i+1, ... , Key_j}
	BinaryTree memos[][];
	
	public BSTOptimizer() {
		// do nothing. don't do anything. just stop it.
	}

	// set those children to null by default
	public void addKey(String key, int frequency) {
		keys.add(new Node(key, null, null, frequency));
	}

	public BinaryTree computeSubtree(int firstIndex, int endIndex, int depth) {
		if (firstIndex > endIndex) {
			return new BinaryTree();		// don't go crossing streams! get outta there!
		}
	
		// if we're doing memos, then check the memo!
		if (MEMOIZE) {
			if (memos[firstIndex][endIndex].cost != 0) {
				return memos[firstIndex][endIndex];
			}
		}
			
		// initialize some bookkeeping stuff
		Node newRoot = null;
		Node bestRoot = null;
		BinaryTree bestLeft = null;
		BinaryTree bestRight = null;
		
		int min = Integer.MAX_VALUE;	// initalize this to huge
		int cost;						// and this to tiny
	
		// let's try each guy as the root!
		for (int i = firstIndex; i <= endIndex; i++) {
			newRoot = cloneNode(i);		// basically just keys.get(i)
			
			// grab those subtrees based around this root
			BinaryTree leftSubtree = computeSubtree(firstIndex, i - 1, depth + 1);
			BinaryTree rightSubtree = computeSubtree(i + 1, endIndex, depth + 1);
			CALLS += 2;		// so we can print out big numbers
			
			cost =    leftSubtree.cost 						// our recursive left answer
					+ rightSubtree.cost						// and recursive right
					+ newRoot.frequency						// add the root's frequency
					+ sumFrequencies(firstIndex, i - 1)		// and all the frequencies
					+ sumFrequencies(i + 1, endIndex);		// of keys below it
			
			if (cost < min) {
				min = cost;					// ho man, we got a new min
				bestRoot = newRoot;			// store this for later
				bestLeft = leftSubtree;		// if it turns out to be
				bestRight = rightSubtree;	// the very best!
			}
		}
		
		// now we have our true bests
		BinaryTree ans = new BinaryTree();
		ans.root = bestRoot;					// hook up the bestRoot
		ans.cost = min;							// that cost we found
		ans.root.leftChild = bestLeft.root;		// and the children
		ans.root.rightChild = bestRight.root;	// yeaaahhhh!!!!

		// set the memo
		memos[firstIndex][endIndex] = ans;

		return ans;		// get outta here
	}
	
	// this wrapper is really for my peace of mind, and a potential bug
	public Node cloneNode(int i) {
		return new Node(keys.get(i).key, null, null, keys.get(i).frequency);
	}
	
	// doesn't get much easier than this
	public int sumFrequencies(int first, int last) {
		int sum = 0;
		for (int i = first; i <= last; i++) {
			sum += keys.get(i).frequency;
		}
		return sum;
	}
	
	// get the answer!
	public BinaryTree optimize() {
		Collections.sort(keys); 							// do an initial sort beforehand
		
		// set up the memos (the ones we'll use, that is)
		memos = new BinaryTree[keys.size()][keys.size()];	// allocate space 
		for (int i = 0; i < keys.size(); i++) {
			for (int j = i; j < keys.size(); j++) {
				memos[i][j] = new BinaryTree();				// no nullpointers here
			}
		}
		
		// setup the diagonal ahead of time
		for (int i = 0; i < keys.size(); i++) {
			memos[i][i].cost = keys.get(i).frequency;
			memos[i][i].root = cloneNode(i); 
		}
		
		// this guy right here does ALLLLLL the work
		computeSubtree(0, keys.size() - 1, 1);
		CALLS++;								// no off by one errors here
			 
		return memos[0][keys.size() - 1];		// that's our answer
	}
}
