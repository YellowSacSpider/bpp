#include "parser.h"


void Parser::Parse() {
	if (tokens[0] == "decl")
	{
		//std::cout << "FOUND VAR decl \n";
		//std::cout << "With type: " << tokens[1] << "\n";
		//std::cout << "With name: " << tokens[2] << "\n";
		//std::cout << "With value: " << tokens[3] << "\n";



		//	CHECK ARITHMETIC BEFORE PUSH VARIABLE TO THE STACK
		//	TODO: MAKE IT BETTER ->
		//	1. GENERIC EVALUATION

		/*
		if (!tokens[4].empty()) {
			if (std::isalpha(tokens[3][0])) lValue = variables[tokens[3]]->iValue;
			else lValue = std::stoi(tokens[3]);
			if (std::isalpha(tokens[5][0])) rValue = variables[tokens[5]]->iValue;
			else lValue = std::stoi(tokens[5]);
				if (tokens[4] == "/") tokens[3] = std::to_string(lValue / rValue);
				else if (tokens[4] == "*") tokens[3] = std::to_string(lValue * rValue);
				else if (tokens[4] == "-") tokens[3] = std::to_string(lValue - rValue);
				else if (tokens[4] == "+") tokens[3] = std::to_string(lValue + rValue);
				tokens.erase(tokens.begin()+4, tokens.begin()+5);
			}
			*/

		Calculate(tokens);
		while (!tokens[4].empty()) {
			Calculate(tokens, 3, tokens.size());
		}
		variables.insert(std::pair<std::string, std::unique_ptr<Variable>>(tokens[2], std::make_unique<Variable>()));
		
		if (tokens[1] == "int") {
			variables[tokens[2]]->type = INT;
			variables[tokens[2]]->iValue = std::stoi(tokens[3]);
		}

		if (tokens[1] == "string") {
			variables[tokens[2]]->type = STRING;
			variables[tokens[2]]->sValue = getStringFromQuotes(tokens[3], 1); // THIS PROBABLY SHOULD BE IN A LEXER
		}
	}
	if (tokens[0] == "print") {
		//std::cout << "FOUND print function \n";

		std::vector<std::string> args;
		// Get args for print
		for (int i = 1; i < tokens.size(); i++) {
			if (tokens[i] != ",") args.emplace_back(tokens[i]);

		}


		for (int i = 0; i < args.size(); i++) {
			if (args[i][0] == '\"') args[i] = getStringFromQuotes(args[i], 1);
			if (std::isalpha(args[i][0])) {
				if (variables[args[i]]->type == INT) args[i] = std::to_string(variables[args[i]]->iValue);
				else if (variables[args[i]]->type == STRING) args[i] = variables[args[i]]->sValue;
			}
		}

		for (const auto& val : args) {
			if (std::isdigit(args[1][0]) || !std::isalpha(args[1][0])) {
				Calculate(args);
				Calculate(args, 0, args.size());
			}
		}


		for (const auto& val : args) {

			std::cout << val << "\n";
		}


		//for (const auto& val : args) {
			//std::cout << val;
		//}
		/*
		int comma_index;
		if (tokens[1][0] == '\"') {
			std::cout << getStringFromQuotes(tokens[1], 1);
		}

		if (std::isalpha(tokens[1][0])) {

			if (variables[tokens[1]]->type == INT) tokens[1] = std::to_string(variables[tokens[1]]->iValue);
			else if (variables[tokens[1]]->type == STRING) tokens[1] = variables[tokens[1]]->sValue;
		}

		if (std::isdigit(tokens[1][0]) || !std::isalpha(tokens[1][0])) {
			for (int i = 1; i < tokens.size(); i++) {
				if (tokens[i] == ",") {
					comma_index = i;
					break;
				}
				else
				{
					comma_index = tokens.size();
				}
			}
			Calculate();
			while (!tokens[2].empty() && tokens[2] != ",") {
				Calculate(1, comma_index);
			}
			std::cout << tokens[1];
		}


		//Check for more print arguments
		for (int i = 1; i < tokens.size(); i++)
		{


			if (tokens[i] == ",") {
				if (tokens[i+1][0] == '\"') {
					std::cout << getStringFromQuotes(tokens[i+1], 1); // THIS PROBABLY SHOULD BE IN A LEXER
				}

				if (std::isalpha(tokens[i+1][0])) {
					if (variables[tokens[i+1]]->type == INT) std::cout << variables[tokens[i+1]]->iValue;
					else if (variables[tokens[i+1]]->type == STRING) std::cout << variables[tokens[i+1]]->sValue;
				}

				if (std::isdigit(tokens[i+1][0]) || !std::isalpha(tokens[i+1][0])) {
					Calculate();
					while (!tokens[i+2].empty() && tokens[i+2] != ",") {
						Calculate(i+1, 2);
					}
					std::cout << tokens[i+1];
				}
			}
		}
		*/

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

void Parser::Calculate(std::vector<std::string>& _tokens, int from, int to) {
	// dumb negative number conversion
	if (from != -1) {
		if (_tokens[from] == "-") {
			_tokens[from] = _tokens[from] + _tokens[from + 1];
			_tokens.erase(_tokens.begin() + from + 1);
			if (_tokens[from + 1].empty()) {
				return;
			}
		}
	}

	// Get matched parenthesis and calculate inside parenthesis
	if (from == -1 && to == -1) {
		std::deque<int> parenthesis_open;
		std::deque<int> parenthesis_closed;
		for (int i = 0; i < _tokens.size(); i++) {
			if (_tokens[i] == "(") {
				parenthesis_open.push_back(i);
				//std::cout << i;
			}
			else if (_tokens[i] == ")") {
				parenthesis_closed.push_back(i);
				//std::cout << i;
			}
			//std::cout << "\n";
		}
		while (!parenthesis_open.empty() && !parenthesis_closed.empty()){
			Calculate(_tokens,parenthesis_open.back(), parenthesis_closed.back());
			//for (int i = 0; i < _tokens.size(); i++)
				//std::cout << _tokens[i];
			parenthesis_open.pop_back();
			parenthesis_closed.pop_back();
		}
		for (int i = 0; i < _tokens.size(); i++) {
			if(_tokens[i] == "(" || _tokens[i] == ")") _tokens.erase(_tokens.begin() + i);
		}
		//for (int i = 0; i < _tokens.size(); i++)
				//std::cout << _tokens[i];
	}

	//************************
	int found = 0;
	if (from > -1 && to > -1) {
			for (int i = from; i < to; i++) {
				if (_tokens[i] == "/") {
					if (_tokens[i + 1] == "-") {
						_tokens[i + 1] = _tokens[i + 1] + _tokens[i + 2];
						_tokens.erase(_tokens.begin() + i + 2);
					}
					lValue = std::stoi(_tokens[i - 1]);
					rValue = std::stoi(_tokens[i + 1]);
					_tokens[i - 1] = std::to_string(lValue / rValue);
					_tokens.erase(_tokens.begin() + i + 1);
					_tokens.erase(_tokens.begin() + i);
					break;
				}
				else if (_tokens[i] == "*") {
					if (_tokens[i + 1] == "-") {
						_tokens[i + 1] = _tokens[i + 1] + _tokens[i + 2];
						_tokens.erase(_tokens.begin() + i + 1);
						_tokens.erase(_tokens.begin() + i);
					}
					lValue = std::stoi(_tokens[i - 1]);
					rValue = std::stoi(_tokens[i + 1]);
					_tokens[i - 1] = std::to_string(lValue * rValue);
					_tokens.erase(_tokens.begin() + i + 1);
					_tokens.erase(_tokens.begin() + i);
					break;
				}
				else if (_tokens[i] == "-") {
					for (int j = from; j < to; j++) {
						if (_tokens[j] == "*" || _tokens[j] == "/")
							found = 1;
							break;
						}
					if (!found) {
						lValue = std::stoi(_tokens[i - 1]);
						rValue = std::stoi(_tokens[i + 1]);
						_tokens[i - 1] = std::to_string(lValue - rValue);
						_tokens.erase(_tokens.begin() + i + 1);
						_tokens.erase(_tokens.begin() + i);
						break;
					}
						}
				else if (_tokens[i] == "+") {
							for (int j = from; j < to; j++) {
								if (_tokens[j] == "*" || _tokens[j] == "/")
									found = 1;
									break;
							}
							if(!found){
								lValue = std::stoi(_tokens[i - 1]);
								rValue = std::stoi(_tokens[i + 1]);
								_tokens[i - 1] = std::to_string(lValue + rValue);
								_tokens.erase(_tokens.begin() + i + 1);
								_tokens.erase(_tokens.begin() + i);
								break;
								}
							}
						}
			}
}