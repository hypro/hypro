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

jumps		: 'jumps' '{' transition* '}' ;

transition 	: fromto (urgent | guard | labels | resetfct | aggregation)* ;

fromto		: VARIABLE JUMP VARIABLE ;

urgent		: 'urgent' ;

guard		: 'guard' '{' constrset? '}' ;

labels      : 'label' '{' VARIABLE* '}' ;

allocation	: VARIABLE DEFINE (polynom | interval) ;

resetfct	: 'reset' '{' allocation* '}' ;

aggregation	: (PARALLELOTOPE | BOX | INTERVALAGG) '{' '}' ;

//////// Lexer Rules

PARALLELOTOPE 	: 'parallelotope aggregation' ;

BOX 			: 'box aggregation' ;

INTERVALAGG		: 'interval aggregation';

JUMP			: '->' ;

DEFINE 			: ':=' ;
