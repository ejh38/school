/* Zach Sadler
 * zps6@pitt.edu
 * Project 5
 * 
 * Simple program that finds a Longest Common Subsequence 
 * between two strings in a quick amount of time.
 */


public class LCS {

	static int [][] memos;			// the lcs length up to the i,j position of s1,s2
	static String s1, s2;			// the strings we look through
	static int length1, length2;	// the lengths of s1 and s2

	// this stacks all the memos
	public static String findLCS(String s11, String s22) {
		
		// first make the larger string s1
		if (s11.length() >= s22.length()) {
			s1 = s11;
			s2 = s22;
		}
		else {
			s1 = s22;
			s2 = s11;
		}
		// now s1 and s2 are correctly set, so get the lengths
		length1 = s1.length();
		length2 = s2.length();
		
		// and make the memo with the correct size
		memos = new int[length1 + 1][length2 + 1];
		
		// set up the first row and first column with 0's
		for (int i = 0; i < length1; i++) {
			memos[i][0] = 0;
		}
		for (int i = 0; i < length2; i++) {
			memos[0][i] = 0;
		}
		
		// double for loop through the two strings
		for (int i = 1; i <= length1; i++) {
			for (int j = 1; j <= length2; j++) {
				// if we get a matching character, then set the memo appropriately
				if (s1.charAt(i-1) == s2.charAt(j-1)) {
					memos[i][j] = memos[i-1][j-1] + 1;
				}
				else {
					// otherwise fill in with the max of the previous ones
					// above and to the left of the current one
					memos[i][j] = (memos[i][j-1] > memos[i-1][j]) ? memos[i][j-1] : memos[i-1][j];
				}
			}
		}
		
		// now the memos are completely set, so just do a single
		// trace through the 2d array to get an answer
		return getAnswer(length1, length2);
	}
	
	// this backtracks through the memo starting from the end and figures
	// out which characters are the ones that matter
	public static String getAnswer(int i, int j) {	
		// base case; return the empty string
		if (i == 0 || j == 0) {
			return "";
		}
		// if we have a match here, then keep recursing
		// and return the character that gives the match
		else if (s1.charAt(i-1) == s2.charAt(j-1)) {
			return getAnswer(i-1, j-1) + s1.charAt(i-1);
		}
		// if no match, then determine whether to go left or up
		else {
			if (memos[i][j-1] > memos[i-1][j])
				return getAnswer(i, j-1);
			else
				return getAnswer(i-1, j);
		}
	}
	
}
