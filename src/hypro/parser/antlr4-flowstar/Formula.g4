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

term 				: (NUMBER | VARIABLE) (TIMES (NUMBER | VARIABLE))* ;
polynom				: term (PLUS term)* ;
interval 			: '[' NUMBER ',' NUMBER ']' ;

equation 			: VARIABLE EQUALS polynom ;
constraint			: polynom (BOOLRELATION | EQUALS) polynom; 
intervalexpr		: VARIABLE IN interval;  

////// Lexer Rules

//Always remember: Keywords first!
IN 					: 'in' ;
COMMENT				: '#' ~[\r\n] -> skip ;

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
WS					: (' ' | '\t' | '\n' | '\r' )+ -> skip ;


