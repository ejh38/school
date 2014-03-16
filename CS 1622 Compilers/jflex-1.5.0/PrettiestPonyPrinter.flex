/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (C) 2014-2014  Zach Sadler <zps6@pitt.edu>                    *
 * All rights reserved.                                                    *
 *                                                                         *
 * License: BSD                                                            *
 *                                                                         *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

%%

%public
%class Zps6PrettiestPrinter
%type void

%unicode

%line
%column

%{

  int SPACES_PER_TABS = 8;

  StringBuilder string = new StringBuilder();
  StringBuilder tabBuilder = new StringBuilder();
  String space = " ";
  int returnState;
  int ifParenBalance;
  int unindentPls = 0;
  int inIf = 0;
  int currentColumn;

  int indentationLevel = 0;
  int unindent = 0;

  private void print(String a) {
    System.out.print(a);
  }

  private String getTabs() {
    tabBuilder.setLength(0);

    for (int i = 0; i < indentationLevel; i++) {
      tabBuilder.append("\t");
    }
    return tabBuilder.toString();
  }

%}

/* main character classes */
LineTerminator = \r|\n|\r\n
InputCharacter = [^\r\n]

WhiteSpace = {LineTerminator} | [ \t\f]

/* comments */
Comment = {TraditionalComment} | {EndOfLineComment} | 
          {DocumentationComment}

TraditionalComment = "/*" [^*] ~"*/" | "/*" "*"+ "/"
EndOfLineComment = "//" {InputCharacter}* {LineTerminator}?
DocumentationComment = "/*" "*"+ [^/*] ~"*/"

/* identifiers */
Identifier = [:jletter:][:jletterdigit:]*
MethodCall = {Identifier} | "." | "this"

/* integer literals */
DecIntegerLiteral = 0 | [1-9][0-9]*


/* these can be printed directly out as they are, nothing fancy */
StraightPrintables = "boolean"      | "break"        | "byte"         | "case"         | "catch"        | "char"         | "class"        | "const"        | "continue"     | "do"           | "double"       | "else"         | "extends"      | "final"        | "finally"      | "float"        | "for"          | "default"      | "implements"   | "import"       | "instanceof"   | "int"          | "interface"    | "long"         | "native"       | "new"          | "goto"         | "if"           | "public"       | "short"        | "super"        | "switch"       | "synchronized" | "package"      | "private"      | "protected"    | "transient"    | "return"       | "void"         | "static"       | "while"        | "this"         | "throw"        | "throws"       | "try"          | "volatile"     | "strictfp"     |   {BinaryOperators}
BinaryOperators = "&&"           |         "<"            | "+"            | "-"            | "*"            | "="            
UnaryOperators = "!" | "-"
ClassSignifier = "class" 
MethodSignifier = "public"

%state EMPTYPARENS, INPARENS, CLASSDECLARATION, METHODDECLARATION, IFTIMEWOOO, BLOCKCOMMENTSBLOW

%%

<YYINITIAL> {

  /* indentation stuff */
  "{"                            {  indentationLevel++; print("{\n" + getTabs()); }
  "}"                            {  indentationLevel--; print("\r" + getTabs() + yytext() + "\n" + getTabs()); }  
  
  /* separators */
  "(" / {WhiteSpace}* ")"        { print("("); yybegin(EMPTYPARENS); }
  "("                            { print("(" + space); ifParenBalance = 1; inIf = 0; yybegin(INPARENS); }
  ")"                            { print(")"); }

  "else" \ {WhiteSpace}* "if"    { print("else" + space); }
  "else" {WhiteSpace}* "{" {WhiteSpace}*     { indentationLevel++; print("else {\n" + getTabs()); }
  "else" {WhiteSpace}*           { indentationLevel++; unindentPls++; print("else\n" + getTabs()); }

  "if" {WhiteSpace}* "("        { print("if" + space + "(" + space); ifParenBalance = 1; inIf = 1; yybegin(INPARENS); }

  "while" {WhiteSpace}* "("     { print("while" + space + "(" + space); ifParenBalance = 1; inIf = 1; yybegin(INPARENS); }



  /* if we see "class" then we need to make sure it's declared on one line */
  {ClassSignifier}              { print(yytext() + space); yybegin(CLASSDECLARATION); }
  {MethodSignifier}             { print(yytext() + space); yybegin(METHODDECLARATION); }

  /* things you can print straight out */
  {StraightPrintables}                         { print(yytext() + space); }

  /* identifiers */
  {Identifier}                   { print(yytext()); }

  /* method calls */
  {Identifier} {MethodCall}*     { print(yytext()); }

  {WhiteSpace}                   { /* do nothing */ }

  //{LineTerminator} {WhiteSpace}* { if (unindentPls > 0 ) { indentationLevel--; unindentPls-- ; } print("\n" + getTabs()); }
  {DecIntegerLiteral}            { print(yytext()); }

  {MethodCall}                  { print(yytext()); }
  

  {Identifier} / {WhiteSpace}* {BinaryOperators} { print(yytext() + space); }
  {DecIntegerLiteral} / {WhiteSpace}* {BinaryOperators} { print(yytext() + space); }
    
  {BinaryOperators}             { print(yytext() + space); }

  /* don't forget this guy */
  ";"                            { if (unindentPls > 0) { indentationLevel--; unindentPls--; } print(";\n" + getTabs()); }

}

<CLASSDECLARATION> {

  {Identifier}                   { print(yytext() + space); }
  {WhiteSpace}*                  { /* do nothing */ }
  "{"                            { indentationLevel++; print("{\n" + getTabs()); yybegin(YYINITIAL); }

}

<METHODDECLARATION> {
  {StraightPrintables}           { print(yytext() + space); }
  "main"                         { print(yytext() + space); }
  "("                            { print("(" + space); }
  {WhiteSpace}*                  { /* do nothing */ }
  {Identifier}                   { print(yytext() + space); }
  ")"                            { print(yytext() + space); }
  "{"                            { indentationLevel++; print("{\n" + getTabs()); yybegin(YYINITIAL); }
  "String" {WhiteSpace}* "[" {WhiteSpace}* "]"        { print("String[] "); }
  "(" / {WhiteSpace}* ")"        { print("("); }
  

}

<EMPTYPARENS> {
  {WhiteSpace}                   { /* do nothing, no whitespace in empty parens */ }
  ")"                            { print(")"); if (returnState == INPARENS) { yybegin(INPARENS); returnState = YYINITIAL; } else { yybegin(YYINITIAL); } }
}

<INPARENS> {
  {LineTerminator}              { /* do nothing */ }
  {WhiteSpace}                  { /* do nothing */ }
  {MethodCall}                  { print(yytext()); }

  {StraightPrintables}          { print(yytext() + space); }

  
  {Identifier} / {WhiteSpace}* {BinaryOperators} { print(yytext() + space); }
  {DecIntegerLiteral} / {WhiteSpace}* {BinaryOperators} { print(yytext() + space); }
  {Identifier} / {WhiteSpace}* ")"    { print(yytext() + space); }
  
 
  ")"                           { print(") "); ifParenBalance--; if (ifParenBalance == 0 && inIf == 1) { inIf = 0; indentationLevel++; print("\n" + getTabs()); unindentPls++; yybegin(YYINITIAL); } else if (ifParenBalance == 0 && inIf == 0) { print("\b"); yybegin(YYINITIAL); } }
  ")" {WhiteSpace}* "{"         { indentationLevel++; print(") {\n" + getTabs()); ifParenBalance = 0; yybegin(YYINITIAL); }

  "("                           { print("( "); ifParenBalance++; }
  "(" / {WhiteSpace}* ")"        { print("("); returnState = INPARENS; yybegin(EMPTYPARENS); }
  
  {BinaryOperators}             { print(yytext()); }
  {DecIntegerLiteral}           { print(yytext() + space); }
  

  /* special case because String[] isn't actually valid MiniJava */
  "String" {WhiteSpace}* "[" {WhiteSpace}* "]"        { print("String[] "); }

}

<BLOCKCOMMENTSBLOW> {

  {LineTerminator}               { print("\n" + getTabs()); currentColumn = indentationLevel*SPACES_PER_TABS; }
  [^*]                           { currentColumn += yytext().length(); if (currentColumn <= 80) { print(yytext()); } else if (currentColumn > 80) { print(yytext().substring(0,80-(currentColumn-yytext().length())) + "\n" + getTabs() + yytext().substring(80-(currentColumn-yytext().length()))); currentColumn = indentationLevel*SPACES_PER_TABS; } }
  "*"+ "/"                       { print("*/"); yybegin(YYINITIAL); }
  {WhiteSpace}* "*"+ "/" {WhiteSpace}* {LineTerminator}*  { print("\n" + getTabs() + "*/\n" + getTabs()); yybegin(YYINITIAL); }

}

  "/*"                           { print("\r"+getTabs()+"/*"); currentColumn = indentationLevel*SPACES_PER_TABS + 2; yybegin(BLOCKCOMMENTSBLOW); }
  
  /* brackets */
  "[" {WhiteSpace}* "]"          { print("[] "); }
  "["                            { print("[ "); }
  "]"                            { print(" ] "); }
  "]" / {WhiteSpace}* ";"          { print(" ]"); }
  
 {UnaryOperators}                { print(yytext()); } 
 ","                           { print("\b" + yytext() + space); }
{EndOfLineComment}             { /* discard line comments as per rule 9 */}
[^]                                   { throw new RuntimeException("Illegal character \""+yytext()+
                                                              "\" at line "+yyline+", column "+yycolumn); }

<<EOF>>                        { throw new RuntimeException("THIS IS NOT AN EXCEPTION\nConsumed EOF and execution ended as expected. Repeat, this is NOT an exception."); }
