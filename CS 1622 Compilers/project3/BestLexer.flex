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
%} 

int = 0 | -?[1-9][0-9]*

new_line = \r|\n|\r\n|\z
white_space = {new_line} | [ \t\f]
identifier = [_a-zA-Z][_a-zA-Z0-9]*

%%

/* MiniJava Terminals! */

"("		 		{ return new Symbol(LPAREN, yyline+1, yycolumn+1); }
")"		 		{ return new Symbol(RPAREN, yyline+1, yycolumn+1); }
"!"				{ return new Symbol(NOT, yyline+1, yycolumn+1); }
"new"			{ return new Symbol(NEW, yyline+1, yycolumn+3); }
"int"			{ return new Symbol(INT, yyline+1, yycolumn+3); }
"this"			{ return new Symbol(THIS, yyline+1, yycolumn+4); }
"true"			{ return new Symbol(TRUE, yyline+1, yycolumn+4); }
"false"			{ return new Symbol(FALSE, yyline+1, yycolumn+5); }
"length"			{ return new Symbol(LENGTH, yyline+1, yycolumn+6); }
"extends"			{ return new Symbol(EXTENDS, yyline+1, yycolumn+7); }
"["				{ return new Symbol(LBRACKET, yyline+1, yycolumn+1); }
"]"				{ return new Symbol(RBRACKET, yyline+1, yycolumn+1); }
","			 	{ return new Symbol(COMMA, yyline+1, yycolumn+1); }
{int}			{return new Symbol(INTLITERAL, yyline+1, yycolumn+1, new Integer(Integer.parseInt(yytext())));}
"&&"			{ return new Symbol(AND, yyline+1, yycolumn+2); }
"<"			 	{ return new Symbol(LESSTHAN, yyline+1, yycolumn+1); }
"."			 	{ return new Symbol(DOT, yyline+1, yycolumn+1); }
"+"			 	{ return new Symbol(PLUS, yyline+1, yycolumn+1); }
"-"			 	{ return new Symbol(MINUS, yyline+1, yycolumn+1); }
"*"			 	{ return new Symbol(TIMES, yyline+1, yycolumn+1); }
"="			 	{ return new Symbol(EQUALS, yyline+1, yycolumn+1); }
";"			 	{ return new Symbol(SEMICOLON, yyline+1, yycolumn+1); }
"System.out.println"    { return new Symbol(PRINTLN, yyline+1, yycolumn+18); }
"while"			{ return new Symbol(WHILE, yyline+1, yycolumn+5); }
"if"			{ return new Symbol(IF, yyline+1, yycolumn+2); }
"{"			 	{ return new Symbol(LBRACE, yyline+1, yycolumn+1); }
"}"			 	{ return new Symbol(RBRACE, yyline+1, yycolumn+1); }
"boolean"		{ return new Symbol(BOOLEAN, yyline+1, yycolumn+7); }
"public"	 	{ return new Symbol(PUBLIC, yyline+1, yycolumn+6); }
"return"	 	{ return new Symbol(RETURN, yyline+1, yycolumn+6); }
"static"	 	{ return new Symbol(STATIC, yyline+1, yycolumn+6); }
"void"	 		{ return new Symbol(VOID, yyline+1, yycolumn+4); }
"main"	 		{ return new Symbol(MAIN, yyline+1, yycolumn+4); }
"String"	 	{ return new Symbol(STRING, yyline+1, yycolumn+6); }
{identifier}	{ return new Symbol(IDENTIFIER, yyline+1, yycolumn+yytext().length, yytext()); }


".text"	 { /* do nothing */ }

{new_line} { /*ignore! */ }

{white_space}	{ /* ignore */ }

/* error fallback */
"[^]"	{ error("Illegal character <"+ yytext()+">"); }
