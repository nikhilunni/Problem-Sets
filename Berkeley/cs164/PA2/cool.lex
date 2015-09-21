/*
 * CS164: Spring 2004
 * Programming Assignment 2
 *
 * The scanner definition for Cool.
 *
 */

import java_cup.runtime.Symbol;

%%

/* Code enclosed in %{ %} is copied verbatim to the lexer class definition.
 * All extra variables/methods you want to use in the lexer actions go
 * here.  Don't remove anything that was here initially.  */
%{
    // Max size of string constants
    static int MAX_STR_CONST = 1024;

    // For assembling string constants
    StringBuffer string_buf = new StringBuffer();

    // For line numbers
    private int curr_lineno = 1;
    int get_curr_lineno() {
	return curr_lineno;
    }

    private AbstractSymbol filename;

    void set_filename(String fname) {
	filename = AbstractTable.stringtable.addString(fname);
    }

    AbstractSymbol curr_filename() {
	return filename;
    }

    /*
     * Add extra field and methods here.
     */
    StringBuffer str;
%}


/*  Code enclosed in %init{ %init} is copied verbatim to the lexer
 *  class constructor, all the extra initialization you want to do should
 *  go here. */
%init{
    str = new StringBuffer();
%init}

/*  Code enclosed in %eofval{ %eofval} specifies java code that is
 *  executed when end-of-file is reached.  If you use multiple lexical
 *  states and want to do something special if an EOF is encountered in
 *  one of those states, place your code in the switch statement.
 *  Ultimately, you should return the EOF symbol, or your lexer won't
 *  work. */
%eofval{
    switch(yystate()) {
    case YYINITIAL:
	/* nothing special to do in the initial state */
	break;
    case MULTI_COMMENT:
        yybegin(EOF);
        return new Symbol(TokenConstants.ERROR,
                          AbstractTable.stringtable.addString("EOF in comment"));
    case EOF:
        return new Symbol(TokenConstants.EOF);
    }
   return new Symbol(TokenConstants.EOF);
%eofval}

/* Do not modify the following two jlex directives */
%class CoolLexer
%cup


/* This defines a new start condition for line comments.
 * .
 * Hint: You might need additional start conditions. */
%xstate MULTI_COMMENT 
%xstate STRING
%xstate EOF


/* Define lexical rules after the %% separator.  There is some code
 * provided for you that you may wish to use, but you may change it
 * if you like.
 * .
 * Some things you must fill-in (not necessarily a complete list):
 *   + Handle (* *) comments.  These comments should be properly nested.
 *   + Some additional multiple-character operators may be needed.  One
 *     (DARROW) is provided for you.
 *   + Handle strings.  String constants adhere to C syntax and may
 *     contain escape sequences: \c is accepted for all characters c
 *     (except for \n \t \b \f) in which case the result is c.
 * .
 * The complete Cool lexical specification is given in the Cool
 * Reference Manual (CoolAid).  Please be sure to look there. */
%%
[\n]+	                 { curr_lineno += yytext().length(); }
[ ]+                     { /* Fill-in here. */ }
\"                       { str.setLength(0); //Reset StringBuffer
                           yybegin(STRING); 
                         }
<STRING> {
    \"                   { yybegin(YYINITIAL);
                           for(int my_i = 0; my_i < str.length(); my_i++) {
                               if((int)(str.charAt(my_i)) <= 0)
                                   return new Symbol(TokenConstants.ERROR,
                                                     AbstractTable.stringtable.addString("String contains null character"));
                           }
                         return new Symbol(TokenConstants.STR_CONST, 
                                           AbstractTable.stringtable.addString(str.toString()));
                         }
   \\b                   { str.append((char)8 ); }
   \\t                   { str.append((char)9 ); }
   \\n                   { str.append((char)10); }
   \\f                   { str.append((char)12); }
   [\\][^]               { str.append(yytext().charAt(1)); 
                           if(yytext().charAt(1) == '\n')
                               curr_lineno++;
                         }
                                   
   [^\n\f\r\t\v\"\\]+    { str.append(yytext()); }
   \n                    { curr_lineno++; //CHECK ME LATER
                           yybegin(YYINITIAL);
                           return new Symbol(TokenConstants.ERROR,
                                             AbstractTable.stringtable.addString("Unterminated string constant"));
                         }
} 

/* dash dash followed by nonnewline characters (maybe) followed by a newline character */
--[^\r\n]*[\r|\n|\r\n]? {
  char last = yytext().charAt(yytext().length()-1);
  if(last == '\r' || last == '\n')
      curr_lineno++;
}

"(*"                    { yybegin(MULTI_COMMENT); }
<MULTI_COMMENT> {
   \n                   { curr_lineno++; }
   "*)"                 { yybegin(YYINITIAL); }
   [^]                  {}

}



"*)"         { return new Symbol(TokenConstants.ERROR,
                                            AbstractTable.stringtable.addString("Unmatched *)")); }
"=>"		{ return new Symbol(TokenConstants.DARROW); }
[0-9][0-9]*  { /* Integers */
                          return new Symbol(TokenConstants.INT_CONST,
					    AbstractTable.inttable.addString(yytext())); }


[Cc][Ll][Aa][Ss][Ss] { return new Symbol(TokenConstants.CLASS); }
[Ii][Nn][Hh][Ee][Rr][Ii][Tt][Ss] { return new Symbol(TokenConstants.INHERITS); }
[Cc][Aa][Ss][Ee]	{ return new Symbol(TokenConstants.CASE); }
[Ee][Ll][Ss][Ee]  	{ return new Symbol(TokenConstants.ELSE); }
[Ee][Ss][Aa][Cc]	{ return new Symbol(TokenConstants.ESAC); }
f[Aa][Ll][Ss][Ee]	{ return new Symbol(TokenConstants.BOOL_CONST, Boolean.FALSE); }
[Ff][Ii]             { return new Symbol(TokenConstants.FI); }
[Ii][Ff]  		{ return new Symbol(TokenConstants.IF); }
[Ii][Nn]             { return new Symbol(TokenConstants.IN); }
[Ii][Nn][Hh][Ee][Rr][Ii][Tt][Ss] { return new Symbol(TokenConstants.INHERITS); }
[Ii][Ss][Vv][Oo][Ii][Dd] { return new Symbol(TokenConstants.ISVOID); }
[Ll][Ee][Tt]         { return new Symbol(TokenConstants.LET); }
[Ll][Oo][Oo][Pp]  	{ return new Symbol(TokenConstants.LOOP); }
[Nn][Ee][Ww]		{ return new Symbol(TokenConstants.NEW); }
[Nn][Oo][Tt] 	{ return new Symbol(TokenConstants.NOT); }
[Oo][Ff]		{ return new Symbol(TokenConstants.OF); }
[Pp][Oo][Oo][Ll]  	{ return new Symbol(TokenConstants.POOL); }
[Tt][Hh][Ee][Nn]   	{ return new Symbol(TokenConstants.THEN); }
t[Rr][Uu][Ee]	{ return new Symbol(TokenConstants.BOOL_CONST, Boolean.TRUE); }
[Ww][Hh][Ii][Ll][Ee] { return new Symbol(TokenConstants.WHILE); }

[A-Z][a-zA-Z0-9_]* { return new Symbol(TokenConstants.TYPEID,
                                      AbstractTable.stringtable.addString(yytext())); }
[a-z][a-zA-Z0-9_]* { return new Symbol(TokenConstants.OBJECTID,
                                      AbstractTable.stringtable.addString(yytext())); }


"<-"                    { return new Symbol(TokenConstants.ASSIGN); }
"+"			{ return new Symbol(TokenConstants.PLUS); }
"/"			{ return new Symbol(TokenConstants.DIV); }
"-"			{ return new Symbol(TokenConstants.MINUS); }
"*"			{ return new Symbol(TokenConstants.MULT); }
"="			{ return new Symbol(TokenConstants.EQ); }
"<"			{ return new Symbol(TokenConstants.LT); }
"."			{ return new Symbol(TokenConstants.DOT); }
"~"			{ return new Symbol(TokenConstants.NEG); }
","			{ return new Symbol(TokenConstants.COMMA); }
";"			{ return new Symbol(TokenConstants.SEMI); }
":"			{ return new Symbol(TokenConstants.COLON); }
"("			{ return new Symbol(TokenConstants.LPAREN); }
")"			{ return new Symbol(TokenConstants.RPAREN); }
"@"			{ return new Symbol(TokenConstants.AT); }
"}"			{ return new Symbol(TokenConstants.RBRACE); }
"{"			{ return new Symbol(TokenConstants.LBRACE); }

[\x00-\x1F]             { } 
.                       { return new Symbol(TokenConstants.ERROR,
                                            AbstractTable.stringtable.addString(yytext())); }
