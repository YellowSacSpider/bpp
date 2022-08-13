#include "lexer.h"
#include "FunctionUtilities.h"


void Lexer::Advance() {
	if (*textptr != '\0' || *textptr == ' ' || *textptr == '\t') // increment pointer until pass a null or increment pointer if pass a space.
		textptr++;
}
void Lexer::Check() {
	if (*textptr == '\0')
	{
		tokens.emplace_back(token);
	}
	switch (*textptr)
	{
	//Make string
	case '\"':
		token += '\"';
		while (true) {
			if (*(++textptr) != '\"') token += *textptr;
			else break;
		}
		token += '\"';
		tokens.emplace_back(token);
		token.clear();
		break;
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '(':
	case ')':
	case '[':
	case ']':
	case '{':
	case '}':
	case ',':
	case '.':
	case '!':
	case '?':
	case '@':
	case '#':
	case '$':
	case '^':
	case '&':
	case '_':
	case '=':
	case '`':
	case '~':
	case ';':
	case '\'':
	case ':':
	case '|':
	case '<':
	case '>':
	case '\\':
	case '//':
		token = *textptr;
		tokens.emplace_back(token);
		token.clear();
		break;
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
		token += *textptr;
		if (!std::isalnum(*(textptr + 1))) {
			tokens.emplace_back(token);
			token.clear();
		}
		break;


	}
}
void Lexer::setCode(std::string m_code)
{
	code = m_code;
	textptr = &code[0];
}

std::vector<std::string> Lexer::Tokenize() {
	if (code.empty()) {
		std::cout << "CANNOT TOKENIZE EMPTY STRING!" << '\n';
		return tokens;
	}

	tokens.clear();
	token.clear();
	while (true) {
		if (*textptr == '\0') //check dupy
		{
			Check();
			break;
		}
		Check();
		Advance();
	}

	return tokens;
}

void Lexer::Display() {
	for (const auto& val : tokens) {
		std::cout << val;
		std::cout << '\n';
	}
	std::cout << '\n';
}