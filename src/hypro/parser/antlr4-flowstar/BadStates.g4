/*
 * BadStates.g4
 *
 * Grammar to parse bad states in a given model file.
 *
 * @author Phillip Tse
 * @date 14.9.2017
 */ 

grammar BadStates;

options { tokenVocab = FormulaLexer; }

import FormulaParser;

/////////// Parser Rules

unsafeset 			: 'unsafe set' '{' (gbadstate | lbadstate)* '}' ;

lbadstate 			: VARIABLE '{' constrset? '}' ;

gbadstate			: constrset ;
