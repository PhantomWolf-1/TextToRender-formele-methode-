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

	
	std::shared_ptr<State> startState;
	std::shared_ptr<State> currentState;
	std::vector<std::string> transitionsMade;

public:
	NDFA(Grammar g);
	~NDFA();

	bool CreateNDFA();
	bool TurnToDFA();

	void PrintModel();
	bool isDetermenistic();

	void LoopThroughModel(std::string input);
	void CheckForNextState(std::string input);

	void PrintCurrentState();
	bool IsCurrentStateFinal();

	std::vector<std::string> GetTransitionsMade();

	void ResetValues();

};

