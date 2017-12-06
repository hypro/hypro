/*
 * Location.g4
 *
 * @author Phillip Tse
 * @date 20.6.2017
 *
 * A grammar for AnTLR to generate a parser for the location of a hybrid automaton.
 */

grammar Location;

options { tokenVocab = FormulaLexer; }

import FormulaParser;

////// Parser Rules

modes			: 'modes' '{' location* '}' ;

location 		: VARIABLE '{' activities invariants* '}' ;	

activities		: ('poly ode 1' | 'poly ode 2' | 'poly ode 3' | 'linear ode') '{' equation* '}' ; 

invariants		: 'inv' '{' constrset? '}' ;



