/*exported from CIF3 Sytax*/
grammar Expressions;

expressions: 		expression (',' expression)*;

optExpression: 		expression?;

expression: 		orExpression
			| orExpression '=>' orExpression
			| orExpression '<=>' orExpression;

equations: 		equation (',' equation)*;

equation: 		identifier '\'' '=' expression							# EquationDerivate
			| identifier '=' expression							# EquationNonDerivate
			;

orExpression: 		andExpression ('or' andExpression)*;

andExpression: 		compareExpression ('and' compareExpression)*;

compareExpression: 	addExpression (COMPOP addExpression)* ;

addExpression: 		mulExpression (ADDOP mulExpression)*;

mulExpression: 		unaryExpression (MULOP unaryExpression)*;

unaryExpression: 	funcExpression									# unaryExprFunc
			| '-' unaryExpression								# unaryExprMinus
			| '+' unaryExpression								# unaryExprPlus
			| 'not' unaryExpression								# unaryExpr
			| 'sample' unaryExpression							# unaryExpr
			;

funcExpression: 	( expressionFactor 
				| stdLibFunction '(' ')' 
				| stdLibFunction '(' expressions ')' )
			( '[' expressions ']'
				| '[' optExpression ':' optExpression ']'
				| '(' ')'
				| '(' expressions ')' )* ;

expressionFactor: 		 'true'									# ExprFact
				| 'false' 								# ExprFact
				| NUMBER 								# ExprFactNumber
				| REALNUMBER								# ExprFactRealNumber
				| name									# ExprFactName
				| stringToken 								# ExprFact
				| 'time' 								# ExprFact
				| '[' ']'								# ExprFact
				| '[' expressions ']'							# ExprFact
				| '{' '}'								# ExprFact
				| nonEmptySetExpression							# ExprFact
				| '{' dictPairs '}'							# ExprFact
				| '(' expression ',' expression ')'					# ExprFact
				| '<' type '>' expressionFactor						# ExprFact
				| 'if' expressions ':' expression optElifExprs 'else' expression 'end'	# ExprFact
				| 'switch' expression ':' switchBody 'end'				# ExprFact
				| '(' expression ')'							# ExprFact
				| name '\''								# ExprFact
				| '?'									# ExprFact
				| 'self'								# ExprFact
				;

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


//Operators
MULOP: '*' | '/' | 'div' | 'mod';
ADDOP: '+' | '-' ;
COMPOP: '<' | '<=' | '=' | '!=' | '>=' | '>' | 'in' | 'sub' ;


fragment DIGIT: [0-9];
fragment LETTER: [A-Za-z];
NUMBER: '0' | [1-9] DIGIT*;
REALNUMBER: NUMBER '.' (DIGIT+); //TODO e
STRING: '"' LETTER* '"';
IDENTIFIER: (LETTER | '_') (LETTER|DIGIT|'_')*;
RELATIVENAME: IDENTIFIER ('.' IDENTIFIER)+;
ABSOLUTENAME: '.' (IDENTIFIER | RELATIVENAME);
ROOTNAME: '^' (IDENTIFIER | RELATIVENAME);

WS : [ \t\r\n]+ -> skip ; // skip spaces, tabs, newlines
