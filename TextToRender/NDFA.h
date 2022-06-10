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

	void MakeTransitions(State& head, std::vector<State>& substates);
	void MakeTransitions(std::vector<State>& substates, State& head);


public:
	NDFA(Grammar g);
	~NDFA();

	bool CreateNDFA();
	bool TurnToDFA();

	std::vector<Transition> GetTransitions();

	void PrintModel();
	bool isDetermenistic();

};

