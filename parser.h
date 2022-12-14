#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

class Parser final {
private:
	enum {
		INT,
		STRING
	};

	struct Variable {
		int type;
		int iValue;
		std::string sValue;
	};

	std::vector<std::string> tokens;
	std::map<std::string, std::unique_ptr<Variable>> variables;

public:
	Parser() {};
	Parser(std::vector<std::string> _tokens) : tokens(_tokens) {}

	void Parse();
	void displayVariables();
	void setTokens(std::vector<std::string> __tokens);
};