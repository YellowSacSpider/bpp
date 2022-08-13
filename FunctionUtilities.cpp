#include "FunctionUtilities.h"

/*
int getIndexOfChar(std::vector<std::string>& __tokens, std::string __token) {
	int i = 0;
	for (; i < __tokens.size(); i++) {
		if (__tokens[i] == __token) break;
	}

	return i;
}
*/

std::string getStringFromQuotes(std::string& __tokens, int charPos) {

	std::string word;
	for (int i = charPos; i < __tokens.size(); i++) {
		if (__tokens[i] != '\"') {
			word += __tokens[i];
		}
	}
	

	return word;
}