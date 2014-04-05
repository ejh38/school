public class Token {
	
	public Object content;
	public int line, column;
	
	public Token(int a, int b) {
		line = a;
		column = b;
	}

	public Token(int a, int b, Object c) {
		line = a;
		column = b;
		content = c;
	}
}