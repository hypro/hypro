/*
 * HybridAutomaton.g4
 *
 * @author Phillip Tse
 * @date 27.6.2017
 *
 * A grammar for AnTLR to generate a parser for a hybrid automaton.
 */
 
grammar HybridAutomaton;

import Location, InitialSet, BadStates, Transition, Setting;

///////////// Parser Rules //////////////

start 				: 'hybrid reachability' CBOPEN vardeclaration constantdeclaration? setting modes jumps init+ CBCLOSE unsafeset? ;

vardeclaration      : 'state var' VARIABLE ((COMMA VARIABLE)+)? ;

constantdeclaration : PAR CBOPEN (constantexpr | replacedexpr)* CBCLOSE ;

