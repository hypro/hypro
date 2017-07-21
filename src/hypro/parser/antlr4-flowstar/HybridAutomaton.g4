/*
 * HybridAutomaton.g4
 *
 * @author Phillip Tse
 * @date 27.6.2017
 *
 * A grammar for AnTLR to generate a parser for a hybrid automaton.
 */

grammar HybridAutomaton;

import Location;

////// Parser Rules

// TODO: Until now only declaring the variables correctly implement parsing of locations

start				: 'hybrid reachability' '{' vardeclaration modes '}' ;

vardeclaration		: 'state var' VARIABLE ((',' VARIABLE)+)? ;

//setting				: 'setting' '{'  '}'; 
