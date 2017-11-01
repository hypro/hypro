/*
 * Formula.g4
 *
 * @author Phillip Tse
 * @date 22.6.2017
 *
 * A parser grammar for AnTLR to generate a parser for boolean expressions, equations and formulas.
 */

grammar Formula;

////// Parser Rules

//1. Maybe add MONOM 

connector 			: PLUS | MINUS ; 
term 				: (NUMBER | VARIABLE) (TIMES connector* (NUMBER | VARIABLE))* ;
polynom				: connector* term (connector+ term)* ;
interval 			: '[' MINUS? NUMBER ',' MINUS? NUMBER ']' ;

equation 			: VARIABLE EQUALS polynom ;
constraint			: polynom (BOOLRELATION | EQUALS) polynom; 
intervalexpr		: VARIABLE IN interval;  
constrset	 		: (constraint | intervalexpr)+;

////// Lexer Rules

//Always remember: Keywords first!
IN 					: 'in' ;

COMMENT				: '#' ~[\r\n]* -> skip ;

EQUALS				: '=' ;
BOOLRELATION		: '<=' | '>=' | '<' | '>' ;
PLUS				: '+' ;
MINUS 				: '-' ;
TIMES				: '*' ;

fragment UPPERCASE	: [A-Z] ;
fragment LOWERCASE	: [a-z] ;
fragment DIGIT		: [0-9] ;
fragment SPECIALCHAR: '_' | '\'' ;

//NUMBER				: '-'? DIGIT+ ('.' DIGIT+)? ;
//BEWARE! Numbers itself can now only be positive. A negative number has an odd number of MINUS connectors in front.
NUMBER				: DIGIT+ ('.' DIGIT+)? ;
VARIABLE			: (UPPERCASE | LOWERCASE)(UPPERCASE | LOWERCASE | DIGIT | SPECIALCHAR)*  ;
WS					: (' ' | '\t' | '\n' | '\r' )+ -> skip ;


