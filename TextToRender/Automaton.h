#pragma once
#include "Grammar.h"
#include "Transition.h"

class Automaton
{
private:
	std::vector<State> states;


public:
	Automaton(Grammar grammar);
	~Automaton();
};

