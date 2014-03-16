Zach Sadler
zps6@pitt.edu
Project 1
CS 1622

BUILD AND RUN INSTRUCTIONS:
jflex Zps6PrettiestPrinter.flex
javac Driver.java
javac Zps6PrettiestPrinter.java
java Driver INPUT_FILE_HERE


'IMPOSSIBLE' NOTES:
So I may be way off-base and just not doing a good enough job testing my program, but I think I nailed it. There is only one thing I didn't successfully complete, which is to handle a structure like:

	if (a < b)
		if (1 < 3) {
			multiple();
			statements();
			here();
		}
	// then back to perfect indentation here.

My program is unable to handle this sort of thing because I'd have to do an entire 'lookahead' of the full if (1 < 3) { } statement, which encompasses multiple lines, all the while keeping track of the fact that I need to unindent after the multi-line statement is over so that I can match the indentation that belongs with the if statement from before.

It's hard to explain but easy to see. Perhaps with a lot of hacked in java code I could accomplish it, but I was happy enough getting nested ifs, block comments, and all the other rules successfully handled.
