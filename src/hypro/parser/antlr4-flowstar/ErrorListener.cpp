#include "ErrorListener.h"

namespace hypro {

	//Recognizer* recognizer, Token* offendingSymbol, , std::exception_ptr e
	void ErrorListener::syntaxError(size_t line, size_t charPositionInLine, const std::string &msg){

		std::string message("ERROR: line: ");
		message += std::to_string(line);
		message += ":";
		message += std::to_string(charPositionInLine);
		message += " ";
		message += msg;
		message += "\n";
		throw std::runtime_error(message);

	}
}