#include "lexer.h"
#include "parser.h"

int main() {
	std::string word = "";
	Lexer lexer;
	Parser parser;
	while (word != "exit()") {
		std::cout << ">> ";
		std::getline(std::cin, word);
		if (!word.empty()) {
			lexer.setCode(word);
			parser.setTokens(lexer.Tokenize());
			parser.Parse();
			std::cout << "\n";
		}
	}

	/*
	parser.Parse();
	lexer.setCode("print abc");
	parser.setTokens(lexer.Tokenize());
	parser.Parse();
	//parser.displayVariables();
	*/
	return 0;
}