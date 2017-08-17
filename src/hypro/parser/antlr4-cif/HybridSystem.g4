/*exported from CIF3 Sytax*/
grammar HybridSystem;
import Expressions, InputOutput;

specification: 			groupBody;

groupBody: 			optGroupDecls;

automatonBody: 			optAutDecls locations optIoDecls;

optGroupDecls: 			groupDecl*;

groupDecl: 			decl
				| 'import' imports ';'
				| 'namespace' IDENTIFIER ';'
				| 'namespace' RELATIVENAME ';'
				| 'func' types identifier funcParams ':' funcBody
				| identifier ':' name actualParms ';'
				| 'group' 'def' identifier formalParms ':' groupBody 'end'
				| optSupKind 'automaton' 'def' identifier formalParms ':' automatonBody 'end'
				| supKind 'def' identifier ':' groupBody 'end'
				| optSupKind 'automaton' identifier ':' automatonBody 'end'
				| supKind identifier ':' automatonBody 'end';


optAutDecls: 			autDecl*;

autDecl: 			decl
				| 'alphabet' events ';'
				| 'alphabet' ';'
				| 'monitor' events ';'
				| 'monitor' ';'
				| 'disc' type discDecls ';';

decl: 				'type' typeDefs ';'
				| 'enum' enumDefs ';'
				| optControllability 'event' identifier ';'
				| optControllability 'event' eventType identifier ';'
				| controllability identifier ';'
				| controllability eventType identifier ';'
				| 'const' type constantDefs ';'
				| 'alg' type algVarsDefs ';'
				| 'input' type identifier ';'
				| 'cont' contDecls ';'
				| 'equation' equations ';'
				| 'initial' expressions ';'
				| invariantDecls 
				| 'marked' expressions ';'
				| ioDecls;

imports: 			stringToken (',' stringToken)*;

typeDefs: 			identifier '=' type (',' identifier '=' type)*;

enumDefs: 			identifier '=' '{' identifier '}' (',' identifier '=' '{' identifier '}')*;

constantDefs: 			identifier '=' expression (',' identifier '=' expression)*;

algVarsDefs: 			( identifier | identifier '=' expression) ( ',' (identifier | identifier '=' expression))*;

funcParams: 			'(' ')' | '(' funcParamDecls ')';

funcParamDecls: 		type identifier (';' type identifier)*;

funcBody: 			funcVarDecls funcStatements 'end'
				| stringToken ';';

funcVarDecls: 			(type funcVarDecl ';')*;

funcVarDecl: 			( identifier | identifier '=' expression) ( ',' (identifier | identifier '=' expression))*;

funcStatements: 		funcStatement+;

funcStatement: 			adressables ':=' expressions ';'
				| 'if' expressions ':' funcStatements optElifFuncStats optElseFuncStat 'end'
				| 'while' expressions ':' funcStatements 'end'
				| 'break' ';'
				| 'continue' ';'
				| 'return' expressions ';';

optElifFuncStats: 		('elif' expression ':' funcStatements)*;

optElseFuncStat: 		'else' funcStatements;

events: 			name (',' name)*;

coreEdge: 			edgeEvents optEdgeGuard optEdgeUrgent optEdgeUpdate
				| 'when' expressions optEdgeUrgent optEdgeUpdate
				| 'now' optEdgeUpdate
				| 'do' updates;

optEdgeGuard: 			('when' expressions)?;

optEdgeUrgent: 			'now'?;

optEdgeUpdate: 			('do' updates)?;

edgeEvents: 			edgeEvent (',' edgeEvent)*;

edgeEvent: 			'tau'
				| name
				| name '!'
				| name '!' expression
				| name '?';

locations:			location+; 

location: 			'location' ';' 					# loc
				| 'location' identifier ';'			# locId
				| 'location' ':' locationElements		# locElem
				| 'location' identifier ':' locationElements	# locIdElem
				;

locationElements: 		locationElement+;

locationElement: 		'initial' ';'
				| 'initial' expressions ';'
				| invariantDecls
				| 'equation' equations ';'
				| 'marked' ';'
				| 'marked' expressions ';'
				| 'urgent' ';'
				| 'edge' coreEdge 'goto' identifier ';'
				| 'edge' coreEdge ';' ;

actualParms: 			'(' ')' | '(' expressions ')';

formalParms: 			'(' ')' | '(' formalDecls ')';

formalDecls: 			formalDeclaration (';' formalDeclaration)*;

formalDeclaration: 		optControllability 'event' identifier
				| optControllability 'event' eventType identifier
				| controllability identifier
				| controllability eventType identifier
				| name identifier
				| 'location' identifier
				| 'alg' type identifier;

discDecls: 			discDecl (',' discDecl)*;

discDecl: 			identifier
				| identifier 'in' 'any'
				| identifier '=' expression
				| identifier 'in' '{' expressions '}';

contDecls: 			contDecl (',' contDecl)*;

contDecl: 			identifier optDerivate 
				| identifier '=' expression optDerivate;

optDerivate: 			('der' expression)?;

equations: 			equation (',' equation)*;

equation: 			identifier '\'' '=' expression
				| identifier '=' expression;

invariantDecls: 		optSupKind 'invariant' invariants ';'
				| supKind invariants ';' ;

invariants: 			invariant (',' invariant)*;

invariant: 			expression
				| name 'needs' expression
				| nonEmptySetExpression 'needs' expression
				| expression 'disables' name
				| expression 'disables' nameSet ;

updates: 			update (',' update)*;

update: 			adressable ':=' expression
				| 'if' expressions ':' updates optElifUpdates optElseUpdate 'end';

adressables: 			adressable (',' adressable)*;

adressable: 			identifier
				| identifier projections
				| '(' adressable ',' adressable ')';

projections: 			projection*;

projection: 			'[' expression ']';

optElifUpdates: 		('elif' expressions ':' updates)*;

optElseUpdate: 			('else' update)?;

optControllability: 		controllability?;

controllability: 		'controllable'
				| 'uncontrollable';

eventType: 			'void'
				| type;
