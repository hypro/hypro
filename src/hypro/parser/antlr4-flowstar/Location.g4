/*
 * Location.g4
 * 
 * @author Phillip Tse @date 20.6.2017
 * 
 * A grammar for AnTLR to generate a parser for the location of a hybrid automaton.
 */

grammar Location;

import Formula;

////// Parser Rules

modes: 'modes' '{' (location | stochasticlocation)* '}';

location: VARIABLE '{' activities invariants* loc_labels '}';

activities: (POLY | LINEAR | NONLINEAR | NONPOLY | LTI) ODE NUMBER* '{' (
		equation
		| intervalexpr
	)* '}';

invariants: 'inv' '{' constrset? '}';

// start of grammer rules exclusively for Stochastic Hybrid Automata
stochasticlocation:
	VARIABLE '{' activities invariants* probdistribution '}';

probdistribution: 'probdist' '{' equation* '}';

loc_labels: URGENT?;

////// Lexer Rules

POLY: 'poly';

LINEAR: 'linear';

NONLINEAR: 'nonlinear';

NONPOLY: 'nonpoly';

LTI: 'lti';

ODE: 'ode';

URGENT: 'urgent';

