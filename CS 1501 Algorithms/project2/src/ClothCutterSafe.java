import java.util.ArrayList;


public class ClothCutterSafe {

	int bestValue;
	int width;
	int height;
	ArrayList<Pattern> patterns;
	ArrayList<Cut> cuts;
	ArrayList<Cut> finalCuts;
	ArrayList<Garment> garments;
	
	// this stores the value of the maximum profit from size [width][height]
	int [][] memos;
	
	public ClothCutterSafe(int width, int height, ArrayList<Pattern> p) {
		this.width = width;
		this.height = height;
		patterns = p;
		// make this one extra row and column so we don't have to talk about 0,0
		memos = new int[width + 1][height + 1];
		
		// initialize the memos to -1 so we can fill with zeroes as needed
		for (int i = 0; i < width + 1; i++) {
			for (int j = 0; j < height + 1; j++) {
				memos[i][j] = -1;
			}
		}
		
		// no NullPointerExceptions over here!
		cuts = new ArrayList<Cut>(10);
		finalCuts = new ArrayList<Cut>(10);
		garments = new ArrayList<Garment>(10);
		
	}
	
	public ArrayList<Cut> cuts() {
		return finalCuts;
	}
	
	public ArrayList<Garment> garments() {
		return garments;
	}
	
	public void finalRun(Cut c, int absx, int absy) {
		if (c == null) {
			return;
		}
		System.out.println("The current cut is " + c);
		System.out.println("With absx, absy: " + absx + ", " + absy);
		
		finalCuts.add(new Cut(c.vertical, c.position, c.x, c.y, absx, absy));
		
		if (c.vertical) {
			finalRun(getCut(c.x - c.position, c.y), absx + c.position, absy);
			finalRun(getCut(c.position, c.y), absx, absy);
		}
		else if (!c.vertical) {
			finalRun(getCut(c.x, c.y - c.position), absx, absy + c.position);
			finalRun(getCut(c.x, c.position), absx, absy);
		}
						
	}
	
	public void optimize() {

		// solve all the subproblems, printing as you go
		for (int i = 1; i < width + 1; i++) {
			for (int j = 1; j < height + 1; j++) {
				memos[i][j] = solveSubproblem(i, j);
				System.out.println("memos[" + i + "][" + j + "] = " + memos[i][j]);
			}
		}
		
		finalRun(cuts.get(cuts.size()-1), 0, 0);
		
		System.out.println("\n\nThe final cuts are:");
		for (Cut c: finalCuts) {
			System.out.println(c);
		}
	}
	
	public Cut getCut(int x, int y) {
		for (Cut c: cuts) {
			if (c.x == x && c.y == y) {
				return c;
			}
		}
		// need something that can talk about Cut or Pattern,
		// then return that
		// or just recognize we're done
		// and stop cutting
		System.out.println("pattern with dim: " + x + " " + y);
		return null;
	}
	
	public int solveSubproblem(int subWidth, int subHeight) {
		
		// we'll use these to determine what to do
		int ans = 0;
		int memoBest = 0;
		int patternBest = -1;
		int horizontalBest = 0;
		int verticalBest = 0;
		
		// initialize a bunch of stuff to null/-1
		Pattern bestPattern = new Pattern(0, 0, -1, "a");
		Cut bestHorizontal = null;
		Cut bestVertical = null;
		
		// first check this value and keep that result
		memoBest = memos[subWidth][subHeight];
		if (memoBest > -1) {
			return memoBest;
		}
		
		// then try to fit each pattern on there and store that result
		for (Pattern p : patterns) {
			if (p.width <= subWidth && p.height <= subHeight && p.value > bestPattern.value) {
				bestPattern = p;
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
				
		// take the max of all those
		ans = Math.max(patternBest, Math.max(horizontalBest, verticalBest));
		// depending which won out, add it to patterns or cuts
		if (bestPattern != null && ans == patternBest) {
			patterns.add(bestPattern);
			System.out.println("Pattern " + bestPattern.toString() + " at " + subWidth + " by " + subHeight);
		}
		else if (bestHorizontal != null && ans == horizontalBest) {
			cuts.add(bestHorizontal);
		}
		else if (bestVertical != null && ans == verticalBest) {
			cuts.add(bestVertical);
		}
		return ans;
	}
	
	public int value() {
		return bestValue;
	}
}
