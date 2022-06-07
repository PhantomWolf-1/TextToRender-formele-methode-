#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <map>


class Grammar
{
private:
	std::vector<char> alphabet;
	std::vector<std::string> wordAlphabet;
	std::vector<std::pair<std::string, std::vector<std::string>>> headAndSupNodes;

public:
	Grammar(std::string grammarFilePath);

	bool IsAlreadyInAlphabet(std::string keyword);
	bool AddWordToAlphabet(std::string word);

	std::string ToLowerCase(std::string word);
};

	



