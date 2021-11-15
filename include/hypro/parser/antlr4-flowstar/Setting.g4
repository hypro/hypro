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

setting 		: 'setting' '{' (fixedsteps | time | remainder | identity | qrprecond | plotsetting | fixedorders | adaptiveorders | cutoff | precision | filename | maxjumps | print)* '}' ;

//// Important Parser Rules

fixedsteps		: 'fixed steps' NUMBER ;

time 			: 'time' NUMBER ;

plotsetting 	: 'gnuplot octagon' VARIABLE ((',' VARIABLE)+)? ;

filename 		: 'output' VARIABLE ;

maxjumps 		: 'max jumps' NUMBER ;

print 			: 'print' VARIABLE ;

//// Unimportant Parser Rules

remainder 		: 'remainder estimation' EXPONENTIAL ;

identity 		: 'identity precondition' ;

qrprecond 		: 'QR precondition' ;

fixedorders 	: 'fixed orders' NUMBER ;

adaptiveorders  : 'adaptive orders' '{' 'min' NUMBER ',' 'max' NUMBER '}' ;

cutoff 			: 'cutoff' EXPONENTIAL ;

precision 		: 'precision' NUMBER ;

//////// Lexer Rules

EXPONENTIAL 	: MINUS? NUMBER 'e' MINUS? NUMBER ;
