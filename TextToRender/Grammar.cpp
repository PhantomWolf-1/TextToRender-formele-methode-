#include "Grammar.h"
#include <fstream>
#include <streambuf>
#include <string> 
#include <algorithm>




Grammar::Grammar(std::string grammarFilePath)
{
	std::fstream file (grammarFilePath);

	if (file.is_open()) {
		std::string str((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
		std::string tmp = "";
		std::string currentHeadNode;
		std::vector<std::string> currentSubNodes;
		for (int i = 0; i < str.size(); i++) {
			if (str[i] != ',' && str[i] != ' ' && str[i] != '-' && str[i] != '\n') {
				tmp += str[i];
			}
			
			if ((str[i] == ' ' || i == str.size()-1 || str[i] == '\n') && tmp.length() != 0) {
				if (tmp.find(':') != std::string::npos) {
					tmp.erase(remove(tmp.begin(), tmp.end(), ':'));
					
					tmp = ToLowerCase(tmp);
					AddWordToAlphabet(tmp);
					if (tmp != currentHeadNode) {
						if (!currentHeadNode.empty()) {
							this->headAndSupNodes.push_back({currentHeadNode, currentSubNodes});
							currentSubNodes.clear();
						}
						std::cout << "Setting current head" << std::endl;
						currentHeadNode = tmp;
						//this->headAndSupNodes[currentHeadNode] = std::vector<std::string>();
					}
				} 
				else {
					tmp = ToLowerCase(tmp);
					AddWordToAlphabet(tmp);
					currentSubNodes.push_back(tmp);
				}
				
				tmp = "";
			} 
		}
		this->headAndSupNodes.push_back({ currentHeadNode, currentSubNodes });
		file.close();

		for (const auto& item : this->wordAlphabet) {
			std::cout << item << std::endl;
		}

		std::cout << "\nNow all the head and sup nodes: " << std::endl;
		for (int i = 0; i < this->headAndSupNodes.size(); i++) {
			std::cout << "Head node: " << this->headAndSupNodes.at(i).first << std::endl;
			std::cout << "Sub nodes: " << std::endl;
			for (int j = 0; j < this->headAndSupNodes.at(i).second.size(); j++) {
				std::cout << "\t-" << this->headAndSupNodes.at(i).second[j] << std::endl;
			}
			std::cout << std::endl;
		}

	}

	//if (file.is_open()) {
	//	std::string str((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
	//	for (int i = 0; i < str.size(); i++) {
	//		if (str[i] != NULL && str[i] != ' ' && str[i] != ',') {
	//			bool inList = false;
	//			for (const auto& item : this->alphabet) {
	//				if (item == str[i]) {
	//					inList = true;
	//				}
	//			}

	//			if(!inList)
	//				this->alphabet.push_back(str[i]);
	//		}
	//			
	//	}
	//	//std::cout << str << std::endl;
	//	file.close();

	//	this->alphabet.sort();
	//	std::cout << "Current alphabet: " << std::endl;
	//	for (const auto &i : this->alphabet) {
	//		std::cout << i << ", ";
	//	}
	//	std::cout << std::endl;
	//}
}

bool Grammar::AddWordToAlphabet(std::string word)
{
	//std::cout << "After LowerCase: "<< tmp << std::endl;
	if (!IsAlreadyInAlphabet(word)) {
		this->wordAlphabet.push_back(word);
		return true;
	}
		
	return false;
}

std::string Grammar::ToLowerCase(std::string word)
{
	std::string tempString = word;
	std::for_each(tempString.begin(), tempString.end(), [](char& c) {
		//std::cout << "In lower case" << std::endl;
		c = ::tolower(c);
		});

	return tempString;
}

bool Grammar::IsAlreadyInAlphabet(std::string keyword)
{
	for (const auto& item : this->wordAlphabet) {
		if (item == keyword) {
			return true;
		}
	}
	return false;
}






