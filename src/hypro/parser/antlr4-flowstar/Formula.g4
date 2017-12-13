/*
 * Formula.g4
 *
 * @author Phillip Tse
 * @date 22.6.2017
 *
 * A combined grammar for AnTLR to generate a parser for boolean expressions, equations and formulas.
 *
 * === A LITTLE BIT MORE THAN FILE STRUCTURE ===
 * This grammar is the basic grammar for the other grammars. It is imported by BadStates.g4, InitialSet.g4,
 * Location.g4, Setting.g4 and Transition.g4. Since HybridAutomaton.g4 imports the five grammars listed before,
 * Formula.g4 is imported transitively by HybridAutomaton.g4. 
 * This file is segmented into four parts: A C++ part, a Java part, the parser rules and the lexer rules.
 * The C++ and the java part contain both named actions from AnTLR and parser rules with actions that have target-specific code,
 * to inject target-specific code into the generated HybridAutomatonParser and HybridAutomatonLexer. 
 * Only the C++ code is actually used in Hypro; the Java code is needed for testing the grammars with the AnTLR TestRig (or grun).
 * Then the actual grammar begins: At first, the lexer rules are used to create tokens from the input.
 * AnTLR chooses the first lexer rule that matches the longest coherent token as the rule defining the type of the token.
 * Therefore, keywords and special symbols make up the first lexer rules. Afterwards, more general lexer rules like
 * NUMBER or VARIABLE are introduced.
 * Afterwards the parser takes the tokens and matches them parser rules. During this, the order of the parser rules given in this file 
 * does not matter, in contrast to the lexer rules.
 * The parser will build a parsetree from these rules that can be visited by a visitor. The main visitor for HybridAutomata in Hypro 
 * is HyproHAVisitor.h/.cpp which is a subclass of the generated HybridAutmatonVisitor. 
 *
 * === ON PARSING CONSTANTS ===
 * Following problem occurs when trying to read CONSTANTs in order to replace them with their values afterwards: 
 * The lexer does not really know if a combination of letters and other symbols is actually a CONSTANT or a VARIABLE.
 * This could be solved by using a different lexer mode which is a feature provided by AnTLR.
 * But as AnTLR has not implemented the import of lexer grammars with lexer modes into combined grammars yet, we use another way
 * to implement lexer modes. When the lexer reads the token 'par', a bool named parsingConstants in the lexer is set to true 
 * and we know that every VARIABLE that occurs until the next '}' token is actually a definition for a CONSTANT. 
 * Thus, while parsingConstants is true, we set the type of every VARIABLE to CONSTANT. Now since the CONSTANT rule is before
 * the VARIABLE rule, the lexer would later on match variables with one letter to the type CONSTANT. In order to avoid this, we set a CONSTANT
 * to a VARIABLE, if parsingConstants is false. 
 * The parser then must build a tree first to be able to put the constants and their values into a map before it can check 
 * whether there are CONSTANT tokens in the token stream given from the lexer. If this is the case, a TokenStreamRewriter replaces all VARIABLE
 * tokens that have the same text as a CONSTANT with their respective values. The altered input will then be parsed.
 */

grammar Formula;

/////////////////// C++ FOR USAGE ///////////////////////

@lexer::members {
	bool parsingConstants = false;	
}

@parser::postinclude {
	#include <map>
	#include <string>
}

@parser::declarations {
	std::map<std::string, std::string> constants;
}

@parser::members {
	inline const std::map<std::string, std::string>& getConstants() const { return constants; }
}

constantexpr		: CONSTANT EQUALS MINUS? NUMBER {
	//std::cout << "In constantexpr! MINUS text is: " << $MINUS.text << std::endl;
	if($MINUS.text != ""){
		constants.insert({$CONSTANT.text, $MINUS.text.append($NUMBER.text)});
		//std::cout << "Constant " << $CONSTANT.text << " with value " << $MINUS.text.append($NUMBER.text) << " was put in map!\n";
	} else {
		constants.insert({$CONSTANT.text, $NUMBER.text});
		//std::cout << "Constant " << $CONSTANT.text << " with value " << $NUMBER.text << " was put in map!\n";
	}
};

/////////////////// JAVA FOR TESTING //////////////////
//
//@lexer::members {
//	private boolean parsingConstants = false;
//}
//
//@parser::header {
//	import java.util.HashMap;
//	import java.lang.String;
//}
//
//@parser::members {
//	public HashMap<String,String> constants = new HashMap<String,String>();
//	public HashMap<String,String> getConstants() { return constants; }
//}
//
//constantexpr		: CONSTANT EQUALS MINUS? NUMBER {
//	if($MINUS.text != null){
//		constants.put($CONSTANT.text, ($MINUS.text + $NUMBER.text));
//		System.out.println("1.Constant " + $CONSTANT.text + " with value " + $MINUS.text + $NUMBER.text + " was put in map!");
//	} else {
//		constants.put($CONSTANT.text, $NUMBER.text);
//		System.out.println("2.Constant " + $CONSTANT.text + " with value " + $NUMBER.text + " was put in map!");
//	}
//};

/////////////////// Parser Rules /////////////////////

connector 			: PLUS | MINUS ; 
term 				: (NUMBER | VARIABLE) (TIMES connector* (NUMBER | VARIABLE))* ;
polynom				: connector* term (connector+ term)* ;
interval 			: '[' MINUS? (NUMBER | VARIABLE) ',' MINUS? (NUMBER | VARIABLE) ']' ;

equation 			: VARIABLE EQUALS polynom (connector interval)?;
constraint			: polynom (BOOLRELATION | EQUALS) polynom; 
intervalexpr		: VARIABLE IN interval; 
constrset	 		: (constraint | intervalexpr)+ ;
replacedexpr		: MINUS? NUMBER EQUALS MINUS? NUMBER ;

//constantexpr is above in C++ or in Java

/////////////////// Lexer Rules //////////////////////

//Always remember: Keywords first!
IN 					: 'in' ;
PAR 		 		: 'par' { parsingConstants = true; } ;

JUMPS 				: 'jumps' ;
URGENT 				: 'urgent' ;
GUARD 				: 'guard' ;
RESET 				: 'reset' ;
PARALLELOTOPE 		: 'parallelotope aggregation' ;
BOX 				: 'box aggregation' ;
JUMP				: '->' ;
DEFINE 				: ':=' ;

COMMENT				: '#' ~[\r\n]* -> skip ;

EQUALS				: '=' ;
BOOLRELATION		: '<=' | '>=' | '<' | '>' ;
PLUS				: '+' ;
MINUS 				: '-' ;
TIMES				: '*' ;
SBOPEN				: '[' ;
SBCLOSE 			: ']' ;
CBOPEN 				: '{' ;
CBCLOSE 			: '}' { if(parsingConstants){ parsingConstants = false; } };
COMMA 				: ',' ;

fragment UPPERCASE	: [A-Z] ;
fragment LOWERCASE	: [a-z] ;
fragment DIGIT		: [0-9] ;
fragment SPECIALCHAR: '_' | '\'' ;

//BEWARE! Numbers itself can now only be positive. A negative number has an odd number of MINUS connectors in front.
NUMBER				: DIGIT+ ('.' DIGIT+)? ;
CONSTANT 			: (UPPERCASE | LOWERCASE) { if(!parsingConstants) { setType(VARIABLE); } };
VARIABLE			: (UPPERCASE | LOWERCASE)(UPPERCASE | LOWERCASE | DIGIT | SPECIALCHAR)* { if(parsingConstants){ setType(CONSTANT); } };

WS					: (' ' | '\t' | '\n' | '\r' )+ -> channel(HIDDEN) ;






