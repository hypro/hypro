#include "ErrorListener.h"

namespace hypro {

	void ErrorListener::syntaxError(Recognizer* , Token* token, size_t line, size_t charPositionInLine, const std::string &msg, std::exception_ptr ){

		std::string message("ERROR: at token ");
		message += token->getText();
		message += " (type ";
		message += token->getType();
		message += ") in line: ";
		message += std::to_string(line);
		message += ":";
		message += std::to_string(charPositionInLine);
		message += " ";
		message += msg;
		message += "\n";
		throw std::runtime_error(message);

	}
}