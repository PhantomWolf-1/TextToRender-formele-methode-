#include "NDFA.h"
#include <string>


NDFA::NDFA(Grammar g) : grammar(g), NDFAdone(false)
{
}

NDFA::~NDFA()
{
}

bool NDFA::CreateNDFA()
{
	std::vector<std::shared_ptr<State>> headStates;
	std::vector<std::shared_ptr<State>> subStates;
	auto headAndSubNodes = grammar.GetHeadAndSupNodes();
	int stateCount = 1;
	for (int i = 0; i < headAndSubNodes.size(); i++) {
		headStates.push_back(std::make_shared<State>(std::to_string(stateCount)));
		stateCount++;
		for (int j = 0; j < headAndSubNodes.at(i).second.size(); j++) {
			subStates.push_back(std::make_shared<State>(std::to_string(stateCount)));
			stateCount++;
		}
	}
	std::cout << "stateCount: " << stateCount << std::endl;

	std::shared_ptr<State> start = std::make_shared<State>(std::to_string(0));
	start->SetIsStart(true);
	start->AddTransition(std::make_shared<Transition>(start, headAndSubNodes.at(0).first, headStates.at(0)));
	states.push_back(start);
	startState = start;
	currentState = start;

	int subStateCount = 0;
	for (int i = 0; i < headAndSubNodes.size(); i++) {
		states.push_back(headStates.at(i));
		
		for (int j = 0; j < headAndSubNodes.at(i).second.size(); j++) {
			headStates.at(i)->AddTransition(std::make_shared<Transition>(headStates.at(i), headAndSubNodes.at(i).second.at(j), subStates.at(subStateCount)));
			int extraCount = i;
			extraCount += 1;
			if (!(extraCount >= headAndSubNodes.size())) {
				subStates.at(subStateCount)->AddTransition(std::make_shared<Transition>(subStates.at(subStateCount), headAndSubNodes.at(extraCount).first, headStates.at(extraCount)));
			}
			else {
				subStates.at(subStateCount)->SetIsFinal(true);
			}
			states.push_back(subStates.at(subStateCount));
			subStateCount++;
		}
	}


	if (headStates.size() != 0 && subStates.size() != 0)
		return true;


	return false;
}

bool IsValueInList(std::string value, std::vector<std::string> list) {
	for (int i = 0; i < list.size(); i++) {
		if (value == list.at(i)) {
			return true;
		}
	}
	return false;
}

bool NDFA::TurnToDFA()
{
	std::shared_ptr<State> error = std::make_shared<State>(std::to_string(states.size()));
	states.push_back(error);
	std::vector<std::string> allKeywords = grammar.GetWordAlphabet();

	for (int i = 0; i < states.size(); i++) {

		if (!states.at(i)->GetIsStart()) {
			std::vector<std::string> keyWordsAlreadyUsed;

			std::vector<std::string> keywordsUsed;
			for (int keywordIndex = 0; keywordIndex < allKeywords.size(); keywordIndex++) {
				for (int j = 0; j < states.at(i)->GetTransitions().size(); j++) {
					if (states.at(i)->GetTransitions().at(j)->GetKeyword() == allKeywords.at(keywordIndex)) {
						keyWordsAlreadyUsed.push_back(states.at(i)->GetTransitions().at(j)->GetKeyword());
					}
				}
			}

			/*for (int j = 0; j < states.at(i)->GetTransitions().size(); j++) {
				std::cout << "transition keyword to check: " << states.at(i)->GetTransitions().at(j)->GetKeyword() << std::endl;
				for (int keywordIndex = 0; keywordIndex < allKeywords.size(); keywordIndex++) {
					if (states.at(i)->GetTransitions().at(j)->GetKeyword() == allKeywords.at(keywordIndex)) {
						allKeywords.erase(allKeywords.begin() + keywordIndex);
					}
					if (states.at(i)->GetTransitions().at(j)->GetKeyword() != allKeywords.at(keywordIndex)) {
						if (!IsValueInList(allKeywords.at(keywordIndex), keyWordsToAdd)) {
							std::cout << "keyword added to list: " << allKeywords.at(keywordIndex) << std::endl;
							keyWordsToAdd.push_back(allKeywords.at(keywordIndex));
						}
					}
				}
			}*/
			for (int addIndex = 0; addIndex < allKeywords.size(); addIndex++) {
				bool addKeyword = true;
				for (int k = 0; k < keyWordsAlreadyUsed.size(); k++) {
					if (addKeyword && allKeywords.at(addIndex) == keyWordsAlreadyUsed.at(k)) {
						addKeyword = false;
					}
				}

				if(addKeyword)
					states.at(i)->AddTransition(std::make_shared<Transition>(states.at(i), allKeywords.at(addIndex), error));
				//std::cout << "transition added to error with keyword: " << keyWordsToAdd.at(addIndex) << ", for state: " << states.at(i)->GetStateName() << std::endl;
				
			}
		}
		
	}

	return false;
}


void NDFA::PrintModel()
{
	std::cout << "Print Model..." << std::endl;
	for (int i = 0; i < states.size(); i++) {
		states.at(i)->PrintState();
	}
}

bool NDFA::isDetermenistic()
{
	for (int i = 0; i < states.size(); i++) {
		if (!states.at(i)->GetIsStart()) {
			if (!states.at(i)->isDeterministic(grammar.GetWordAlphabet())) {
				return false;
			}
		}
		
	}
	return true;
}

void NDFA::LoopThroughModel(std::string input)
{
	std::string tmp = "";
	for (int i = 0; i < input.length(); i++) {
		if (input.at(i) != ' ' && input.at(i) != ',' && input.at(i) != '.') {
			//std::cout << "input added:" << input.at(i) << "..." << std::endl;
			tmp += input.at(i);
		}


		if ((input.at(i) == ' ' || input.at(i) == ',' || input.at(i) == '.' || i == input.length() - 1) && tmp.length() != 0) {
			if (tmp != "") {
				//std::cout << "Check for the word:" << tmp << "..." << std::endl;
				CheckForNextState(tmp);
				tmp = "";
			}
		}
	}
}

void NDFA::CheckForNextState(std::string input)
{
	std::shared_ptr<State> tmp = currentState->GetStateFromKeyword(input);
	if (tmp != nullptr) {
		transitionsMade.push_back(currentState->GetTransitionFromKeyword(input)->GetKeyword());
		currentState = tmp;
	}
		
}

void NDFA::PrintCurrentState()
{
	std::cout << "current state is: " << currentState->GetStateName() << std::endl;
	std::cout << "is current state an end state?: " << currentState->GetIsFinal() << std::endl;

}

bool NDFA::IsCurrentStateFinal()
{
	if (currentState != nullptr)
		return currentState->GetIsFinal();

	return false;
}

std::vector<std::string> NDFA::GetTransitionsMade()
{
	return transitionsMade;
}

void NDFA::ResetValues()
{
	this->currentState = startState;
	this->transitionsMade.clear();
}


