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

	


	/*int stateCount = 0;
	State* nextHead;

	for (int i = 0; i < grammar.GetHeadAndSupNodes().size(); i++) {
		std::cout << "Head node: " << grammar.GetHeadAndSupNodes().at(i).first << std::endl;
		State s = State(std::to_string(stateCount));
		stateCount++;
		if (i == 0)
			s.SetIsStart(true);

		int checkNextHead = stateCount;
		if (!(checkNextHead++ >= grammar.GetHeadAndSupNodes().size())) {
			tempState = new State();
		}
			


		std::cout << "Sub nodes: " << std::endl;
		for (int j = 0; j < grammar.GetHeadAndSupNodes().at(i).second.size(); j++) {
			State next = State(std::to_string(stateCount));
			stateCount++;

			s.AddTransition(Transition(&s, grammar.GetHeadAndSupNodes().at(i).second[j], &next));
			std::cout << "\t-" << grammar.GetHeadAndSupNodes().at(i).second[j] << std::endl;
			s.AddTransition(Transition(s, grammar.GetHeadAndSupNodes().at(i).second[j], ));
			if (!nextHead)
				nextHead = new State(std::to_string(stateCount));
				make transition to the next state
			else
				next.AddTransition(Transition(next, ));
				make new next state
		}
		std::cout << std::endl;
	}*/

	/*int stateCount = 0;
	State* from = NULL;
	State* to = NULL;
	std::vector<State> subNodes;
	auto nodeList = grammar.GetAllNodes();
	for (int i = 0; i < nodeList.size(); i++) {
		if (nodeList[i].second == true) {
			if (!from) {
				from = new State(std::to_string(stateCount));
				stateCount++;
			}
			else if (!to) {
				to = new State(std::to_string(stateCount));

				for (int j = 0; j < subNodes.size(); j++) {
					from->AddTransition(Transition(from, ));
				}
				to = NULL;
			}
		} 
		else {
			State s = State(std::to_string(stateCount));
			stateCount++;
			subNodes.push_back(s);
		}
	}*/


	return false;
}

bool NDFA::TurnToDFA()
{
	return false;
}

std::vector<Transition> NDFA::GetTransitions()
{
	return std::vector<Transition>();
}

void NDFA::MakeTransitions(State& head, std::vector<State>& substates)
{
	/*for (int i = 0; i < substates.size(); i++) {
		head.AddTransition(Transition(substates[i], ))
	}*/
}

void NDFA::MakeTransitions(std::vector<State>& substates, State& head)
{

}

void NDFA::PrintModel()
{
	std::cout << "Print Model..." << std::endl;
	for (int i = 0; i < states.size(); i++) {
		states.at(i)->PrintState();
	}
}
