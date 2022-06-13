#pragma once
#include "Grammar.h"


#include <memory>
#include "Transition.h"




class NDFA
{
private:
	std::vector<std::shared_ptr<State>> states;
	Grammar grammar;
	bool NDFAdone;

	std::shared_ptr<State> currentState;
	std::vector<std::string> transitionsMade;

public:
	NDFA(Grammar g);
	~NDFA();

	bool CreateNDFA();
	bool TurnToDFA();

	void PrintModel();
	bool isDetermenistic();

	void CheckForNextState(std::string input);

	void PrintCurrentState();

	std::vector<std::string> GetTransitionsMade();

};

