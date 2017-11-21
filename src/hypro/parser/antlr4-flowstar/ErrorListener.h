/*
 * ErrorListener.h
 *
 * A class that takes the exception messages from AnTLR4 and converts them
 * into self defined exceptions. 
 *
 * @author Phillip Tse
 * @date 5.9.2017
 */

#pragma once

#include <stdexcept>
#include <exception>
#include "antlr4-runtime.h"

using namespace antlr4;

namespace hypro {

class ErrorListener : public antlr4::BaseErrorListener {

	public:

		ErrorListener(){ }
		~ErrorListener(){ }

		//Recognizer* recognizer, Token* offendingSymbol, , std::exception_ptr e
		void syntaxError(size_t line, size_t charPositionInLine, const std::string &msg);

};

} //namespace hypro
