#pragma once
#include <iostream>
#include <map>
#include "FunctionUtilities.h"

class Parser final {
private:
	enum {
		INT,
		STRING
	};
	struct Variable {
		int type = 0;
		int iValue = 0;
		std::string sValue = "";
	};

	int lValue = 0;
	int rValue = 0;

	std::vector<std::string> tokens;
	std::map<std::string, std::unique_ptr<Variable>> variables;

public:
	Parser() {};
	Parser(std::vector<std::string> _tokens) : tokens(_tokens) {}

	void Parse();
	void displayVariables();
	void setTokens(std::vector<std::string> __tokens);
	void Calculate(std::vector<std::string>& tokens, int from = -1, int to = -1);
};