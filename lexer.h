#pragma once
#include <iostream>
#include <vector>
#include <string>

class Lexer final {
private:
	std::string token;
	std::vector<std::string> tokens{};
	std::string code;
	char* textptr = nullptr;
public:
	void Advance();
	void Check();
	std::vector<std::string> Tokenize();
	void Display();
	void setCode(std::string m_code);
	Lexer() {};
	Lexer(std::string f_code) : code(f_code)
	{
		textptr = &code[0];
	}


};

