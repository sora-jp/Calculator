grammar Infix;

eval : expression
	 | assignment
	 | functionDef
	 ;

assignment
	: variable EQUALS expression
	;

functionDef
	: funcWVars EQUALS expression
	;

funcWVars
	: ID LPAREN variable RPAREN
	| ID LPAREN (variable COMMA)+ variable RPAREN
	;
	
expression
    : term
    | expression PLUS term
    | expression MINUS term
    ;

term
    : factor
    | term MULT factor
    | term DIV factor
    | term MOD factor
    ;

factor
    : secondary
    | MINUS factor
    | PLUS  factor
    ;

secondary
	: primary
	| secondary POW factor
	;

primary
    : func
	| histref
	| variable
	| constant
    | '(' expression ')'
    ;
	
variable
	: ID
	;

histref
	: LBRACK INTEGER RBRACK
	;

constant
	: NUMBER
	| INTEGER
	| INUMBER
	| IINTEGER
	;
	
func 
	: ID params
	;

params
	: LPAREN expression RPAREN
	| LPAREN (expression COMMA)+ expression RPAREN
	;


// Tokenizers/Lexers
MULT  : '*' ;
DIV   : '/' ;
MOD   : '%' ;
PLUS  : '+' ;
MINUS : '-' ;
DOT   : '.' ;
POW   : '^' ;
COMMA : ',' ;
EQUALS: '=' ;

LPAREN : '(' ;
RPAREN : ')' ;
LBRACK : '[' ;
RBRACK : ']' ;

INTEGER : [0-9]+ ;
NUMBER  : [0-9]+ '.' [0-9]+ ('e'[0-9]+)?
		| '.' [0-9]+ ('e'[0-9]+)?;

IINTEGER : INTEGER 'i';
INUMBER : NUMBER 'i';

ID : [a-zA-Z] [a-zA-Z0-9]*;

COMMENT : '//' .+? ('\n'|EOF) -> skip ;
WS : [ \t\r\n]+ -> skip ; 