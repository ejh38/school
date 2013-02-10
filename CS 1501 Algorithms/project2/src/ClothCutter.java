import java.util.ArrayList;


public class ClothCutter {

	int bestValue;
	int width;
	int height;
	ArrayList<Pattern> patterns;
	ArrayList<Cut> cuts;
	ArrayList<Garment> garments;
	
	Garment [][] memos;
	
	
	public ClothCutter(int width, int height, ArrayList<Pattern> p) {
		this.width = width;
		this.height = height;
		patterns = p;
		// make this one extra row and column so we don't have to talk about 0,0
		memos = new Garment[width + 1][height + 1];
		
		for (int i = 0; i < width + 1; i++) {
			for (int j = 0; j < height + 1; j++) {
				memos[i][j] = new Garment(0, 0, "a", -1);
			}
		}
		
		cuts = new ArrayList<Cut>(10);
		garments = new ArrayList<Garment>(10);
	}
	
	public ArrayList<Cut> cuts() {
		return cuts;
	}
	
	public ArrayList<Garment> garments() {
		return garments;
	}
	
	public void optimize() {
		// do everything!
		// set best value
		
		for (int i = 1; i < width + 1; i++) {
			for (int j = 1; j < height + 1; j++) {
				memos[i][j] = solveSubproblem(i, j);
				System.out.println("memos[" + i + "][" + j + "] = " + memos[i][j]);
			}
		}
		
		System.out.println("The patterns I got are: ");
		
		for (Pattern p: patterns) {
			System.out.println(p);
		}
		
		System.out.println("The cuts I got are: ");
		
		for (Cut c: cuts) {
			System.out.println(c);
		}
	}
	
	public Garment solveSubproblem(int subWidth, int subHeight) {
		int ans = 0;
		Garment memoBest = new Garment(0, 0, "fail", -1);
		int patternBest = -1;
		int horizontalBest = 0;
		int verticalBest = 0;
		
		Pattern bestPattern = new Pattern(0, 0, -1, "a");
		Cut bestHorizontal = null;
		Cut bestVertical = null;
		
		Garment returnValue = new Garment(0, 0, "fail", -1);
		
		// first check this value and keep that result
		memoBest = memos[subWidth][subHeight];
		if (memoBest.value > -1) {
			return memoBest;
		}
		
		// then try to fit each pattern on there and store that result
		for (Pattern p : patterns) {
			if (p.width <= subWidth && p.height <= subHeight && p.value > bestPattern.value) {
				bestPattern = p;
				patternBest = p.value;
				returnValue = new Garment(subWidth, subHeight, bestPattern.name, p.value);
			}
		}	
		
		// then do all the horizontal cuts and get the max of those
		for (int i = 1; i < subHeight; i++) {
			int temp = solveSubproblem(subWidth, i).value + solveSubproblem(subWidth, subHeight - i).value;
			if (temp > horizontalBest) {
				bestHorizontal = new Cut(false, i);
				horizontalBest = temp;
			}
		}
		
		// then do all the vertical cuts and get the max of those
		for (int i = 1; i < subWidth; i++) {
			int temp = solveSubproblem(i, subHeight).value + solveSubproblem(subWidth - i, subHeight).value;
			if (temp > verticalBest) {
				bestVertical = new Cut(true, i);
				verticalBest = temp;
			}
		}
				
		// take the max of all those
		ans = Math.max(patternBest, Math.max(horizontalBest, verticalBest));
				
		if (bestPattern != null && ans == patternBest) {
			patterns.add(bestPattern);
		}
		else if (bestHorizontal != null && ans == horizontalBest) {
			cuts.add(bestHorizontal);
		}
		else if (bestVertical != null && ans == verticalBest) {
			cuts.add(bestVertical);
		}
		
		return returnValue;
	}
	
	public int value() {
		return bestValue;
	}
}
