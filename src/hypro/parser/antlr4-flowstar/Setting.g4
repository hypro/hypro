/*
 * Setting.g4
 *
 * @author Phillip Tse
 * @date 27.6.2017
 *
 * A grammar for AnTLR to generate a parser to parse the settings of Flow*.
 */

grammar Setting;

import Formula;

//////// Parser Rules

setting 		: 'setting' '{' fixedsteps time remainder identity plotsetting fixedorders cutoff precision filename maxjumps print '}' ;

//// Important Parser Rules

fixedsteps		: 'fixed steps' NUMBER ;

time 			: 'time' NUMBER ;

plotsetting 	: 'gnuplot octagon' VARIABLE ((',' VARIABLE)+)? ; 

filename 		: 'output' VARIABLE ; 

maxjumps 		: 'max jumps' NUMBER ;

print 			: 'print' VARIABLE ; 
//Note: VARIABLE is only allowed to be "on" or "off". We do not define "on"/"off" lexer rules in 
//this file since all "on"/"off" tokens would be matched as a VARIABLE.
//We do not define "on"/"off" lexer rules in Formula.g4 since 

//// Unimportant Parser Rules

remainder 		: 'remainder estimation' EXPONENTIAL ; 

identity 		: 'identity precondition' ;

fixedorders 	: 'fixed orders' NUMBER ;

cutoff 			: 'cutoff' EXPONENTIAL ;

precision 		: 'precision' NUMBER ;

//////// Lexer Rules

EXPONENTIAL 	: NUMBER 'e' NUMBER ;
