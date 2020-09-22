/*
 * Transition.g4
 *
 * @author Phillip Tse
 * @date 20.6.2017
 *
 * A grammar for AnTLR to generate a parser for the transitions of a hybrid automaton.
 */

grammar Transition;

import Formula;

//////// Parser Rules

//fromto must be at the beginning. Then, all the other options are optional.
//It can be that one will have (fromto reset reset reset), in this case trigger a warning!

jumps		: 'jumps' '{' (transition | stochastictransition)* '}' ;

transition 	: fromto (urgent | guard | labels | resetfct | aggregation)* ;

fromto		: VARIABLE JUMP VARIABLE ;

urgent		: 'urgent' ;

guard		: 'guard' '{' constrset? '}' ;

labels      : 'label' '{' VARIABLE* '}' ;

allocation	: VARIABLE DEFINE (polynom | interval) ;

resetfct	: 'reset' '{' allocation* '}' ;

aggregation	: (PARALLELOTOPE | BOX | INTERVALAGG) '{' '}' ;

// start of grammer rules exclusively for Stochastic Hybrid Automata
stochastictransition	: probfrom (urgent | guard | labels)* '{' probtransition* '}';

probtransition		    : probto (resetfct | aggregation)* ;

// <source-location> --
probfrom			    : VARIABLE MINUS MINUS;

// <weight> -> <target-location>
probto				    : NUMBER JUMP VARIABLE ;

//////// Lexer Rules

PARALLELOTOPE 	: 'parallelotope aggregation' ;

BOX 			: 'box aggregation' ;

INTERVALAGG		: 'interval aggregation';

JUMP			: '->' ;

DEFINE 			: ':=' ;
