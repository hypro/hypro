/*exported from CIF3 Sytax*/
grammar HybridSystem;
import Expressions, CIFLocation, InputOutput;

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

optControllability: 		controllability?;

controllability: 		'controllable'
				| 'uncontrollable';

eventType: 			'void'
				| type;
