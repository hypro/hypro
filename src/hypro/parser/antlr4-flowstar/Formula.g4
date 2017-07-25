/*
 * Formula.g4
 *
 * @author Phillip Tse
 * @date 22.6.2017
 *
 * A grammar for AnTLR to generate a parser for boolean expressions, equations and formulas.
 */

grammar Formula;

////// Parser Rules

//1. Maybe add MONOM 
//2. Add possiblity of boolexpr v boolexpr ...

term 				: (NUMBER | VARIABLE) (TIMES (NUMBER | VARIABLE))* ;
polynom				: term (PLUS term)* ;

equation 			: VARIABLE EQUALS polynom ;
constraint			: polynom (BOOLRELATION | EQUALS) polynom; 
interval 			: '[' NUMBER ',' NUMBER ']' ;
intervalexpr		: VARIABLE IN interval;  

////// Lexer Rules

//TODO: Add either 'v' keyword for OR for multiple boolean expressions 

//Always remember: Keywords first!
IN 					: 'in' ;

EQUALS				: '=' ;
BOOLRELATION		: '<=' | '>=' | '<' | '>' ;
PLUS				: '+' ;
TIMES				: '*' ;

fragment UPPERCASE	: [A-Z] ;
fragment LOWERCASE	: [a-z] ;
fragment DIGIT		: [0-9] ;
fragment SPECIALCHAR: '_' | '\'' ;

NUMBER				: '-'? DIGIT+ ('.' DIGIT+)? ;
VARIABLE			: (UPPERCASE | LOWERCASE)(UPPERCASE | LOWERCASE | DIGIT | SPECIALCHAR)* ;
//INTERVAL 			: '[' NUMBER ',' NUMBER ']' ;
WS					: (' ' | '\t' | '\n' | '\r' )+ -> skip ;


