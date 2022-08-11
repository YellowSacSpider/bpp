#include "parser.h"


void Parser::Parse() {
	if (tokens[0] == "decl")
	{
		//std::cout << "FOUND VAR decl \n";
		//std::cout << "With type: " << tokens[1] << "\n";
		//std::cout << "With name: " << tokens[2] << "\n";
		//std::cout << "With value: " << tokens[3] << "\n";

		variables.insert(std::pair<std::string, std::unique_ptr<Variable>>(tokens[2], std::make_unique<Variable>()));
		
		if (tokens[1] == "int") {
			variables[tokens[2]]->type = INT;
			variables[tokens[2]]->iValue = std::stoi(tokens[3]);
		}

		if (tokens[1] == "string") {
			variables[tokens[2]]->type = STRING;
			variables[tokens[2]]->sValue = tokens[3];
		}
	}

	if (tokens[0] == "print") {
		//std::cout << "FOUND print function \n";
		if (tokens[1] == "\"") {
			int i = 0;
			for (; i < tokens.size(); i++) {
				if (tokens[i] == "\"") break;
			}
			for (int k = i+1; k < tokens.size(); k++) {
				if (tokens[k] == "\"") break;
				std::cout << tokens[k] << " ";
			}

		}
		else {
			if (variables[tokens[1]]->type == INT) std::cout << variables[tokens[1]]->iValue;
			else if (variables[tokens[1]]->type == STRING) std::cout << variables[tokens[1]]->sValue;
		}
	}

}
void Parser::displayVariables() {
	for (auto const& [key, __] : variables) {
		if (variables[key]->type == INT) std::cout << variables[key]->iValue;
		else if (variables[key]->type == STRING) std::cout << variables[key]->sValue;
	}
}


void Parser::setTokens(std::vector<std::string> __tokens) {
	tokens.clear();
	if (!__tokens.empty()) {
		tokens = __tokens;
	}
	//Parse();
}