grammar Matrix;

/* Matrix format:
 *
 * Number<m,n> matrixName = [1,2.5,-3,INF,-INF,...]
 *
 */

//////Parser Rules

type				: WORD SIZE;

name 				: WORD ;

allocation			: type name '=' MATRIX ;


//////Lexer Rules

fragment DIGIT		: [0-9] ;

fragment INF 		: 'I' 'N' 'F' ;

fragment MINF 		: '-' INF ; 

fragment INTEGER	: '-'? DIGIT+ ;

fragment NUMBER 	: (INTEGER ('.' INTEGER)?) | INF | MINF;

fragment UPPERCASE	: [A-Z] ;

fragment LOWERCASE	: [a-z] ;

MATRIX 				: '[' NUMBER (',' NUMBER)* ']' ; 

WORD				: (UPPERCASE | LOWERCASE | '_' | DIGIT)+ ;

//WHITESPACE			: ([\t\r\n] | ' ') -> skip ;
WHITESPACE			: ( '\t' | ' ' | '\n') -> skip ;

SIZE				: '<' INTEGER ',' INTEGER '>' WHITESPACE;



