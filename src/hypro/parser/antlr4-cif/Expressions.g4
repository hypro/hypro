/*exported from CIF3 Sytax*/
grammar Expressions;

expressions: 		expression (',' expression)*;

optExpression: 		expression?;

expression: 		orExpression
			| orExpression '=>' orExpression
			| orExpression '<=>' orExpression;

orExpression: 		andExpression ('or' andExpression)*;

andExpression: 		compareExpression ('and' compareExpression)*;

compareExpression: 	addExpression ( ( '<' | '<=' | '=' | '!=' | '>=' | '>' | 'in' | 'sub') addExpression)* ;

addExpression: 		mulExpression (('+' | '-') mulExpression)*;

mulExpression: 		unaryExpression (('*' | '/' | 'div' | 'mod') unaryExpression)*;

unaryExpression: 	funcExpression
			| '-' unaryExpression
			| '+' unaryExpression
			| 'not' unaryExpression
			| 'sample' unaryExpression;

funcExpression: 	( expressionFactor 
				| stdLibFunction '(' ')' 
				| stdLibFunction '(' expressions ')' )
			( '[' expressions ']'
				| '[' optExpression ':' optExpression ']'
				| '(' ')'
				| '(' expressions ')' )* ;

expressionFactor: 		'true' 
				| 'false' 
				| NUMBER 
				| REALNUBER
				| stringToken 
				| 'time' 
				| '[' ']'
				| '[' expressions ']'
				| '{' '}'
				| nonEmptySetExpression
				| '{' dictPairs '}'
				| '(' expression ',' expression ')'
				| '<' type '>' expressionFactor
				| 'if' expressions ':' expression optElifExprs 'else' expression 'end'
				| 'switch' expression ':' switchBody 'end'
				| '(' expression ')'
				| name
				| name '\''
				| '?'
				| 'self';

nonEmptySetExpression: 		'{' expressions '}';

dictPairs: 			expression ':' expression (',' expression ':' expression);

optElifExprs: 			(expression ':' expression 'elif')*;

switchBody: 			switchCases
				| switchCases 'else' expression
				| 'else' expression;

switchCases: 			('case' expression ':' expression)+;

types: 				type (',' type)*;

type: 				'bool'
				|'int'
				|'int' '[' expression '..' expression ']'
				|'real'
				|'string'
				|'list' type
				|'list' '[' expression ']' type
				|'list' '[' expression '..' expression']' type
				|'set' type
				|'dict' '(' type ':' type ')'
				|'tuple' '(' fields ')'
				|'func' type '(' ')'
				|'func' type '(' types ')'
				|'dist' type
				|name;

fields: 			field (',' field)*;

field:				type identifier;

nameSet: 			'{' names '}';

names: 				name (',' name)*;

name: 				identifier
				| RELATIVENAME
				| ABSOLUTENAME
				| ROOTNAME;

optSupKind: 			supKind?;

supKind: 			'plant'
				| 'requirement'
				| 'supervisor';

identifier: 			IDENTIFIER;
stringToken: 			STRING;

stdLibFunction: 'acosh' |'acos'|'asinh'|'asin'|'atanh'|'cosh'|'cos'|'sinh'
|'sin'|'tanh'|'tan'|'abs'|'cbrt'|'ceil'|'del'|'empty'
|'exp'|'floor'|'fmt'|'ln'|'log'|'max'|'min'|'pop'|'pow'
|'round'|'scale'|'sign'|'size'|'sqrt'|'bernoulli'|'beta';


fragment DIGIT: [0-9];
fragment LETTER: [A-Za-z];
NUMBER: '0' | [1-9] DIGIT*;
REALNUBER: NUMBER '.' (DIGIT+); //TODO e
STRING: '"' LETTER* '"';
IDENTIFIER: (LETTER | '_') (LETTER|DIGIT|'_')*;
RELATIVENAME: IDENTIFIER ('.' IDENTIFIER)+;
ABSOLUTENAME: '.' (IDENTIFIER | RELATIVENAME);
ROOTNAME: '^' (IDENTIFIER | RELATIVENAME);

WS : [ \t\r\n]+ -> skip ; // skip spaces, tabs, newlines
