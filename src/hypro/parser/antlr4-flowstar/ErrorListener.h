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

		//The parameters Recognizer*, Token* and std::exception_ptr must stay as this is a function inherited from BaseErrorListener
		void syntaxError(Recognizer* , Token* , size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr);

};

} //namespace hypro
