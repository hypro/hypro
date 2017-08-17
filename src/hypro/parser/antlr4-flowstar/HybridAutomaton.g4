/*
 * HybridAutomaton.g4
 *
 * @author Phillip Tse
 * @date 27.6.2017
 *
 * A grammar for AnTLR to generate a parser for a hybrid automaton.
 */
 
grammar HybridAutomaton;

import Transition, Setting, Location, InitialSet;

////// Parser Rules
 
start               : 'hybrid reachability' '{' vardeclaration setting modes jumps init'}' ;
 
vardeclaration      : 'state var' VARIABLE ((',' VARIABLE)+)? ;


