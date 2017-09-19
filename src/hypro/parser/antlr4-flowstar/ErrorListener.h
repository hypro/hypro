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

		void syntaxError(Recognizer* recognizer, Token* offendingSymbol, size_t line, size_t charPositionInLine,
      		const std::string &msg, std::exception_ptr e);

};

} //namespace hypro
