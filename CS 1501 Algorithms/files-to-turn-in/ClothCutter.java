/********************************
 * Zach Sadler
 * zps6@pitt.edu
 * Project 2
 * Cloth Cutting & Dynamic Programming
 ********************************/

import java.util.ArrayList;

public class ClothCutter {

	int width;		// for the cloth
	int height;		// for the cloth
	
	ArrayList<Pattern> patterns;	// stores the Patterns we have to work with
	ArrayList<Cut> allCuts;			// stores all the Cuts performed
	ArrayList<Cut> finalCuts;		// stores the correct sequence of Cuts from 'allCuts'
	ArrayList<Garment> garments;	// stores the Garments we use along the way
	
	// stores the value of the maximum profit from size [width][height]
	int [][] memos;
	
	public ClothCutter(int width, int height, ArrayList<Pattern> p) {
		// copy in values
		this.width = width;
		this.height = height;
		patterns = p;
		
		// make this one extra row and column so we don't have to talk about 0,0
		memos = new int[width + 1][height + 1];
		
		// initialize the memos to -1 so we can differentiate between
		// not yet solved-for (-1) and no value (0)
		for (int i = 0; i < width + 1; i++) {
			for (int j = 0; j < height + 1; j++) {
				memos[i][j] = -1;
			}
		}
		
		// no NullPointerExceptions over here!
		allCuts = new ArrayList<Cut>();
		finalCuts = new ArrayList<Cut>();
		garments = new ArrayList<Garment>();
	}
	
	// the correct sequence of cuts to maximize value
	public ArrayList<Cut> cuts() {
		return finalCuts;		
	}
	
	// the garments yielded from the cloth
	public ArrayList<Garment> garments() {
		return garments;
	}
	
	// this is the amount we can make from the cloth
	public int value() {
		return memos[width][height];
	}
	
	// takes in the size (x, y) and absolute offset of a pattern
	// then turns it into a garment and adds it to the ArrayList
	public void addGarment(int x, int y, int absx, int absy) {
		int value = -1;
		Garment toAdd = null;
		
		for (Pattern p: patterns) {
			if (p.width == x && p.height == y && p.value > value) {
				value = p.value;	// if multiple Patterns are the same dimensions, 
									// we'll get the one with the highest value
				toAdd = new Garment(absx, absy, p.name); 
				toAdd.setDimensions(x, y);
			}
		}
		
		garments.add(toAdd);
	}
	
	// this function is done after filling in the memo grid
	// it is called from the first cut to be made
	// on the size [width, height] cloth and then
	// calculates the rest of the cuts that need to be made
	// along with their local origin/absolute offset
	public void finalRun(Cut c, int absx, int absy) {
		
		if (c.position == -1) {
			addGarment(c.x, c.y, absx, absy);
			return;
		}
	
		// add to the sequence of cuts the one that got passed in
		finalCuts.add(new Cut(c.vertical, c.position, c.x, c.y, absx, absy));
		
		// then recurse on the two resulting parts
		if (c.vertical) {
			finalRun(getCut(c.x - c.position, c.y), absx + c.position, absy);
			finalRun(getCut(c.position, c.y), absx, absy);
		}
		else if (!c.vertical) {
			finalRun(getCut(c.x, c.y - c.position), absx, absy + c.position);
			finalRun(getCut(c.x, c.position), absx, absy);
		}
						
	}
	
	
	// this creates all the memos, then calls
	// finalRun for a single top->down pass through
	public void optimize() {

		// solve all the subproblems, printing as you go
		for (int i = 1; i < width + 1; i++) {		// don't forget we made the array
			for (int j = 1; j < height + 1; j++) {	// one bigger than width and height
				memos[i][j] = solveSubproblem(i, j);
			}
		}
		
		// start finalRun off with an absolute offset of 0,0
		// and the last cut that we made/first one we will make
		if (allCuts.size() > 0) {
			finalRun(allCuts.get(allCuts.size()-1), 0, 0);		
		}
		else {		// this is the case where we have no patterns that fit
			System.out.println("Something's screwy; there are no patterns that"
							+ " can fit on the given size cloth. Try again with better input.");
		}
	}
	
	// this method searches through the ArrayList of Cuts
	// and returns the correct one for the given size
	// basically an alternative to using Cuts as Memos
	public Cut getCut(int x, int y) {
		for (Cut c: allCuts) {
			if (c.x == x && c.y == y) {
				return c;		// c is unique- no worries there
			}
		}
	
		// if we didn't find a cut with those dimensions then we have
		// a flag to make a garment with these dimensions
		return new Cut(true, -1, x, y, -1, -1);
	}
	
	public int solveSubproblem(int subWidth, int subHeight) {
		
		// right off the bat, check against the memos
		// if we have a non-flagged answer, then we're done
		int memoBest = memos[subWidth][subHeight];
		if (memoBest > -1) {
			return memoBest;
		}
		
		// set up a bunch of placeholder values
		// to compare against as we loop through the lists
		int ans = 0;
		int patternBest = 0;
		int horizontalBest = 0;
		int verticalBest = 0;
		
		// set up placeholders for Cuts as well
		Cut bestHorizontal = null;
		Cut bestVertical = null;
		
		// try to fit each pattern on there and store that result
		for (Pattern p : patterns) {
			if (p.width <= subWidth && p.height <= subHeight && p.value > patternBest) {
				patternBest = p.value;
			}
		}	
		
		// then do all the horizontal cuts and get the max of those
		for (int i = 1; i < subHeight; i++) {
			int temp = solveSubproblem(subWidth, i) + solveSubproblem(subWidth, subHeight - i);
			if (temp > horizontalBest) {
				bestHorizontal = new Cut(false, i, subWidth, subHeight, 0, 0);
				horizontalBest = temp;
			}
		}
		
		// then do all the vertical cuts and get the max of those
		for (int i = 1; i < subWidth; i++) {
			int temp = solveSubproblem(i, subHeight) + solveSubproblem(subWidth - i, subHeight);
			if (temp > verticalBest) {
				bestVertical = new Cut(true, i, subWidth, subHeight, 0, 0);
				verticalBest = temp;
			}
		}
				
		// take the max of the three choices
		ans = Math.max(patternBest, Math.max(horizontalBest, verticalBest));
		
		// depending which won out add the correct Cut to allCuts
		if (bestHorizontal != null && ans == horizontalBest) {
			allCuts.add(bestHorizontal);
		}
		else if (bestVertical != null && ans == verticalBest) {
			allCuts.add(bestVertical);
		}
		return ans;
	}
	
}
