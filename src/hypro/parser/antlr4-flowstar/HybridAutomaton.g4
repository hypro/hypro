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

start 				: old | comp ;

old                 : 'hybrid reachability' CBOPEN automaton CBCLOSE unsafeset? ;

automaton           : vardeclaration constantdeclaration? setting? modes jumps init+ ;

comp                : setting 'hybrid reachability' CBOPEN globalvardeclaration 'components' CBOPEN component+ CBCLOSE CBCLOSE ;

vardeclaration      : 'state var' VARIABLE ((COMMA VARIABLE)+)? ;

constantdeclaration : PAR CBOPEN (constantexpr | replacedexpr)* CBCLOSE ;

globalvardeclaration : 'global state var' VARIABLE ((COMMA VARIABLE)+)? ;

component            : VARIABLE CBOPEN automaton CBCLOSE ;