#include "ErrorListener.h"

namespace hypro {

	void ErrorListener::syntaxError(Recognizer* , Token* , size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr ){

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