/*
 * Formula.g4
 *
 * @author Phillip Tse
 * @date 22.6.2017
 *
 * A parser grammar for AnTLR to generate a parser for boolean expressions, equations and formulas.
 */

grammar Formula;

/////////////////// C++ FOR USAGE ///////////////////////
//
//@lexer::declaration {
//	private: 
//		bool parsingConstants = false;
//	protected:	
//}
//
//@parser::postinclude {
//	#include <map>
//	#include <string>
//}
//
//@parser::declarations {
//	private: 
//		std::map<std::string, std::string> constants;
//	public: 
//		inline const std::map<std::string&, std::string&>& getConstants() const { return constants; }
//}
//
//constantexpr		: CONSTANT EQUALS MINUS? NUMBER {
//	if($MINUS.text != ""){
//		constants.insert({$CONSTANT.text, $MINUS.text.append($NUMBER.text)});
//		std::cout << "Constant " << $CONSTANT.text << " with value " << $MINUS.text.append($NUMBER.text) << " was put in map!\n";
//	} else {
//		constants.insert({$CONSTANT.text, $NUMBER.text});
//		std::cout << "Constant " << $CONSTANT.text << " with value " << $NUMBER.text << " was put in map!\n";
//	}	
//};

/////////////////// JAVA FOR TESTING //////////////////

@lexer::members {
	private boolean parsingConstants = false;
}

@parser::header {
	import java.util.HashMap;
	import java.lang.String;
}

@parser::members {
	public HashMap<String,String> constants = new HashMap<String,String>();
	public HashMap<String,String> getConstants() { return constants; }
}

constantexpr		: CONSTANT EQUALS MINUS? NUMBER {
	if($MINUS.text != null){
		constants.put($CONSTANT.text, ($MINUS.text + $NUMBER.text));
		System.out.println("1.Constant " + $CONSTANT.text + " with value " + $MINUS.text + $NUMBER.text + " was put in map!");
	} else {
		constants.put($CONSTANT.text, $NUMBER.text);
		System.out.println("2.Constant " + $CONSTANT.text + " with value " + $NUMBER.text + " was put in map!");
	}
};

/////////////////// Parser Rules /////////////////////

connector 			: PLUS | MINUS ; 
term 				: (NUMBER | VARIABLE) (TIMES connector* (NUMBER | VARIABLE))* ;
polynom				: connector* term (connector+ term)* ;
interval 			: '[' MINUS? NUMBER ',' MINUS? NUMBER ']' ;

equation 			: VARIABLE EQUALS polynom (connector interval)?;
constraint			: polynom (BOOLRELATION | EQUALS) polynom; 
intervalexpr		: VARIABLE IN interval; 
constrset	 		: (constraint | intervalexpr)+ ;

//constantexpr is above in C++ or in Java

/////////////////// Lexer Rules //////////////////////

//Always remember: Keywords first!
IN 					: 'in' ;
PAR 		 		: 'par' { parsingConstants = true; } ;

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

WS					: (' ' | '\t' | '\n' | '\r' )+ -> skip ;






