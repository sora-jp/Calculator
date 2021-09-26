grammar Infix;

eval : expression ;

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
	| variable
	| constant
    | '(' expression ')'
    ;
	
variable
	: ID
	;

constant
	: NUMBER
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

LPAREN : '(' ;
RPAREN : ')' ;

NUMBER  : [0-9]+ ('.' [0-9]+)? ('e'[0-9]+)? 
		| '.' [0-9]+ ('e'[0-9]+)? ;

ID : [a-zA-Z] [a-zA-Z0-9]*;

COMMENT : '//' .+? ('\n'|EOF) -> skip ;
WS : [ \t\r\n]+ -> skip ; 