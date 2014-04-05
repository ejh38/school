import java_cup.runtime.Symbol;

%%

%class BestLexer
%cup
%implements sym
%line
%column
%ignorecase
%eofclose

%{
  private void error(String message) {
    System.err.println("Error at line "+(yyline+1)+", column "+(yycolumn+1)+" : "+message);
  }

  public Symbol tokenize(int sym) {
  	return new Symbol(sym, new Token(yyline+1, yycolumn+1));
  }

  public Symbol tokenize(int sym, Object contents) {
  	return new Symbol(sym, new Token(yyline+1, yycolumn+1, contents));
  }
%} 

int = 0 | [1-9][0-9]*

new_line = \r|\n|\r\n|\z
white_space = {new_line} | [ \t\f]
identifier = [_a-zA-Z][_a-zA-Z0-9]*

/* comments */
comment = {TraditionalComment} | {EndOfLineComment} | 
          {DocumentationComment}
InputCharacter = [^\r\n]

TraditionalComment = "/*" [^*] ~"*/" | "/*" "*"+ "/"
EndOfLineComment = "//" {InputCharacter}* {new_line}?
DocumentationComment = "/*" "*"+ [^/*] ~"*/"

%%

/* MiniJava Terminals! */

"System.out.println"    { return tokenize(PRINTLN); }
"("		 		{ return tokenize(LPAREN); }
")"		 		{ return tokenize(RPAREN); }
"!"				{ return tokenize(NOT); }
"new"			{ return tokenize(NEW); }
"int"			{ return tokenize(INT); }
"this"			{ return tokenize(THIS); }
"true"			{ return tokenize(TRUE); }
"false"			{ return tokenize(FALSE); }
"length"			{ return tokenize(LENGTH); }
"extends"			{ return tokenize(EXTENDS); }
"["				{ return tokenize(LBRACKET); }
"]"				{ return tokenize(RBRACKET); }
","			 	{ return tokenize(COMMA); }
"&&"			{ return tokenize(AND); }
"<"			 	{ return tokenize(LESSTHAN); }
"."			 	{ return tokenize(DOT); }
"+"			 	{ return tokenize(PLUS); }
"-"			 	{ return tokenize(MINUS); }
"*"			 	{ return tokenize(TIMES); }
"="			 	{ return tokenize(EQUALS); }
";"			 	{ return tokenize(SEMICOLON); }
"while"			{ return tokenize(WHILE); }
"if"			{ return tokenize(IF); }
"{"			 	{ return tokenize(LBRACE); }
"}"			 	{ return tokenize(RBRACE); }
"boolean"		{ return tokenize(BOOLEAN); }
"public"	 	{ return tokenize(PUBLIC); }
"return"	 	{ return tokenize(RETURN); }
"static"	 	{ return tokenize(STATIC); }
"void"	 		{ return tokenize(VOID); }
"main"	 		{ return tokenize(MAIN); }
"String"	 	{ return tokenize(STRING); }
"class"			{ return tokenize(CLASS); }
"else"			{ return tokenize(ELSE); }

{identifier}	{ return tokenize(IDENTIFIER, yytext()); }
{int}			{ return tokenize(INTLITERAL, new Integer(Integer.parseInt(yytext()))); }

{comment}		{ /* ignore! */ }

{new_line} { /*ignore! */ }

{white_space}	{ /* ignore */ }



/* error fallback */
"[^]"	{ error("Illegal character <"+ yytext()+">"); }
