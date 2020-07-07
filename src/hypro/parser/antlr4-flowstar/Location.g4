/*
 * Location.g4
 *
 * @author Phillip Tse
 * @date 20.6.2017
 *
 * A grammar for AnTLR to generate a parser for the location of a hybrid automaton.
 */

grammar Location;

import Formula;

////// Parser Rules

modes			: 'modes' '{' location* '}' ;

location 		: VARIABLE '{' activities invariants* '}' ;

activities 		: (POLY | LINEAR | NONLINEAR | NONPOLY | LTI) ODE NUMBER* '{' (equation | intervalexpr)* '}' ;

invariants		: 'inv' '{' constrset? '}' ;

////// Lexer Rules

POLY  			: 'poly' ;

LINEAR 			: 'linear' ;

NONLINEAR       : 'nonlinear' ;

NONPOLY         : 'nonpoly' ;

LTI             : 'lti' ; 

ODE 			: 'ode' ;

